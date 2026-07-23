# Mario Kart DS Decompilation (mkds-decomp)

An AI-driven, from-scratch **matching** decompilation of **Mario Kart DS (Europe)**
into C.

## Progress

<!-- progress:start -->
```
Functions  ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░   7.2%      551 / 7,693
Code size  █░░░░░░░░░░░░░░░░░░░░░░░░░░░░░   2.1%   28,756 / 1,375,980 bytes
```
<!-- progress:end -->

(arm9 main module; numbers as of 2026-07-16. Function count climbs faster than code
size because small, regular functions match first — the honest metric is bytes.)

## What "matching" means

The goal is source code that, when compiled with the original toolchain, produces a
binary byte-for-byte identical to the retail ROM. The full ROM is reproduced
bit-for-bit on every build (SHA1 `ce97d9b43f0d3ca0d48b781983e8a16f6393378f`);
functions not yet decompiled are carried as original-byte gap objects, so the ROM
always matches and every landed function is proven correct.

## Legal and scope

This repo contains only original work: the tooling, the hand-written C, and the
notes. It contains no ROM, no BIOS, and no extracted Nintendo assets — those are
read locally from a cartridge dump you own and are git-ignored. Do not commit
anything derived from the ROM's data or assets. In-game strings are never committed
as literals; code references them as `data_<address>` symbols.

## How matching works

Every candidate is verified the same way: compile it with the original compiler,
byte-compare against the ROM relocation-aware (`tools/aimatch.py`), check relocation
destinations (`tools/linkcheck.py`), then rebuild the full ROM and compare the SHA1.
Nothing counts as matched until all three pass. The work is organized in tiers:

1. **Family replication** (`tools/coddog_pool.py`): functions sharing an identical
   skeleton that differ only in pool words are cloned from one matched template and
   verified individually (~2s per function).
2. **SDK import** (`tools/sdk_hangin.py`): known NitroSDK functions are matched from
   donor decompilations and hung in as isolated objects.
3. **AI wave agents** (`tools/wave_prep.py` / `tools/wave_harvest.py`): parallel
   agents crack real-logic functions, briefed with disassembly context, callee
   signatures (`ai/funcfacts.jsonl`), known struct layouts (`ai/structs.jsonl`), and
   accumulated codegen tricks (`ai/tricks.jsonl`) — a knowledge base the agents both
   read and extend, so every wave starts smarter than the last.

The pinned compiler is **mwccarm 1.2/sp2p3** with these flags:

```
-O4,p -enum int -lang c99 -char signed -interworking -proc arm946e -gccext,on -msgstyle gcc
```

with one measured exception: the game mixes compiler versions per translation unit
(e.g. `Arc_MountArchive` only matches under 1.2/base — the thumb jumptable dispatch
form is the fingerprint), so the toolchain supports per-TU versions.

## Repository layout

| Path | Contents |
|------|----------|
| `src/arm9/` | Decompiled C — one file per function, filename = symbol name |
| `config/eur/arm9/` | dsd config: `symbols.txt`, `relocs.txt`, `delinks.txt` |
| `tools/` | The pipeline: `aimatch.py` (byte oracle), `linkcheck.py`, `coddog_pool.py`, `hangin.py`, `wave_prep.py`/`wave_harvest.py`, `doctor.py`, `diffmap.py`, `batch_compile.py` |
| `notes/` | mwccarm codegen lessons |
| `ai/*.jsonl` | Self-learning knowledge base + match register |
| `PLAN.md` | Full work log: how the matching build works and every breakthrough |

## Naming convention

Names are assigned by evidence tier and never touch the bytes:

| Prefix | Meaning |
|--------|---------|
| plain name (`memchr`, `Arc_MountArchive`) | certain (SDK byte-match or unique string evidence) |
| `Maybe_get_/set_<global>` | tiny global read/write, inferred from shape |
| `Maybe_call_<target>` | thin wrapper around that function |
| `Maybe_CreateObj_<template>` | allocates + initializes an object from that data template |
| `Maybe_calc_/check_/helper_<addr>` | small pure computation / predicate / helper |
| `func_<address>` | a larger function not yet understood |

Per-function evidence lives in `ai/names.jsonl`.

## Setup

You supply your own cartridge dump (EUR). Short version:

```
pip install ndspy capstone pyelftools
# get mwccarm (pinned in the DS-decomp Discord) into ../st/tools/mwccarm/
# extract your own ROM under extract/, then:
bash build.sh
```

The build fails hard on any deviation; a green `tools/doctor.py` plus the SHA1 match
is the proof. On macOS, mwccarm runs under wine.

## How you can help

Pick an unmatched function (`func_*` in `config/eur/arm9/symbols.txt` without a file
in `src/`), write C for it, verify with `tools/aimatch.py`, and open a pull request —
one function or a small related group per PR. Use only your own legally dumped ROM,
and never commit it or anything derived from it. All code comments are in English.

**Fastest way to start with an AI assistant** — paste this into a Claude Code session:

```
Clone https://github.com/ai-tdd-labs/mkds-decomp and set up the Mario Kart DS
matching-decompilation toolchain on my machine. In order:
1. Read README.md and PLAN.md in the repo.
2. Install Python dependencies: ndspy, capstone, pyelftools.
3. mwccarm cannot be downloaded automatically (DS-decomp Discord, resources
   channel); wait for me to fetch it, then place it per README.
4. Extract my own Mario Kart DS (EUR) cartridge dump under extract/.
5. Confirm the toolchain: bash build.sh must end byte-perfect (SHA1
   ce97d9b43f0d3ca0d48b781983e8a16f6393378f), and re-verify one landed function
   from src/ with tools/aimatch.py.
6. Pick an unmatched function, help me write matching C, verify with
   tools/aimatch.py and a full build.
Use only my own legally dumped ROM. Never commit the ROM or anything extracted from it.
```

## Credits

The workflow is inspired by and shares ideas with
[sm64ds-decomp](https://github.com/tangosdev/sm64ds-decomp) (knowledge notes,
near-miss thinking, link verification). The build rides on
[AetiasHax's dsd / ds-decomp toolkit](https://github.com/AetiasHax/ds-decomp) and
ds-rom. The `coddog_pool.py` family scheduler was inspired by
[Chris Lewis's writeup](https://blog.chrislewis.au/the-long-tail-of-llm-assisted-decompilation/)
on LLM-assisted decompilation. Symbol knowledge builds on the DS decompilation
community; the rule is import knowledge, write code.

## License

The original work in this repo (the C, the tooling, the notes) is released under the
MIT License, see [LICENSE](LICENSE). This applies only to that original work and
grants no rights to any Nintendo material, which is not present here.
