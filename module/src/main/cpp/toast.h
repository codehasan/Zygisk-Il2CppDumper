//
// Show an Android Toast from native code (any thread).
//

#ifndef ZYGISK_IL2CPPDUMPER_TOAST_H
#define ZYGISK_IL2CPPDUMPER_TOAST_H

#include <string>

// Toast durations, matching android.widget.Toast constants.
constexpr int TOAST_LENGTH_SHORT = 0;
constexpr int TOAST_LENGTH_LONG = 1;

// Display a Toast with the given text. Safe to call from any (detached) native
// thread; if the JavaVM or application context is not yet available the call is
// a no-op. Non-blocking: the work runs on its own short-lived thread.
void show_toast(const std::string &text, int duration = TOAST_LENGTH_SHORT);

#endif //ZYGISK_IL2CPPDUMPER_TOAST_H
