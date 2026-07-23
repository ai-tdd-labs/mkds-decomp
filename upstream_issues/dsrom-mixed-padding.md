# A single `section_padding_value` cannot express Mario Kart DS's mixed padding (0x00 and 0xFF)

## Summary

`ds-rom`'s `RomConfig` exposes one `section_padding_value` and one `file_image_padding_value`. Mario Kart DS (EUR) does **not** pad uniformly: the gaps after the ARM9 block, the overlay table, and between overlay files are `0x00`, while the gaps after ARM7 / FNT / FAT and inside the file image are `0xFF`. No single value reproduces both, so a rebuild leaves ~1.5 KB of gap bytes wrong (whichever value you pick).

## Environment

- **ds-rom version:** as bundled with dsd v0.11.0
- **ROM:** Mario Kart DS (EUR), SHA-1 `ce97d9b43f0d3ca0d48b781983e8a16f6393378f`

## Evidence

With `section_padding_value: 255`, the surviving diffs are exactly the regions the original padded with `0x00`, e.g.:

```
0x00eb528..0x00eb5ff   orig 00..  rebuilt ff..   (after ARM9 / overlay table)
0x0110b2c..0x0110bff   orig 00..  rebuilt ff..   (between overlay files)
```

With `section_padding_value: 0`, the mirror-image set of diffs appears in the `0xFF` regions instead. The two padding conventions coexist in one image.

## Workaround

We post-process the rebuilt ROM: recompute the gap regions from the header/FAT/overlay layout and stamp each gap with the original ROM's byte **only if that gap is uniformly `0x00` or `0xFF`** (a uniformity guard, so real content is never overwritten). This restores a byte-exact image. Happy to share the ~60-line script if useful.

## Suggested fix

Either (a) allow per-section-class padding values in `RomConfig` (arm9 / overlay-table / overlay-files vs arm7 / fnt / fat / file-image), or (b) capture the observed padding bytes per gap during `extract` and replay them on `build`. Option (b) is fully general and needs no schema guessing.

## Why it matters

This is the last obstacle to a byte-exact rebuild of Mario Kart DS EUR after the multiboot-signature and interworking issues are handled. Any retail cart with mixed padding conventions hits the same wall.
