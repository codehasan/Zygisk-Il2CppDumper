<div align="center">

# Zygisk‑Il2CppDumper

**Dump Il2Cpp metadata from a running game — past encryption, obfuscation, and packing.**

[![Platform](https://img.shields.io/badge/platform-Android-3DDC84?logo=android&logoColor=white)](#requirements)
[![Zygisk](https://img.shields.io/badge/Zygisk-module-orange)](#requirements)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)
[![Release](https://img.shields.io/github/v/release/codehasan/Zygisk-Il2CppDumper?label=download)](https://github.com/codehasan/Zygisk-Il2CppDumper/releases/latest)

</div>

---

## Features

From the original: runtime dumping of Il2Cpp metadata to a readable `dump.cs`, on arm64/armeabi‑v7a (and x86_64/x86 via houdini).

This fork adds:

- 🔧 **Switch targets without rebuilding** — the game package is read at runtime from a system property (`persist.il2cppdumper.package`); point it at any game and restart.
- 🔢 **Const value dumping** — literal fields emit their real values for every primitive and `string`, not just enums.
- 🌊 **Streaming output** — the dump is written incrementally, so large games dump with a small memory footprint.
- ⏱️ **Runtime‑readiness polling** — replaces a fixed `sleep(5)` with bounded polling until the runtime is actually ready, fixing early‑load failures.
- 🛡️ **Hardened native path** — fragile syscalls are checked and fail gracefully instead of crashing.
- 🖥️ **WebUI for fast target switching** — set the target package from a simple page in KernelSU/APatch, no ADB or shell needed; shows the current target live.
- 🖲️ **Root‑manager action button** — shows and helps set the current target; a boot service seeds a default.

---

## Requirements

- A Zygisk‑capable root solution with Zygisk **enabled**:
  - **Magisk** (v24+), or
  - **KernelSU** / **APatch** with **ZygiskNext**.
- The target game must be an **Il2Cpp**‑built Unity app.

> [!IMPORTANT]
> **Game crashes on launch?** It likely detects root. Turn **Enforce DenyList OFF**, install [**Shamiko**](https://github.com/LSPosed/LSPosed.github.io/releases), and add the game to the DenyList — this hides root while keeping the module loaded.

---

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
> You can also confirm the current target from the module's **action** button in your root manager.

---

## Building from source

1. Clone or download the source.
2. In Android Studio, run the Gradle task `:module:assembleRelease`.
3. The flashable zip is produced in the `out/` folder.
4. Flash it in your root manager and reboot.

---

## Credits

A fork of the original [Zygisk‑Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper) by [Perfare](https://github.com/Perfare). All the original runtime‑dumping groundwork is theirs — this fork builds on it with the features listed above.

## License

Released under the [MIT License](LICENSE).
