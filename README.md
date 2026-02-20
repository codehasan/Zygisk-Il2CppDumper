# Zygisk-Il2CppDumper
Il2CppDumper with Zygisk, dump il2cpp data at runtime, can bypass protection, encryption and obfuscation.

## Credits
This project is a fork of the original [Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper) by [Perfare](https://github.com/Perfare).

## How to use
1. Install [Magisk](https://t.me/s/magiskalpha) v24 or later and enable Zygisk
2. Build and install module
   - Download the prebuilt module from [Releases](https://github.com/codehasan/Zygisk-Il2CppDumper/releases) or build it yourself
   - Install the module in Magisk and reboot
3. Set target game package name
   ```bash
   # Set the package name of the game you want to dump
   adb shell "echo 'com.example.game' > /data/adb/il2cppdumper/target.txt"
   ```
4. Start the game, `dump.cs` will be generated in the `/data/data/GamePackageName/files/` directory

> **Note:** You can change the target game at any time by modifying `/data/adb/il2cppdumper/target.txt` and restarting the game. No need to rebuild or reinstall the module.

### Advanced: Building from source
If you prefer to build the module yourself:
1. Download the source code
2. Use Android Studio to run the gradle task `:module:assembleRelease` to compile
3. The zip package will be generated in the `out` folder
4. Install the module in Magisk