#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

namespace dmUnityAds {
  
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

void InitExtension();
void FinalizeExtension();

void initialize(const char*game_id, bool is_debug);
void show(char* placementId);
void setDebugMode(bool is_debug);
void setBannerPosition(DefUnityBannerPosition position);
void loadBanner(char* placementId, int width, int height);
void unloadBanner();
void showBanner();
void hideBanner();

bool isReady(char* placementId);
bool isSupported();
bool isInitialized();
bool getDebugMode();

char const* getVersion();
int getPlacementState(char* placementId);

} //namespace

#endif
