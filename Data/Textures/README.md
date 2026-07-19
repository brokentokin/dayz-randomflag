# Optional custom texture

The first build of `SoL_RandomFlag` inherits the vanilla `Flag_White` model and texture. No custom texture is required.

To add a reliable custom retexture later:

1. Extract the current `Flag_White` texture with DayZ Tools so the original dimensions, UV placement, alpha channel, and material behavior are preserved.
2. Paint the custom design over that template without moving UV-dependent details.
3. Save the editable source outside the packed PBO and export the game texture as a power-of-two `.paa` file in this directory.
4. Override `hiddenSelectionsTextures[]` on `SoL_RandomFlag` in `config.cpp`, preserving the same number and order of texture entries used by the current vanilla `Flag_White` config.
5. Pack with binarization enabled and inspect both the folded inventory view and the world model in DayZDiag.

Do not add a guessed texture array before checking the extracted current-game config; an incorrect selection count can make the item render with missing or mismatched materials.
