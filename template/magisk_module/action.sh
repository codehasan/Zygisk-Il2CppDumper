#!/system/bin/sh

PKG_DIR="/data/local/tmp"
PKG_FILE="$PKG_DIR/il2cpp_package.txt"

if [ ! -d "$PKG_DIR" ]; then
    mkdir -p "$PKG_DIR" || {
        printf "Failed to create directory: $PKG_DIR"
        exit 1
    }
fi

if [ ! -f "$PKG_FILE" ]; then
    touch "$PKG_FILE" || {
        printf "Failed to create file: $PKG_FILE"
        exit 1
    }
fi

chmod 666 "$PKG_FILE"

if [ ! -s "$PKG_FILE" ]; then
    echo "com.example.game" > "$PKG_FILE"
fi

if [ -f "$PKG_FILE" ]; then
    printf "Package file created at: $PKG_FILE"
    printf "Permissions set to 666 (read/write for all)"
    printf "You can now edit the file to set your target package"
else
    printf "Failed to create package file"
    exit 1
fi
