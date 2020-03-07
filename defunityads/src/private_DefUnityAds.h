#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

enum DefUnityAdsPlacementState
{
  PLACEMENT_STATE_READY,
  PLACEMENT_STATE_NOT_AVAILABLE,
  PLACEMENT_STATE_DISABLED,
  PLACEMENT_STATE_WAITING,
  PLACEMENT_STATE_NO_FILL
};

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

void DefUnityAds_InitExtension();
void DefUnityAds_FinalizeExtension();

void DefUnityAds_Initialize(const char*game_id, bool is_debug);
void DefUnityAds_Show(char* placementId);
void DefUnityAds_setDebugMode(bool is_debug);
void DefUnityAds_setBannerPosition(DefUnityBannerPosition position);
void DefUnityAds_loadBanner(char* placementId, int width, int height);
void DefUnityAds_unloadBanner();
void DefUnityAds_showBanner();
void DefUnityAds_hideBanner();

bool DefUnityAds_isReady(char* placementId);
bool DefUnityAds_isSupported();
bool DefUnityAds_isInitialized();
bool DefUnityAds_getDebugMode();

char const* DefUnityAds_getVersion();
int DefUnityAds_getPlacementState(char* placementId);

#endif
