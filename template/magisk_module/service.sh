#!/system/bin/sh

PKG_DIR="/data/local/tmp"
PKG_FILE="$PKG_DIR/il2cpp_package.txt"

if [ ! -d "$PKG_DIR" ]; then
    mkdir -p "$PKG_DIR"
fi

if [ ! -f "$PKG_FILE" ]; then
    touch "$PKG_FILE"
    chmod 666 "$PKG_FILE"
    echo "com.example.game" > "$PKG_FILE"
fi
