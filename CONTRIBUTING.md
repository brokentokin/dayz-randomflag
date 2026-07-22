# Contributing to Random Flag

Thanks for helping improve Random Flag. Bug reports, feature ideas, documentation corrections, compatibility findings, and pull requests are all welcome.

Random Flag is a small DayZ mod, but changes can affect clients, servers, persistence, the Central Economy, and compatibility with other mods. Please follow the guidance below so contributions are easy to reproduce and review.

## Ways to contribute

- Report a reproducible bug through [GitHub Issues](https://github.com/brokentokin/dayz-randomflag/issues).
- Suggest a feature or configuration improvement.
- Improve installation, packing, Central Economy, or troubleshooting documentation.
- Update verified vanilla flag or economy information after a DayZ release.
- Submit a pull request that fixes or improves the scripts, examples, or Workshop materials.

Search the existing issues and pull requests before opening a new one. For a substantial feature, configuration-schema change, new dependency, or behavior change, opening an issue first is encouraged so the approach can be discussed before a large amount of work is done.

## Reporting a bug

Please include enough information for someone else to reproduce the problem:

- The DayZ version, map, and server platform being used.
- The Random Flag version, release, or commit.
- Whether the problem occurs on the client, server, or both.
- Clear reproduction steps and what you expected to happen.
- What happened instead, including relevant server and client log excerpts.
- Your relevant `RandomFlagConfig.json` entries.
- Other loaded mods that may affect the behavior or supply configured classnames.
- Whether an admin tool, such as Community Online Tools, has instant or accelerated actions enabled.

Look for messages prefixed with `[Random Flag]` in the script log. Include the surrounding error text, but remove passwords, tokens, private server information, and personal filesystem details before posting.

If a configured classname comes from another mod, identify that mod and confirm it is loaded on both the client and server where required.

## Requesting a feature

Describe the problem or server use case before describing a specific implementation. Include examples of the desired configuration and in-game behavior when possible. Please call out anything that could affect existing configuration files, persistence, client/server requirements, or compatibility with other mods.

## Preparing a pull request

Random Flag uses the standard GitHub fork workflow:

1. Fork [`brokentokin/dayz-randomflag`](https://github.com/brokentokin/dayz-randomflag).
2. Clone your fork to your development machine.
3. Create a focused branch from the current `main` branch.
4. Make and test your changes.
5. Push the branch to your fork and open a pull request against this repository's `main` branch.

Example:

```powershell
git clone https://github.com/YOUR-USERNAME/dayz-randomflag.git
cd dayz-randomflag
git switch -c fix/short-description
```

Keep each pull request focused on one fix or feature. Avoid mixing formatting changes, renames, or unrelated cleanup into a functional change.

By submitting a contribution to this repository, you agree to license it under the [DayZ Public License (DPL)](LICENSE).

## Development environment

Script compilation and in-game verification require Windows with:

- DayZ and DayZ Tools installed through Steam.
- Game data extracted or mounted on the DayZ Tools `P:` drive.
- Addon Builder and the appropriate signing tools.
- `DayZDiag_x64.exe` when diagnostic testing is needed.

Place the source at exactly `P:\RandomFlag` when following the repository's packing instructions. In Addon Builder's options, set **Addon prefix** to exactly `RandomFlag`. The included `$PBOPREFIX$` records the intended namespace for compatible packing tools, but contributors must not assume it overrides or replaces Addon Builder's explicit prefix setting. Do not change the internal prefix without also updating every dependent script and asset path and thoroughly testing the packed result.

The mod contains custom scripts and must be loaded by both the client and server. A server-only test is not sufficient.

## Repository layout

| Path | Purpose |
| --- | --- |
| `Scripts/3_Game/` | JSON configuration classes, loading, validation, and weighted selection. |
| `Scripts/4_World/` | Folded Flag entity, synchronized action duration, action registration, and item replacement. |
| `Scripts/5_Mission/` | Server mission initialization. |
| `Extras/` | Example JSON and Central Economy configuration. |
| `Data/Textures/` | Optional retexture guidance. |
| `Workshop/` | Steam Workshop description and thumbnail source artifact. |
| `config.cpp` | Addon and `Tokin_RandomFlag` item configuration. |

Do not commit packed PBOs, signatures, server profiles, generated logs, private keys, or locally generated DayZ Tools output unless a maintainer has specifically requested an artifact for diagnosis.

## Script and configuration guidelines

- Follow the existing Enforce Script formatting and naming style.
- Preserve the `Tokin_` class prefix and the `RandomFlag` PBO/script path unless a change has been discussed first.
- Keep weighted selection and item creation server-authoritative.
- Synchronize server configuration values when they affect client-visible behavior, such as continuous-action timing.
- Preserve the Folded Flag when configuration is unusable or replacement-item creation fails.
- Maintain the hands, inventory, and ground placement fallback order unless the pull request intentionally changes and documents it.
- Treat existing server JSON files as a compatibility requirement. New fields should have safe defaults when omitted.
- Validate external classnames without adding a hard dependency on the mod that supplies them.
- Do not copy code, models, textures, sounds, or other assets from another mod without clear permission and compatible redistribution terms.
- Update `README.md`, `Extras/`, and `Workshop/description.md` when user-facing behavior or configuration changes.

## Economy and classname changes

When updating the default flag list or `types.example.xml`:

- Use authoritative upstream economy files whenever possible.
- Record the DayZ version or upstream commit used for the audit.
- Confirm that every default classname still exists in the relevant DayZ configuration.
- Present economy files as examples and remind server owners to review every value against their own economy and preferences.
- Explain that existing flag entries must be disabled when the example is intended to replace rather than supplement their spawns.

## Testing expectations

Test in proportion to the change. A script or configuration pull request should normally cover the relevant items below:

1. Pack the PBO without Addon Builder or script compilation errors.
2. Load the mod on both a dedicated server and a matching client.
3. Confirm a missing profile configuration generates a valid default JSON file.
4. Confirm existing JSON files that omit newer optional fields retain documented defaults.
5. Spawn `Tokin_RandomFlag`, put it in the player's hands, and complete `Open Flag`.
6. Confirm weighted selection with both equal and deliberately uneven weights.
7. Confirm missing classnames and non-positive weights are ignored without consuming the Folded Flag when no valid entry remains.
8. Confirm malformed JSON does not consume the Folded Flag.
9. Test replacement in hands, inventory fallback, and ground fallback.
10. Test interruption before the action completes.
11. Test the default opening duration, a longer configured duration, and the one-second clamp for values below `1.0`.
12. Repeat relevant behavior with two clients to detect duplicate creation or synchronization problems.

Admin mods can override continuous-action timing. Disable instant or accelerated actions before reporting duration-test results.

For documentation-only changes, verify links, filenames, classnames, JSON examples, XML syntax, and Steam BBCode formatting as applicable.

## Pull request description

A pull request should include:

- A concise summary of the problem and solution.
- A link to the related issue, if one exists.
- Any configuration or compatibility impact.
- Exact tests performed and their results.
- Relevant screenshots or short log excerpts for visual or runtime changes.
- Documentation updates required by the change.

Mark anything that could not be tested. An untested change may still be useful for discussion, but it should not be presented as verified.

## AI-assisted contributions

AI-assisted contributions are welcome when the contributor understands, reviews, and tests the resulting work. Do not submit unreviewed generated code or documentation. Disclose material AI assistance in the pull request, and remain responsible for correctness, licensing, security, and the accuracy of testing claims.

## Community conduct

Be respectful and constructive when reporting issues, reviewing work, or responding to feedback. Assume good intent, keep discussion focused on the project, and give maintainers and contributors time to investigate DayZ-specific behavior that may require in-game reproduction.
