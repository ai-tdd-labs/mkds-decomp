#!/usr/bin/env python3
"""coddog.py — fuzzy opcode-similarity example finder + scheduler (mkds-native).

coddog_pool.py clusters only on EXACT mnemonic-sequence / name families, so a
target that is one or two instructions off from an already-matched function gets
no example. This ranks unmatched targets against the whole matched corpus by
FUZZY opcode similarity (difflib SequenceMatcher ratio over the mnemonic token
sequence, with a cheap opcode-set Jaccard prefilter), like sm64ds's coddog.

Two uses, both consumed by wave_prep:
  1. Examples : the top-K most-similar MATCHED sources per target -> few-shot
     scaffolding pasted into the brief (fuzzy, not exact-shape).
  2. Scheduling: order a batch so targets with a close matched sibling go first
     (--spread) -> best in-context example, highest hit rate.

  tools/coddog.py --explain func_020a9224           # closest matched siblings
  tools/coddog.py --funcs func_X,func_Y --top 3     # JSON: examples per target
"""
import argparse
import difflib
import json
import pathlib
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import aimatch  # find_symbol / iter_modules / target_bytes / module_binary
from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB

MKDS = pathlib.Path(__file__).resolve().parent.parent
SRC = MKDS / "src" / "arm9"
_MD = {"arm": Cs(CS_ARCH_ARM, CS_MODE_ARM), "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB)}


def opseq(data, mode):
    """mnemonic token sequence for a code blob."""
    return tuple(i.mnemonic for i in _MD[mode].disasm(data, 0))


def _sym_table():
    """{name: (module, mode, addr, size)} over arm9 + overlays."""
    import re
    out = {}
    for mod, symfile in aimatch.iter_modules():
        for line in symfile.read_text().splitlines():
            m = aimatch.SYM_RE.match(line)
            if m and m.group("size"):
                out[m.group("name")] = (mod, m.group("mode"),
                                        int(m.group("addr"), 16),
                                        int(m.group("size"), 16))
    return out


def _matched_names():
    names = {}
    for line in (MKDS / "ai/matched.jsonl").read_text().splitlines():
        if line.strip():
            r = json.loads(line)
            names[r["func"]] = r
    return names


def build_corpus(syms, matched):
    """[(name, opset, opseq, srcpath)] for every matched function we can read."""
    corpus = []
    for name in matched:
        if name not in syms:
            continue
        mod, mode, addr, size = syms[name]
        src = SRC / f"{name}.c"
        if not src.is_file():
            continue
        try:
            data = aimatch.target_bytes(mod, addr, size)
        except SystemExit:
            continue
        seq = opseq(data, mode)
        corpus.append((name, set(seq), seq, src))
    return corpus


def rank(target_name, syms, corpus, top=3, prefilter=40):
    """top-K matched siblings for a target, by fuzzy opcode similarity."""
    if target_name not in syms:
        return []
    mod, mode, addr, size = syms[target_name]
    try:
        tseq = opseq(aimatch.target_bytes(mod, addr, size), mode)
    except SystemExit:
        return []
    tset = set(tseq)
    # cheap Jaccard prefilter to prune the O(n*m) ratio pass
    scored_pre = sorted(
        ((len(tset & oset) / len(tset | oset) if (tset or oset) else 0.0, i)
         for i, (_n, oset, _s, _p) in enumerate(corpus)),
        reverse=True)[:prefilter]
    sm = difflib.SequenceMatcher()
    sm.set_seq2(tseq)
    out = []
    for _j, i in scored_pre:
        name, _oset, seq, src = corpus[i]
        if name == target_name:
            continue
        sm.set_seq1(seq)
        out.append((sm.ratio(), name, src))
    out.sort(reverse=True)
    return out[:top]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--funcs", help="komma-lijst doelen")
    ap.add_argument("--explain", help="toon dichtstbijzijnde matched siblings")
    ap.add_argument("--top", type=int, default=3)
    args = ap.parse_args()

    syms = _sym_table()
    matched = _matched_names()
    corpus = build_corpus(syms, matched)

    if args.explain:
        for score, name, src in rank(args.explain, syms, corpus, args.top):
            print(f"  {score:.0%}  {name:40} {src.relative_to(MKDS)}")
        return

    targets = [f.strip() for f in (args.funcs or "").split(",") if f.strip()]
    result = {}
    for t in targets:
        result[t] = [{"score": round(s, 3), "func": n,
                      "src": str(p.relative_to(MKDS))}
                     for s, n, p in rank(t, syms, corpus, args.top)]
    print(json.dumps(result, indent=1))


if __name__ == "__main__":
    main()
