#!/usr/bin/env python3
"""funcfacts.py — harvest per-function facts from our own matched C.

The cracking agents' briefings only show callee NAMES; but for every matched
function we already KNOW the full truth (signature, arg meaning, one-line
summary) — it's just locked away in individual .c files. This tool extracts
it into ai/funcfacts.jsonl {func, sig, doc}; wave_prep injects the facts for
each callee of a target, so agents stop re-guessing argument counts and
return values of functions we already cracked.

  tools/funcfacts.py            # rebuild ai/funcfacts.jsonl from src/
"""
import json
import pathlib
import re

MKDS = pathlib.Path(__file__).resolve().parent.parent
SRC = MKDS / "src"

# definitie-regel: 'ret naam(args) {' (geen extern, geen ;)
DEF_RE = re.compile(r"^\s*((?:[\w\*]+[\s\*]+)+)(\w+)\s*\(([^)]*)\)\s*\{", re.M)
COMMENT_RE = re.compile(r"/\*(.*?)\*/", re.S)


def main():
    facts = []
    for f in sorted(SRC.rglob("*.c")):
        txt = f.read_text()
        # eerste doc-blok -> eerste zin als samenvatting
        doc = ""
        m = COMMENT_RE.search(txt)
        if m and txt.lstrip().startswith("/*"):
            raw = " ".join(l.strip(" *") for l in m.group(1).splitlines())
            doc = raw.split(". ")[0].strip()[:160]
        stripped = COMMENT_RE.sub("", txt)
        for dm in DEF_RE.finditer(stripped):
            ret, name, args = dm.group(1).strip(), dm.group(2), " ".join(dm.group(3).split())
            if name in ("if", "for", "while", "switch"):
                continue
            facts.append({"func": name, "sig": f"{ret} {name}({args})", "doc": doc})
            break  # één definitie per bestand (onze conventie)
    out = MKDS / "ai/funcfacts.jsonl"
    out.write_text("\n".join(json.dumps(x) for x in facts) + "\n")
    print(f"{len(facts)} functie-feiten -> {out.relative_to(MKDS)}")


if __name__ == "__main__":
    main()
