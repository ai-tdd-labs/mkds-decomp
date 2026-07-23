# Run 20260719_174057

- Goal: Reconstruct `func_0202dc68` as a MWCCARM 1.2 THUMB byte-match candidate.
- Command(s): `../st/.venv/bin/python -c '... capstone ...'` over `extract/eur/arm9/arm9.bin`, base `0x02000000`, addr `0x0202dc68`, size `0x8c`; symbol and relocation lookups with `rg`.
- Artifacts: `/Users/chrislamark/projects/recomp/nds_recompiler/ai-assisted-decomp/mkds/ai/permuter_out/terra_0202dc68.c`; `/Users/chrislamark/projects/recomp/nds_recompiler/ai-assisted-decomp/mkds/config/eur/arm9/symbols.txt`.
- Result: static checks passed: C syntax, all five external symbols, literal-pool decode, and `tools/doctor.py`. Byte equality remains unverified because the local oracle requires Wine or Docker.
- Next action: external harness runs `tools/aimatch.py` with the default MWCCARM 1.2/sp2p3 backend and reports its literal `RESULT` line.
