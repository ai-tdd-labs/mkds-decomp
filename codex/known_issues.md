# known_issues

## 2026-07-19 — func_0202dc68 THUMB reconstruction

Hypothesis: matching the ROM requires a direct two-branch expression tree over
`data_02174e44`, with a `0x30` normal-record stride and a low-byte-indexed
`0x230` extra-record stride. Compiler verification is delegated to the external
harness because local Wine and Docker execution are out of scope.
