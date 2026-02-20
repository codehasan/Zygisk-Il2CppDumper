#!/system/bin/sh

TARGET_DIR="/data/adb/il2cppdumper"
TARGET_FILE="$TARGET_DIR/target.txt"

if [ ! -d "$TARGET_DIR" ]; then
    mkdir -p "$TARGET_DIR"
fi

if [ ! -f "$TARGET_FILE" ]; then
    touch "$TARGET_FILE"
    chmod 666 "$TARGET_FILE"
    echo "com.example.game" > "$TARGET_FILE"
fi
