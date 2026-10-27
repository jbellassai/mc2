# Open questions (player questions to answer from the code)

Status key: **answered** (with evidence), **partial**, **open**.

1. **Pearl plate vs Methreal armor** — open. Only the armor *name* table is located (`_w_armor` DS:3CCA: Leather armor, Ring mail, Chain mail, Elven chain, Dwarven chain, Bro…). The armor stat table (the `c_armor` value each gives, weight, who can wear) is not yet found; `LOCTYPE.pearlsw` (+58) suggests pearl plate has a per-location switch (availability or event). Look in the item/`_ItemPrt` data and `DoUse`/equip code.
2. **Why magic skill never tops out** — answered (combat.md, *Skill advancement*). Caps come from `_maxtbl`: magic cap is 99 for a Wizard, 75 for Human and Elf, 0 for Halfling/Dwarf/Orc. The per-success improvement chance is `base + (50−skill)/4` below 50 and `base − (skill−50)/2` above, floored at 1 %, so a Wizard keeps creeping toward 99 and never visibly stops. TODO: confirm the base chance table and check camp *learn* (P93) uses the same cap.
3. **Clothing vs weather formula** — open. Weather states are `_w_weather` DS:424E: Clear, Overcast, Fog, Rain, Thunderstorm, Snow, Blizzard, Freezing, Gale; globals `_weather` DS:4D05, `_tempert` DS:4D07. The effect on the party (fatigue? energy?) and the clothing modifier are not yet traced — start from writers of `_tempert` in the calendar/`CalUpd` code (P01 wilderness).
4. **Is Elvenspun clothing worth it** — open, depends on 3.
5. **Rescuing party members who go missing** — open. Not yet seen in code; candidates: KNPC/`resids` sub-tables and the location programs' event flags (`_events`, `FindBit`).
6. **Where was Lucas on July 1** — open. NPC schedules live in the location D-file sub-tables (`knpcptr`, `resids`, `peopr`) whose semantics are TODO (formats.md); once decoded this is a table lookup.
7. **What is rope used for** — partial. The generic item handler (`FFRE` module, label `USEROPE` 0c2f:074E) is the shared "nothing happens" path with shovel, pick, horn, orb, scrolls, …: these items only act inside a location program that checks for them. Search the `P0x` overlays for item 'rope' (item number TBD from the item name table at DS:3DA6) to find the scripted uses.
