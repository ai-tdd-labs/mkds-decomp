# `dsd delink` omits `$t` mapping symbol after an inline jump-table, breaking BLX resolution on rebuild

## Summary

When a Thumb function contains an **inline jump table** (a `$d` data island followed by more Thumb code in the *same* function), `dsd delink` does not emit a resuming `$t` mapping symbol at the point where code resumes after the table. On rebuild, `mwldarm`'s `-interworking` pass then reads the resumed code region as **data**, and emits a plain `BL` where the ROM has a `BLX` (Thumb→ARM interworking call). The rebuilt binary differs from the ROM at those call sites.

Branch targets get a mapping symbol; **jump-table-adjacent code-resume points do not**.

## Environment

- **dsd version:** v0.11.0
- **Game:** Mario Kart DS (EUR), analyzed with `--all-mapping-symbols`
- **Toolchain:** mwccarm 1.2/sp2p3 (mwldarm) under Wine, macOS arm64

## Concrete case

In ARM9 main, function region around `0x020cbb10` (Thumb) contains a dispatch with an inline table. Disassembly around the resume point:

```
020cbf74:  movs r0, #5
020cbf76:  movs r1, #0x1f
020cbf78:  bl   #0x20ccc74        ; thumb_call
020cbf7c:  movs r0, #0
020cbf7e:  blx  #0x20cbabc        ; thumb_call_arm  <-- ROM has BLX
020cbf82:  movs r0, #1
020cbf84:  blx  #0x20cc10c        ; thumb_call_arm to an ARM function
```

`0x020cc10c` (`SetB488_B2`) is an **ARM** function; the ROM therefore encodes the call at `0x020cbf84` as `BLX`. After a preceding `$d` island, dsd leaves no `$t` at `0x020cbf74`, so mwldarm treats `0x020cbf74..` as data and does not apply the Thumb→ARM `BLX` transform — it emits `BL`. Result: 6 differing bytes at those call sites versus the ROM.

## Workaround

Adding a manual mapping label at the resume point fixes it:

```
.L_020cbf74 kind:label(thumb) addr:0x020cbf74
```

With this label present, mwldarm sees the region as Thumb code, resolves the interworking calls, and the region rebuilds byte-identical.

## Suggested fix

When delinking, emit a resuming `$t`/`$a` mapping symbol at the address immediately following an inline jump table / `$d` island whenever the containing function's mode implies code resumes there (the relocation kinds `thumb_call*` at those sites already prove the caller mode). This mirrors the mapping symbols already emitted at branch targets.

## Why it matters

This blocks a fully byte-matching rebuild of any overlay-swap / jump-table-heavy game (Mario Kart DS here). It's cheap to detect from the existing relocation table.
