# Optional custom texture

The first build of `Tokin_RandomFlag` inherits the vanilla `Flag_White` model and texture. No custom texture is required.

To add a reliable custom retexture later:

1. Extract the current `Flag_White` texture with DayZ Tools so the original dimensions, UV placement, alpha channel, and material behavior are preserved.
2. Paint the custom design over that template without moving UV-dependent details.
3. Save the editable source outside the packed PBO and export the game texture as a power-of-two `.paa` file in this directory.
4. Override `hiddenSelectionsTextures[]` on `Tokin_RandomFlag` in `config.cpp`, preserving the same number and order of texture entries used by the current vanilla `Flag_White` config.
5. Pack with binarization enabled and inspect both the folded inventory view and the world model in DayZDiag.

Do not add a guessed texture array before checking the extracted current-game config; an incorrect selection count can make the item render with missing or mismatched materials.

## Adding a custom flag reward

To make the same artwork one of the flags that the Folded Flag can reveal, define a separate config-only class that inherits directly from `Flag_White`:

```cpp
class YourTag_CustomFlag : Flag_White
{
    scope = 2;
    displayName = "Custom Flag";
    descriptionShort = "A custom flag.";
    hiddenSelectionsTextures[] =
    {
        "RandomFlag\Data\Textures\your_flag_co.paa"
    };
};
```

Then:

1. Add the custom classname to `CfgPatches.units[]`.
2. Add the classname and its desired weight to the server's `Flags` array in `RandomFlagConfig.json`.
3. Restart the server after changing the JSON configuration.
4. Test the item in inventory and on a flagpole.

Inherit the reward from `Flag_White`, not `Tokin_RandomFlag`. The Folded Flag intentionally clears its inventory slots and receives the `Open Flag` behavior, while a reward flag should retain vanilla flagpole compatibility.

The extracted DayZ 1.29 configuration defines one `camo` hidden selection and one texture slot for this flag model. Recheck `Flag_Base` and `Flag_White` after future DayZ updates before relying on that selection structure.
