<div align="center">

# Zygisk‑Il2CppDumper

**Dump Il2Cpp metadata from a running game — past encryption, obfuscation, and packing.**

[![Platform](https://img.shields.io/badge/platform-Android-3DDC84?logo=android&logoColor=white)](#requirements)
[![Zygisk](https://img.shields.io/badge/Zygisk-module-orange)](#requirements)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
[![Release](https://img.shields.io/github/v/release/codehasan/Zygisk-Il2CppDumper?label=download)](https://github.com/codehasan/Zygisk-Il2CppDumper/releases/latest)

</div>

## Features

**Original:** Runtime Il2Cpp metadata dumping to `dump.cs` on arm64/armeabi-v7a (and x86/x86_64 via houdini).

**This fork adds:**

- 🔧 **Dynamic target switching** — Change games via `persist.il2cppdumper.package` without rebuilding the module.
- 🔢 **Const value dumping** — Extracts actual literal values for all primitives and strings, not just enums.
- 🌊 **Streaming output** — Incremental writes for a low memory footprint on large games.
- ⏱️ **Runtime polling** — Dynamically waits for the runtime instead of a fixed delay, fixing early-load failures.
- 🛡️ **Hardened native path** — Fragile syscalls fail gracefully instead of crashing.
- 🖥️ **WebUI** — Switch targets directly via KernelSU/APatch without ADB or shell.
- 🖲️ **Root-manager integration** — Action button to view/set targets, with a seeded boot default.

## Requirements

- A Zygisk‑capable root solution with Zygisk **enabled**:
  - **Magisk** (v24+), or
  - **KernelSU** / **APatch** with **ZygiskNext**.
- The target game must be an **Il2Cpp**‑built Unity app.

> [!IMPORTANT]
> **Game crashes on launch?** It likely detects root. Turn **Enforce DenyList OFF**, install [**Shamiko**](https://github.com/LSPosed/LSPosed.github.io/releases), and add the game to the DenyList — this hides root while keeping the module loaded.

## Usage

**1. Install the module**

Download the latest build from [Releases](https://github.com/codehasan/Zygisk-Il2CppDumper/releases/latest) (or [build it yourself](#building-from-source)), flash it in your root manager, and reboot.

**2. Set the target game package**

Via ADB:

```bash
adb shell "setprop persist.il2cppdumper.package com.example.game"
```

…from a root shell on the device:

```bash
setprop persist.il2cppdumper.package com.example.game
```

…or, on **KernelSU / APatch**, open the module's **WebUI**, type the package name, and tap **Save** — the page also shows the current target.

**3. Launch the game**

Start the game and let it finish loading. The dump is written to:

```
/data/data/<GamePackageName>/files/dump.cs
```

> [!TIP]
> **Changing the target is instant.** Set the property to a new package and restart that game — no rebuild, no reinstall.
> ```bash
> setprop persist.il2cppdumper.package com.new.game
> ```

## Building from source

1. Clone or download the source.
2. In Android Studio, run the Gradle task `:module:assembleRelease`.
3. The flashable zip is produced in the `out/` folder.
4. Flash it in your root manager and reboot.

## Credits

A fork of the original [Zygisk‑Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper) by [Perfare](https://github.com/Perfare). All the original runtime‑dumping groundwork is theirs — this fork builds on it with the features listed above.

## License

Released under the [MIT License](LICENSE).
