#!/system/bin/sh

TARGET_DIR="/data/adb/il2cppdumper"

if [ -d "$TARGET_DIR" ]; then
    rm -rf "$TARGET_DIR"
fi
