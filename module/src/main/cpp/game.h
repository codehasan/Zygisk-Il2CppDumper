//
// Created by Perfare on 2020/7/4.
//

#ifndef ZYGISK_IL2CPPDUMPER_GAME_H
#define ZYGISK_IL2CPPDUMPER_GAME_H

#include <cstring>
#include <cstdio>
#include "log.h"

#include <cctype>
#include <sys/system_properties.h>

inline const char *GetGamePackageName() {
    static char package_name[256] = {0};
    static bool initialized = false;

    if (!initialized) {
        __system_property_get("persist.il2cppdumper.package", package_name);

        // Fallback to debug property if persist is not set
        if (package_name[0] == '\0') {
            __system_property_get("debug.il2cppdumper.package", package_name);
        }

        // Default fallback if no property is set
        if (package_name[0] == '\0') {
            snprintf(package_name, sizeof(package_name), "com.example.game");
        }
        initialized = true;
    }
    return package_name;
}

#define GamePackageName GetGamePackageName()

#endif //ZYGISK_IL2CPPDUMPER_GAME_H
