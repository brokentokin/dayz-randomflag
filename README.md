# HBC Random Flag

`Tokin_RandomFlag` is a HeyBarmby-themed folded flag item that a player opens from their hands. After a configurable `Open Flag` action, the server selects a weighted classname from a JSON configuration and replaces the folded item with the selected flag.

The source is written for DayZ 1.29 script APIs and uses the vanilla `Flag_White` model with a custom HeyBarmby-themed texture for the Folded Flag.

## Configuration

The dedicated server creates this file automatically on first start:

```text
$profile:Tokin/RandomFlagConfig.json
```

The generated file contains the custom `Tokin_HeyBarmbyFlag` and the 34 `Flag_` entries currently present in Bohemia's Chernarus, Livonia, and Sakhal Central Economy files. Every default entry has an equal weight of `1.0`. It also contains `"OpenActionSeconds": 2.0`; set this to change the opening duration. Existing configuration files that omit it use the embedded two-second default. Configured values below `1.0` are clamped to the one-second minimum.

The default file is only generated when no configuration already exists. Servers upgrading from an earlier build must add `{ "ClassName": "Tokin_HeyBarmbyFlag", "Weight": 1.0 }` to their existing `Flags` array manually.

Additional classnames from loaded mods may be added. Random Flag does not require entries to inherit from `Flag_Base`; it only verifies that each classname exists in `CfgVehicles`, `CfgWeapons`, or `CfgMagazines`.

Restart the server after changing the configuration.

### Economy example

[`Extras/types.example.xml`](Extras/types.example.xml) contains an example Central Economy entry for `Tokin_RandomFlag`. Its values are based on Chernarus and Livonia. Treat it as a starting point and review every value against your server's economy and preferences before using it.

If you intend the Folded Flag to replace existing flag spawns, set both `<nominal>0</nominal>` and `<min>0</min>` on every existing flag economy entry you want to replace. Otherwise, Folded Flags will spawn in addition to those flags. Flags already present in persistence may remain until the Central Economy cleans them up normally.

### Weight examples

Weights are relative and do not need to total 100. For example:

```json
{
    "Version": 1,
    "OpenActionSeconds": 2.0,
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

- `Tokin_RandomFlag` must be in the player's hands and must not be ruined.
- The action duration comes from `OpenActionSeconds`, defaults to two seconds, and has a one-second minimum. It uses `DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM` while standing or crouching.
- Selection and item creation happen on the server.
- DayZ's item-replacement lambda first tries to put the selected item directly into the player's hands.
- If that operation aborts, the mod tries the player's inventory and then the ground at the player's feet.
- The Folded Flag is preserved when configuration is unusable or all creation attempts fail.

## Source layout

```text
config.cpp
mod.cpp
CONTRIBUTING.md
LICENSE
Scripts/
  3_Game/RandomFlag/Tokin_RandomFlagConfig.c
  4_World/RandomFlag/Actions/Tokin_ActionConstructor.c
  4_World/RandomFlag/Actions/Tokin_ActionOpenFlag.c
  4_World/RandomFlag/Entities/Tokin_RandomFlag.c
  5_Mission/RandomFlag/Tokin_MissionServer.c
Extras/
  RandomFlagConfig.example.json
  types.example.xml
Data/
  Textures/
    README.md
    heybarmby_randomflag_co.paa
    heybarmby_randomflag_co.png
Workshop/
  description.md
  random-flag-thumbnail-640x360.png
```

## Packing and testing

1. Place the source at `P:\RandomFlag`. The included `$PBOPREFIX$` fixes the internal PBO prefix as `RandomFlag`, matching the script paths in `config.cpp`.
2. Pack the source with DayZ Tools Addon Builder into a lower-case `addons` directory.
3. Sign the PBO and place the public key in the mod's lower-case `keys` directory for a production server.
4. Load the packed mod on both the server and client. It adds a custom item and action, so it is not server-only.
5. Spawn `Tokin_RandomFlag`, place it in the player's hands, and run `Open Flag`.
6. Check the server script log for messages prefixed with `[Random Flag]`.

A Windows environment with DayZ, DayZ Tools, extracted game data, and `DayZDiag_x64.exe` is required for compilation and in-game verification.

The custom texture and its editable PNG source are documented in `Data/Textures/README.md`. The item inherits the known-good `Flag_White` model and overrides its single `camo` texture selection.

### Suggested in-game checks

1. Open several Folded Flags with the generated equal-weight configuration.
2. Set all but one entry to weight `0` and confirm the one positive entry is always selected.
3. Add a missing classname and confirm the server logs it while continuing to use valid entries.
4. Temporarily break the JSON syntax and confirm the action preserves the Folded Flag.
5. Fill the player's inventory and confirm the replacement still goes to the hands.
6. Use an item that cannot be placed in the hands or inventory and confirm the ground fallback.
7. Interrupt the action before its configured duration and confirm no item is created or consumed.
8. Repeat the test with two clients to check that only the server creates the selected item.

Admin tools such as Community Online Tools can accelerate continuous actions. Disable any instant/fast-action feature when verifying the configured action duration.

## License

Copyright 2026 Tokin.

Random Flag is licensed under the [DayZ Public License (DPL)](LICENSE). It may be shared and adapted with attribution for noncommercial use in DayZ. See the license for the complete legally binding terms and warranty disclaimer.
