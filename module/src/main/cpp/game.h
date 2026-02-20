//
// Created by Perfare on 2020/7/4.
//

#ifndef ZYGISK_IL2CPPDUMPER_GAME_H
#define ZYGISK_IL2CPPDUMPER_GAME_H

#include <cstring>
#include <cstdio>

// Read package name from /data/local/tmp/il2cpp_package.txt
// If file doesn't exist or is empty, use the default package name
inline const char* GetGamePackageName() {
    static char package_name[256] = {0};
    static bool initialized = false;

    if (!initialized) {
        FILE *fp = fopen("/data/local/tmp/il2cpp_package.txt", "r");
        if (fp) {
            if (fgets(package_name, sizeof(package_name), fp)) {
                // Remove trailing newline
                size_t len = strlen(package_name);
                if (len > 0 && (package_name[len - 1] == '\n' || package_name[len - 1] == '\r')) {
                    package_name[len - 1] = '\0';
                }
                if (len > 1 && package_name[len - 2] == '\r') {
                    package_name[len - 2] = '\0';
                }
                if (strlen(package_name) > 0) {
                    fclose(fp);
                    initialized = true;
                    return package_name;
                }
            }
            fclose(fp);
        }
        // Fallback to default
        strcpy(package_name, "com.example.game");
        initialized = true;
    }
    return package_name;
}

#define GamePackageName GetGamePackageName()

#endif //ZYGISK_IL2CPPDUMPER_GAME_H
