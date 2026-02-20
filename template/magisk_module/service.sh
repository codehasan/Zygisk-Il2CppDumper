#!/sbin/sh

# Package file path
PKG_FILE="/data/local/tmp/il2cpp_package.txt"

# Create package file if it doesn't exist
if [ ! -f "$PKG_FILE" ]; then
    touch "$PKG_FILE"
    chmod 666 "$PKG_FILE"
    echo "com.example.game" > "$PKG_FILE"
fi
