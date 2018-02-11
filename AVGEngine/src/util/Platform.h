#pragma once

// 所有平台标识宏：
// AVG_APPLE        任何 Apple 设备（包含 iOS 与 macOS）
// AVG_IOS          iOS 设备
// AVG_MACOS        macOS（OS X）设备
// AVG_WINDOWS      WIN32 设备
// AVG_ANDROID      Android 设备
// AVG_DESKTOP      桌面设备（包含 macOS、WIN32 与 其他 *NIX 桌面设备）
// AVG_LINUX        Linux 设备（不包含 Android）
// AVG_UNIX         *NIX 设备（包含 Linux 与 macOS）

#ifdef __APPLE__
    #define AVG_APPLE
#elif __ANDROID__
    #define AVG_ANDROID
#elif _WIN32
    #define AVG_WINDOWS
#endif

#if defined(AVG_UNIVERSAL_DESKTOP) || defined(AVG_WINDOWS)
    #define AVG_DESKTOP
#endif

#ifdef AVG_APPLE
    #ifdef AVG_DESKTOP
        #define AVG_MACOS
    #else
        #define AVG_IOS
    #endif
#endif

#if defined(AVG_ANDROID) || defined (AVG_IOS)
    #define AVG_MOBILE
#endif

