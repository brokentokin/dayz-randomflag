# HeyBarmby custom texture

`Tokin_RandomFlag` and the flagpole-compatible `Tokin_HeyBarmbyFlag` inherit the vanilla `Flag_White` model and override its single `camo` hidden-selection texture with:

```text
RandomFlag\Data\Textures\heybarmby_randomflag_co.paa
```

`Armband_Tokin_HeyBarmby` inherits the vanilla `Armband_ColorBase` model. Its ground selection and eight male/female, large/small worn selections all use the same texture above. No custom P3D, model configuration, or material is required.

The editable 512 x 256 RGBA source is `heybarmby_randomflag_co.png`. When changing it:

1. Preserve the source dimensions, aspect ratio, and alpha channel.
2. Export it through TexView as `heybarmby_randomflag_co.paa`.
3. Replace the PAA in this directory without changing its filename.
4. Pack with binarization enabled.
5. Inspect the Folded Flag and HeyBarmby Flag in inventory, in the player's hands, on the ground, and on a flagpole in DayZDiag.
6. Inspect the HeyBarmby Armband on the ground and on male and female characters, with and without torso clothing.

The hidden-selection structures were verified against the DayZ 1.29 `DZ_Gear_Camping` and `DZ_Characters_Tops` configurations. Recheck the parent flag and armband definitions if a future DayZ update changes their models or selections.
