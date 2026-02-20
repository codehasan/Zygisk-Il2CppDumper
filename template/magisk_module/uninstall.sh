#!/sbin/sh

# Package file path
PKG_FILE="/data/local/tmp/il2cpp_package.txt"

# Remove the package file if it exists
if [ -f "$PKG_FILE" ]; then
    rm "$PKG_FILE"
fi
