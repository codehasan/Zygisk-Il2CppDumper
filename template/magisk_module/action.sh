#!/system/bin/sh

TARGET_DIR="/data/adb/il2cppdumper"
TARGET_FILE="$TARGET_DIR/target.txt"

if [ ! -d "$TARGET_DIR" ]; then
    mkdir -p "$TARGET_DIR" || {
        printf "Failed to create directory: $TARGET_DIR\n"
        exit 1
    }
fi

if [ ! -f "$TARGET_FILE" ]; then
    touch "$TARGET_FILE" || {
        printf "Failed to create file: $TARGET_FILE\n"
        exit 1
    }
fi

chmod 666 "$TARGET_FILE"

if [ ! -s "$TARGET_FILE" ]; then
    echo "com.example.game" > "$TARGET_FILE"
fi

printf "Target file at: $TARGET_FILE\n"
printf "Current content: "
cat "$TARGET_FILE"
printf "\n"
