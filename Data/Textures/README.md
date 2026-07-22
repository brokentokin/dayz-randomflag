# HeyBarmby custom texture

`Tokin_RandomFlag` and the flagpole-compatible `Tokin_HeyBarmbyFlag` inherit the vanilla `Flag_White` model and override its single `camo` hidden-selection texture with:

```text
RandomFlag\Data\Textures\heybarmby_randomflag_co.paa
```

The editable 512 x 256 RGBA source is `heybarmby_randomflag_co.png`. When changing it:

1. Preserve the source dimensions, aspect ratio, and alpha channel.
2. Export it through TexView as `heybarmby_randomflag_co.paa`.
3. Replace the PAA in this directory without changing its filename.
4. Pack with binarization enabled.
5. Inspect the Folded Flag in inventory, in the player's hands, and on the ground in DayZDiag.

The hidden-selection structure was verified against the DayZ 1.29 `DZ_Gear_Camping` configuration. Recheck the parent `Flag_Base` and `Flag_White` definitions if a future DayZ update changes the model or its selections.
