# DLLTweaks

* [Nexus Page](https://www.nexusmods.com/skyrimspecialedition/mods/44044)

### Requirements

* [XMake](https://xmake.io/) [2.8.2+]
* C++23 Compiler (MSVC)

### Features

#### Fixes
* Starting the game as a Nord no longer breaks intended mechanics.
* Player movement speed now does not scale with race height.

#### Tweaks
* Spell absorption cap will no longer exceed *fPlayerMaxResistance*.

## Visual Studio Project
```
xmake project -k vsxmake
```

## Build
```
git submodule submodule --init --recursive

xmake build
```

## Special Credits
[collinswrath](https://github.com/colinswrath) for the following patches: `AbsorbChance`, `PlayerScaleMovement`. Originally found in [Blade And Blunt](https://github.com/colinswrath/BladeAndBlunt).

[alandtse](https://github.com/alandtse) for [AutoTOML](https://github.com/alandtse/AutoTOML).

[Qudix](https://github.com/Qudix) for [CommonLibSSE-NG Template Plugin](https://github.com/Qudix/template-commonlibsse-ng).

[CharmedBaryon](https://github.com/CharmedBaryon) and all the people who contributed to [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG).

## License
[GPL-3.0](LICENSE)
