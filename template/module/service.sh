#!/system/bin/sh

if [ -z "$(getprop persist.il2cppdumper.package)" ]; then
    setprop persist.il2cppdumper.package "com.example.game"
fi
