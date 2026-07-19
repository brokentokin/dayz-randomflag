[h1]Random Flag[/h1]

Random Flag adds a single lootable “Folded Flag” item that can become one of many different flags.

Place the Folded Flag in your hands and perform the “Open Flag” action. An item from a configurable weighted list replaces the Folded Flag, and gives the selected item to the player.

This allows server owners to keep flags relatively rare in the economy without filling the loot tables with many individual flag classnames.

[h2]Features[/h2]

[list]
[*]Single Folded Flag item for use in the server economy allows you to keep flags rare even with a huge pool of possible flags.
[*]Weighted random selection controlled by a JSON configuration. Make some flags common and others rare.
[*]Includes 34 vanilla DayZ flag classnames by default; add other classnames from other mods or if vanilla changes.
[*]Opening duration is configurable, defaults to two seconds, and has a one-second minimum.
[*]Attempts to place the selected item in the player’s hands. Will fall back to the player’s inventory and then the ground if necessary
[*]Preserves the Folded Flag if the configuration is unusable or item creation fails
[/list]

[h2]Installation[/h2]

Random Flag adds a custom item and action, so the mod must be loaded by both the server and client (aka Client Mod).

Server owners are responsible for adding [code]Tokin_RandomFlag[/code] to their economy (a sample is included in the Extras folder).

The sample is designed to replace the combined vanilla flag spawn target. When using it, set both the nominal and minimum values to [code]0[/code] for every vanilla [code]Flag_*[/code] entry in your mission economy. Otherwise Folded Flags will spawn in addition to the vanilla flags.

Namalsk server owners should note that its regular and hardcore missions use separate economy files. Apply the changes to the mission edition your server loads; see the README for the map-specific details.

Detailed packing, installation, configuration, weighting examples, and troubleshooting information are available in the repo README:

https://github.com/brokentokin/dayz-randomflag

[h2]Configuration[/h2]

On first boot after installing, if you didn't pre-seed a configuration file, it will be automatically generated at:

[code]$profile:Tokin/RandomFlagConfig.json[/code]

Each configured entry contains a classname and weight. Higher weights make that entry more likely to be selected.

Set [code]OpenActionSeconds[/code] to control the opening duration. If it is omitted, Random Flag uses two seconds. Values below [code]1.0[/code] are clamped to the one-second minimum.

You may add vanilla classnames or items supplied by other mods. While Random Flag is intended to be used for flags, it does not explicitly check whether a configured classname is actually a flag so you should be able to use any item you'd like.

[b]Folded Flag classname:[/b]

[code]Tokin_RandomFlag[/code]

Restart the server after changing the configuration.

[h2]Compatibility Note[/h2]

Admin tools that enable instant or accelerated actions may override the configured opening time.

Classnames supplied by other mods will only work when the mod providing those items is also installed and loaded.

[h2]AI Disclosure[/h2]

AI tools were used to assist with the development and documentation of this mod. The resulting code, functionality, and documentation have been reviewed, tested, and improved by humans.
