//
// Show an Android Toast from native code (any thread).
//

#include "toast.h"
#include "log.h"
#include <jni.h>
#include <dlfcn.h>
#include <thread>
#include <unistd.h>

static JavaVM *GetJavaVM() {
    static JavaVM *cached = nullptr;
    if (cached) {
        return cached;
    }
    void *libart = dlopen("libart.so", RTLD_NOW);
    if (!libart) {
        return nullptr;
    }
    auto JNI_GetCreatedJavaVMs = (jint (*)(JavaVM **, jsize, jsize *)) dlsym(
            libart, "JNI_GetCreatedJavaVMs");
    if (!JNI_GetCreatedJavaVMs) {
        return nullptr;
    }
    JavaVM *vms[1];
    jsize num = 0;
    if (JNI_GetCreatedJavaVMs(vms, 1, &num) == JNI_OK && num > 0) {
        cached = vms[0];
    }
    return cached;
}

// Quit the toast thread's Looper (held as a global ref) after a short delay so
// that Looper.loop() returns instead of blocking the thread forever.
static void quit_looper_later(JavaVM *vm, jobject looper_global) {
    sleep(4);
    JNIEnv *env = nullptr;
    if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK) {
        return;
    }
    jclass looperClass = env->FindClass("android/os/Looper");
    if (looperClass) {
        jmethodID quitSafely = env->GetMethodID(looperClass, "quitSafely", "()V");
        if (quitSafely) {
            env->CallVoidMethod(looper_global, quitSafely);
        }
        env->DeleteLocalRef(looperClass);
    }
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
    env->DeleteGlobalRef(looper_global);
    vm->DetachCurrentThread();
}

static void toast_worker(JavaVM *vm, std::string text) {
    JNIEnv *env = nullptr;
    if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK) {
        return;
    }

    jclass looperClass = env->FindClass("android/os/Looper");
    if (!looperClass) {
        vm->DetachCurrentThread();
        return;
    }
    // This detached thread has no Looper yet; Toast needs one.
    jmethodID prepare = env->GetStaticMethodID(looperClass, "prepare", "()V");
    env->CallStaticVoidMethod(looperClass, prepare);
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }

    // context = ActivityThread.currentApplication()
    jclass activityThread = env->FindClass("android/app/ActivityThread");
    jmethodID currentApplication = activityThread ? env->GetStaticMethodID(
            activityThread, "currentApplication", "()Landroid/app/Application;") : nullptr;
    jobject context = currentApplication ? env->CallStaticObjectMethod(
            activityThread, currentApplication) : nullptr;
    if (context == nullptr) {
        LOGW("toast: no application context, dropping: %s", text.c_str());
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
        vm->DetachCurrentThread();
        return;
    }

    jstring jtext = env->NewStringUTF(text.c_str());
    jclass toastClass = env->FindClass("android/widget/Toast");
    jmethodID makeText = toastClass ? env->GetStaticMethodID(
            toastClass, "makeText",
            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;") : nullptr;
    if (makeText) {
        // 1 == Toast.LENGTH_LONG
        jobject toast = env->CallStaticObjectMethod(toastClass, makeText, context, jtext, 1);
        if (toast) {
            jmethodID show = env->GetMethodID(toastClass, "show", "()V");
            env->CallVoidMethod(toast, show);
        }
    }
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }

    // Pump the Looper so the Toast is actually rendered, then have a helper
    // thread quit it so this thread can exit cleanly.
    jmethodID myLooper = env->GetStaticMethodID(looperClass, "myLooper",
                                                "()Landroid/os/Looper;");
    jobject looper = env->CallStaticObjectMethod(looperClass, myLooper);
    if (looper) {
        jobject looper_global = env->NewGlobalRef(looper);
        std::thread(quit_looper_later, vm, looper_global).detach();
        jmethodID loop = env->GetStaticMethodID(looperClass, "loop", "()V");
        env->CallStaticVoidMethod(looperClass, loop);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
        }
    }

    vm->DetachCurrentThread();
}

void show_toast(const std::string &text) {
    JavaVM *vm = GetJavaVM();
    if (!vm) {
        LOGW("toast: no JavaVM, dropping: %s", text.c_str());
        return;
    }
    std::thread(toast_worker, vm, text).detach();
}
