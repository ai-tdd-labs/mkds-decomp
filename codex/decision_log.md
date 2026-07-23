# decision_log

## 2026-07-19 — func_0202dc68 candidate shape

Used the ROM's two explicit paths rather than names inferred from the function's
callers. The normal path loads `+0x814`, maps the course ID, and indexes the
`+0x8bc` records by `0x30`; the extra path subtracts `+0x80c`, narrows the
`+0x894` table entry to `u8`, and indexes `+0x8c0` by `0x230`. All five emitted
extern names are verified in EUR `symbols.txt`; every other pool word is a
literal offset or stride.

The jump-table compiler fingerprint for MWCCARM 1.2/base is absent, so no
sub-version change is indicated; retain the default 1.2/sp2p3 assumption.
