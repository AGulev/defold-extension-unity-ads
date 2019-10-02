#if defined(DM_PLATFORM_IOS)
#include "../private_DefUnityAds.h"
#include "../private_DefUnityCallback.h"

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

UIViewController *uiViewController;
UIView *bannerView;

@interface DefUnityAdsDelegate : NSObject<UnityAdsDelegate>
@end

@implementation DefUnityAdsDelegate

-(void)unityAdsReady:(NSString *)placementId {
  DefUnityCallback_add_to_queue((int)TYPE_IS_READY,(char*)"placementId", (char*)[placementId UTF8String], NULL, 0);
}

-(void)unityAdsDidStart:(NSString *)placementId {
  DefUnityCallback_add_to_queue((int)TYPE_DID_START,(char*)"placementId", (char*)[placementId UTF8String], NULL, 0);
}

-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
  DefUnityCallback_add_to_queue((int)TYPE_DID_ERROR,(char*)"message", (char*)[message UTF8String], (char*)"error", (int)error);
}

-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
  DefUnityCallback_add_to_queue((int)TYPE_DID_FINISH,(char*)"placementId", (char*)[placementId UTF8String], (char*)"state", (int)state);
}

@end

@interface DefUnityAdsBannerDelegate: NSObject <UnityAdsBannerDelegate>
@end

@implementation DefUnityAdsBannerDelegate

-(void) unityAdsBannerDidClick: (NSString *) placementId {
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"placementId", (char*)[placementId UTF8String], (char*)"event", (int)BANNER_EVENT_DID_CLICK);
}

-(void) unityAdsBannerDidError: (NSString *) message {
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"message", (char*)[message UTF8String], (char*)"event", (int)BANNER_EVENT_DID_ERROR);
}

-(void) unityAdsBannerDidHide: (NSString *) placementId {
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"placementId", (char*)[placementId UTF8String], (char*)"event", (int)BANNER_EVENT_DID_HIDE);
}

-(void) unityAdsBannerDidShow: (NSString *) placementId {
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"placementId", (char*)[placementId UTF8String], (char*)"event", (int)BANNER_EVENT_DID_SHOW);
}

-(void) unityAdsBannerDidLoad: (NSString *) placementId view: (UIView *) view {
  bannerView = view;
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"placementId", (char*)[placementId UTF8String], (char*)"event", (int)BANNER_EVENT_DID_LOAD);
}

-(void) unityAdsBannerDidUnload: (NSString *) placementId {
  bannerView = nil;
  DefUnityCallback_add_to_queue((int)TYPE_BANNER,(char*)"placementId", (char*)[placementId UTF8String], (char*)"event", (int)BANNER_EVENT_DID_UNLOAD);
}
@end

void DefUnityAds_InitExtension() {

}

void DefUnityAds_Initialize(const char*game_id, bool is_debug) {
  NSString* gameId = [NSString stringWithUTF8String:game_id];
  DefUnityAdsDelegate* unityAds = [[DefUnityAdsDelegate alloc] init];
  DefUnityAdsBannerDelegate* unityBannerAds = [[DefUnityAdsBannerDelegate alloc] init];
  [UnityAdsBanner setDelegate: unityBannerAds];
  [UnityAds initialize:gameId delegate:unityAds testMode:is_debug ? YES : NO];

  UIWindow* window = dmGraphics::GetNativeiOSUIWindow();
  uiViewController = window.rootViewController;
}

void DefUnityAds_Show(char* placementId) {
  if ((placementId != NULL) && (placementId[0] == '\0')) {
    [UnityAds show:uiViewController];
  }
  else {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    [UnityAds show:uiViewController placementId:placementId_s];
  }
}

void DefUnityAds_setDebugMode(bool is_debug) {
  BOOL enableDebugMode = is_debug ? YES : NO;
  [UnityAds setDebugMode:enableDebugMode];
}

bool DefUnityAds_isReady(char* placementId) {
  BOOL status;
  if ((placementId != NULL) && (placementId[0] == '\0')) {
    status = [UnityAds isReady];
  }
  else {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    status = [UnityAds isReady:placementId_s];
  }
  return status == YES;
}

bool DefUnityAds_isSupported() {
  BOOL status = [UnityAds isSupported];
  return status == YES;
}

bool DefUnityAds_isInitialized() {
  BOOL status = [UnityAds isInitialized];
  return status == YES;
}

bool DefUnityAds_getDebugMode() {
  BOOL status = [UnityAds getDebugMode];
  return status == YES;
}

char const* DefUnityAds_getVersion() {
  NSString *version = [UnityAds getVersion];
  const char *version_lua = [version UTF8String];
  return version_lua;
}

int DefUnityAds_getPlacementState(char* placementId) {
  UnityAdsPlacementState state;
  if ((placementId != NULL) && (placementId[0] == '\0')) {
    state =[UnityAds getPlacementState];
  }
  else {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    state =[UnityAds getPlacementState:placementId_s];
  }
  return (int)state;
}

void DefUnityAds_setBannerPosition(int position) {
  [UnityAdsBanner setBannerPosition:(UnityAdsBannerPosition)position];
}

void DefUnityAds_loadBanner(char* placementId) {
  if ((placementId != NULL) && (placementId[0] == '\0')) {
    [UnityAdsBanner loadBanner];
  }
  else {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    [UnityAdsBanner loadBanner:placementId_s];
  }
}

void DefUnityAds_unloadBanner() {
  [UnityAdsBanner destroy];
}

void DefUnityAds_showBanner() {
  if (bannerView){
    [uiViewController.view addSubview:bannerView];
  }
}

void DefUnityAds_hideBanner() {
  if (bannerView) {
    [bannerView removeFromSuperview];
  }
}

#endif
