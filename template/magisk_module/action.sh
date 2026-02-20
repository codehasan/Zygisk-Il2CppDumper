#!/sbin/sh

# Package file path
PKG_FILE="/data/local/tmp/il2cpp_package.txt"

# Create package file if it doesn't exist
if [ ! -f "$PKG_FILE" ]; then
    touch "$PKG_FILE"
fi

# Set permissions so everyone can read and write
chmod 666 "$PKG_FILE"

# Write default package if file is empty or newly created
if [ ! -s "$PKG_FILE" ]; then
    echo "com.example.game" > "$PKG_FILE"
fi

# Print status
if [ -f "$PKG_FILE" ]; then
    ui_print "Package file created at: $PKG_FILE"
    ui_print "Permissions set to 666 (read/write for all)"
    ui_print "You can now edit the file to set your target package"
else
    ui_print "Failed to create package file"
    exit 1
fi
