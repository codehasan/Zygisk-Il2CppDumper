#!/system/bin/sh

PKG_FILE="/data/local/tmp/il2cpp_package.txt"

if [ -f "$PKG_FILE" ]; then
    rm "$PKG_FILE"
fi
