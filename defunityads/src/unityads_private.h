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

void Initialize_Ext();
void Finalize_Ext();

void Initialize(const char*game_id, bool isDebug, bool enablePerPlacementLoad);
void Load(char* placementId);
void Show(char* placementId);
void SetDebugMode(bool is_debug);
void SetBannerPosition(DefUnityBannerPosition position);
void LoadBanner(char* placementId, int width, int height);
void UnloadBanner();
void ShowBanner();
void HideBanner();
void RequestIDFA();

bool IsReady(char* placementId);
bool IsSupported();
bool IsInitialized();
bool GetDebugMode();

char const* GetVersion();
int GetPlacementState(char* placementId);

} //namespace

#endif
