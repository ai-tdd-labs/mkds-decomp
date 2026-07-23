#!/usr/bin/env python3
"""name_propagate.py — give data_<addr> globals real names from cross-function evidence.

Agents already document what a global IS in per-function comments (e.g.
`extern char data_0217af28[];  /* shared 0x100 path buffer */`) and in struct
typedefs. This tool harvests that evidence across ALL matched src files, and for
each global that (a) is referenced by >= MIN_REFS functions and (b) has a
consistent human description, proposes a real gName and renames it everywhere via
names.rename_everywhere (config symbols + src + scratch + matched.jsonl; relocs
are address-based so BYTES DO NOT CHANGE). Run build.sh afterwards to prove it.

  tools/name_propagate.py            # dry run: print proposals
  tools/name_propagate.py --apply    # rename + (caller must) rebuild to verify
"""
import argparse
import collections
import pathlib
import re

MKDS = pathlib.Path(__file__).resolve().parent.parent
SRC = MKDS / "src"
MIN_REFS = 8

GLOBAL_RE = re.compile(r"\bdata_(02[0-9a-fA-F]{6})\b")
# an 'extern <type> data_X ...;  /* comment */' or 'typedef struct {...} Name; extern Name *data_X'
EXTERN_CMT = re.compile(
    r"extern\s+[\w \*]+\bdata_(02[0-9a-fA-F]{6})\b[^;]*;\s*/\*\s*(.+?)\s*\*/")
STRUCT_PTR = re.compile(
    r"extern\s+(\w+)\s*\*\s*data_(02[0-9a-fA-F]{6})\b")  # extern CupPictureWork *data_X

STOP = {"the", "a", "an", "of", "for", "to", "into", "shared", "current", "this"}


def slug(desc):
    """turn a human description into a gCamelCase name."""
    words = re.findall(r"[A-Za-z0-9]+", desc)
    words = [w for w in words if w.lower() not in STOP][:4]
    if not words:
        return None
    return "g" + "".join(w[:1].upper() + w[1:] for w in words)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--min-refs", type=int, default=MIN_REFS)
    args = ap.parse_args()

    refcount = collections.Counter()
    descs = collections.defaultdict(collections.Counter)   # addr -> {desc: n}
    structnames = collections.defaultdict(collections.Counter)  # addr -> {StructName: n}

    for f in sorted(SRC.rglob("*.c")) + sorted(SRC.rglob("*.cpp")):
        txt = f.read_text()
        for addr in set(GLOBAL_RE.findall(txt)):
            refcount[addr] += 1
        for addr, cmt in EXTERN_CMT.findall(txt):
            # ignore pure format-string comments ("%s%s") — not a good name source
            if cmt.strip('"').replace("%s", "").replace("%d", "").strip(" :/"):
                descs[addr][cmt.strip().strip('"')] += 1
        for sname, addr in STRUCT_PTR.findall(txt):
            if sname not in ("char", "int", "void", "unsigned"):
                structnames[addr][sname] += 1

    proposals = []
    for addr, n in refcount.most_common():
        if n < args.min_refs:
            continue
        # prefer a struct-pointer type name, else the most common description
        name = None
        if structnames[addr]:
            sn = structnames[addr].most_common(1)[0][0]
            name = "g" + sn[0].upper() + sn[1:]
        elif descs[addr]:
            name = slug(descs[addr].most_common(1)[0][0])
        if not name:
            continue
        proposals.append((addr, n, name,
                          descs[addr].most_common(1)[0][0] if descs[addr] else "(struct)"))

    # de-dup names (append addr suffix if two globals want the same name)
    seen = collections.Counter()
    final = []
    for addr, n, name, ev in proposals:
        seen[name] += 1
        uniq = name if seen[name] == 1 else f"{name}_{addr[-4:]}"
        final.append((addr, n, uniq, ev))

    print(f"{len(final)} globals with >= {args.min_refs} refs and clear evidence:\n")
    for addr, n, name, ev in final:
        print(f"  data_{addr}  ({n:2} funcs)  ->  {name:28}  [{ev[:44]}]")

    if args.apply and final:
        import importlib.util
        spec = importlib.util.spec_from_file_location("names", MKDS / "tools/names.py")
        names = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(names)
        for addr, n, name, ev in final:
            names.rename_everywhere(f"data_{addr}", name)
        print(f"\n{len(final)} globals renamed everywhere (config + src + scratch + "
              f"matched.jsonl). Bytes unchanged — run build.sh to prove byte-perfect.")


if __name__ == "__main__":
    main()
