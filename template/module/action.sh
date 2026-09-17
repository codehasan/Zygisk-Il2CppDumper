#!/system/bin/sh

PACKAGE_NAME=$(getprop persist.il2cppdumper.package)

if [ -z "$PACKAGE_NAME" ]; then
    setprop persist.il2cppdumper.package "com.example.game"
    PACKAGE_NAME="com.example.game"
fi

printf "Target package: %s\n" "$PACKAGE_NAME"
printf "\nTo change the target game, run:\n"
printf "  setprop persist.il2cppdumper.package com.new.game\n"
