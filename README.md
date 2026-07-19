# Random Flag

`SoL_RandomFlag` is a folded flag item that a player opens from their hands. After a two-second `Open Flag` action, the server selects a weighted classname from a JSON configuration and replaces the folded item with the selected flag.

The source is written for DayZ 1.29 script APIs and uses the vanilla `Flag_White` model and texture as its no-asset fallback.

## Configuration

The dedicated server creates this file automatically on first start:

```text
$profile:SoLMods/RandomFlagConfig.json
```

The generated file contains the 34 `Flag_` entries currently present in Bohemia's Chernarus, Livonia, and Sakhal Central Economy files. Every default entry has an equal weight of `1.0`.

Additional classnames from loaded mods may be added. Random Flag does not require entries to inherit from `Flag_Base`; it only verifies that each classname exists in `CfgVehicles`, `CfgWeapons`, or `CfgMagazines`.

Restart the server after changing the configuration.

### Weight examples

Weights are relative and do not need to total 100. For example:

```json
{
    "Version": 1,
    "Flags": [
        { "ClassName": "Flag_White", "Weight": 10.0 },
        { "ClassName": "Flag_Chernarus", "Weight": 5.0 },
        { "ClassName": "Flag_Bear", "Weight": 3.0 },
        { "ClassName": "Flag_Pirates", "Weight": 2.0 }
    ]
}
```

The total is 20, so the chances are 50%, 25%, 15%, and 10%. Values of `1, 2, 7` behave exactly like `10, 20, 70`. Decimal weights are allowed. Empty classnames, unavailable classnames, and weights less than or equal to zero are ignored and logged.

## Opening behavior

- `SoL_RandomFlag` must be in the player's hands and must not be ruined.
- The action lasts two seconds and uses `DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM` while standing or crouching.
- Selection and item creation happen on the server.
- DayZ's item-replacement lambda first tries to put the selected item directly into the player's hands.
- If that operation aborts, the mod tries the player's inventory and then the ground at the player's feet.
- The Folded Flag is preserved when configuration is unusable or all creation attempts fail.

## Source layout

```text
config.cpp
mod.cpp
Scripts/
  3_Game/RandomFlag/SoL_RandomFlagConfig.c
  4_World/RandomFlag/Actions/SoL_ActionConstructor.c
  4_World/RandomFlag/Actions/SoL_ActionOpenFlag.c
  4_World/RandomFlag/Entities/SoL_RandomFlag.c
  5_Mission/RandomFlag/SoL_MissionServer.c
Extras/
  RandomFlagConfig.example.json
Data/
  Textures/README.md
```

## Packing and testing

1. Place the source at `P:\RandomFlag`. The included `$PBOPREFIX$` fixes the internal PBO prefix as `RandomFlag`, matching the script paths in `config.cpp`.
2. Pack the source with DayZ Tools Addon Builder into a lower-case `addons` directory.
3. Sign the PBO and place the public key in the mod's lower-case `keys` directory for a production server.
4. Load the packed mod on both the server and client. It adds a custom item and action, so it is not server-only.
5. Spawn `SoL_RandomFlag`, place it in the player's hands, and run `Open Flag`.
6. Check the server script log for messages prefixed with `[Random Flag]`.

A Windows environment with DayZ, DayZ Tools, extracted game data, and `DayZDiag_x64.exe` is required for compilation and in-game verification.

The optional custom-texture workflow is documented in `Data/Textures/README.md`. The initial build deliberately inherits the known-good `Flag_White` appearance.

### Suggested in-game checks

1. Open several Folded Flags with the generated equal-weight configuration.
2. Set all but one entry to weight `0` and confirm the one positive entry is always selected.
3. Add a missing classname and confirm the server logs it while continuing to use valid entries.
4. Temporarily break the JSON syntax and confirm the action preserves the Folded Flag.
5. Fill the player's inventory and confirm the replacement still goes to the hands.
6. Use an item that cannot be placed in the hands or inventory and confirm the ground fallback.
7. Interrupt the action before two seconds and confirm no item is created or consumed.
8. Repeat the test with two clients to check that only the server creates the selected item.

## Optional sound hook

`SoL_RandomFlagReplaceLambda.PlayOptionalOpenSound()` is intentionally empty and contains a commented integration note. A future custom sound should be registered in `CfgSoundShaders`/`CfgSoundSets` and triggered through a client RPC so nearby players can hear it. The base mod requires no sound asset or RPC.
