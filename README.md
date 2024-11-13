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
* Concentration spells that costs more (per second) than the actor's total magicka amount can no longer be casted.
* Jump height while sneaking is reduced (disabled by default).

#### Compatibility
* Tested on Skyrim Special Edition 1.5.97.0 and 1.6.1170.0

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
[Styyx](https://github.com/Styyx1) for the following tweaks: `Tweaks::SneakJumpHeight`.

[collinswrath](https://github.com/colinswrath) for the following patches: `Fixes::ScaleMovementSpeed`, `Tweaks::AbsorptionChance`. Originally found in [Blade And Blunt](https://github.com/colinswrath/BladeAndBlunt).

[Qudix](https://github.com/Qudix) for [CommonLibSSE-NG Template Plugin](https://github.com/Qudix/template-commonlibsse-ng).

[CharmedBaryon](https://github.com/CharmedBaryon) and all the people who contributed to [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG).

## License
[GPL-3.0](LICENSE)
