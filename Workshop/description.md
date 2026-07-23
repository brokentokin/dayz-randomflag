[h1]HBC Random Flag[/h1]
HBC Random Flag adds a lootable HeyBarmby-themed "Folded Flag" item that can become one of several different flags once opened. This allows you to keep flags relatively rare in the economy while allowing for a large number of flag variants.

To use, place the "Folded Flag" in your hands and perform the “Open Flag” action. An item from a configurable weighted list will then replace the Folded Flag.
[h2]Features[/h2]
[list]
[*]Folded Flag item allows you to control flag spawn rates, even with a large number of possible flag variants.
[*]Weighted random selection controlled by a JSON configuration. Make some flags common and others ultra rare.
[*]Includes the custom HeyBarmby flag and 34 vanilla DayZ flag classnames by default; add classnames from other mods or if vanilla changes, or remove classnames to take them out of the selection pool.
[*]Cut the HeyBarmby flag into three matching HeyBarmby armbands using DayZ's normal flag crafting action.
[*]"Open Flag" duration is configurable. Default is two seconds, and has a one-second minimum if configured to be less than 1.0.
[/list]
[h2]Installation[/h2]
HBC Random Flag is a client mod.

Add the following classname to your types (a sample is included in the extras folder).
[code]Tokin_RandomFlag[/code]

The example types entry is based on Chernarus and Livonia. Review each value and adjust it to your server's economy and preferences before using it.

If you intend the Folded Flag to replace existing flag spawns, set both the nominal and minimum values to [code]0[/code] on every existing flag types entry you want to replace. Otherwise, Folded Flags will spawn in addition to those flags.

Detailed packing, installation, configuration, weighting examples, and troubleshooting information are available in the repo README:

https://github.com/brokentokin/dayz-randomflag/tree/heybarmby
[h2]Configuration[/h2]
If you didn't pre-seed a configuration file, it will be automatically generated on first boot at:

[code]$profile:Tokin/RandomFlagConfig.json[/code]

Each configured entry contains a classname and weight. Higher weights make that entry more likely to be selected.

The generated configuration includes the custom HeyBarmby flag at weight [code]1.0[/code]. Existing configuration files are not overwritten during upgrades, so add this entry manually if your configuration predates the HeyBarmby flag:

[code]{ "ClassName": "Tokin_HeyBarmbyFlag", "Weight": 1.0 }[/code]

[b]HeyBarmby flag classname:[/b]

[code]Tokin_HeyBarmbyFlag[/code]

[b]HeyBarmby armband classname:[/b]

[code]Armband_Tokin_HeyBarmby[/code]

Set [code]OpenActionSeconds[/code] to control the opening duration. If it is omitted, Random Flag uses two seconds. Values below [code]1.0[/code] are clamped to the one-second minimum.

You must restart the server anytime you change the configuration.
[h2]Compatibility Note[/h2]
Admin tools that enable instant or accelerated actions may override the configured opening time.

Classnames supplied by other mods will only work when the mod providing those items is also installed and loaded.
[h2]Contributing[/h2]
Community contributions are welcome. GitHub users can report bugs or request features through Issues, and code or documentation improvements can be submitted as pull requests. Please read the contribution guide before getting started:

https://github.com/brokentokin/dayz-randomflag/blob/main/CONTRIBUTING.md
[h2]Repacking[/h2]
[list]
[*]Feel free to add this to your own server pack.
[*]I hate mod sprawl. If you have improvements or additional features/changes, please consider contributing to this project vs. forking your own as described above so that all may benefit without adding "yet another mod".
[/list]
[h2]Credits[/h2]
The legend Zenarchist for his many DayZ modding YouTube videos and mod scaffolding template.

[h2]AI Disclosure[/h2]
AI tools were used to assist with the development and documentation of this mod. The resulting code, functionality, and documentation have been reviewed, tested, and improved by humans.
