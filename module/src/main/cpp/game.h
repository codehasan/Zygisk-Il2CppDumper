//
// Created by Perfare on 2020/7/4.
//

#ifndef ZYGISK_IL2CPPDUMPER_GAME_H
#define ZYGISK_IL2CPPDUMPER_GAME_H

#include <cstring>
#include <cstdio>
#include "log.h"

#include <cctype>
#include <cstring>
#include <cstdio>

inline const char *GetGamePackageName() {
    static char package_name[256] = {0};
    static bool initialized = false;

    if (!initialized) {
        FILE *fp = fopen("/data/adb/il2cppdumper/target.txt", "r");
        if (fp) {
            if (fgets(package_name, sizeof(package_name), fp)) {
                char *start = package_name;

                while (isspace(static_cast<unsigned char>(*start))) start++;

                char *end = start + strlen(start);
                while (end > start && isspace(static_cast<unsigned char>(*(end - 1)))) end--;
                *end = '\0';

                if (start > package_name) {
                    memmove(package_name, start, end - start + 1);
                }
            }
            fclose(fp);
        }

        if (package_name[0] == '\0') {
            snprintf(package_name, sizeof(package_name), "com.example.game");
        }
        initialized = true;
    }
    return package_name;
}

#define GamePackageName GetGamePackageName()

#endif //ZYGISK_IL2CPPDUMPER_GAME_H
