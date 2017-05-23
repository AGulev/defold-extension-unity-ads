#pragma once
#if defined(DM_PLATFORM_ANDROID)
#include <dmsdk/sdk.h>

extern void DefUnityAds_Initialize(const char*game_id, bool is_debug);
extern void DefUnityAds_Show(char* placementId);
extern void DefUnityAds_setDebugMode(bool is_debug);

extern bool DefUnityAds_isReady(char* placementId);
extern bool DefUnityAds_isSupported();
extern bool DefUnityAds_isInitialized();
extern bool DefUnityAds_getDebugMode();

extern char const* DefUnityAds_getVersion();
#endif