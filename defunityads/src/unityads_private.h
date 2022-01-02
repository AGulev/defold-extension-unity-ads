#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

namespace dmUnityAds {

enum DefUnityBannerPosition
{
    BANNER_POSITION_TOP_LEFT,
    BANNER_POSITION_TOP_CENTER,
    BANNER_POSITION_TOP_RIGHT,
    BANNER_POSITION_BOTTOM_LEFT,
    BANNER_POSITION_BOTTOM_CENTER,
    BANNER_POSITION_BOTTOM_RIGHT,
    BANNER_POSITION_CENTER
};

void Initialize_Ext();
void Finalize_Ext();

void Initialize(const char*game_id, bool isDebug);
void Load(char* placementId);
void Show(char* placementId);
void SetDebugMode(bool is_debug);
void SetBannerPosition(DefUnityBannerPosition position);
void LoadBanner(char* placementId, int width, int height);
void UnloadBanner();
void ShowBanner();
void HideBanner();
void RequestIDFA();
void ActivateApp();

bool IsSupported();
bool IsInitialized();
bool GetDebugMode();

char const* GetVersion();

} //namespace

#endif
