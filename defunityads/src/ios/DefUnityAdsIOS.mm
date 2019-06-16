#if defined(DM_PLATFORM_IOS)
#include "../private_DefUnityAds.h"
#include "../private_DefUnityCallback.h"

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

UIViewController *uiViewController;

@interface DefUnityAdsDelegate : NSObject<UnityAdsDelegate>
@end

@interface DefUnityAdsDelegate ()
@end

@implementation DefUnityAdsDelegate

-(void)unityAdsReady:(NSString *)placementId {
  DefUnityCallback_lua_unityAdsReady((char*)[placementId UTF8String]);
}

-(void)unityAdsDidStart:(NSString *)placementId {
  DefUnityCallback_lua_unityAdsDidStart((char*)[placementId UTF8String]);
}

-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
  DefUnityCallback_lua_unityAdsDidError((int)error, (char*)[message UTF8String]);
}

-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
  DefUnityCallback_lua_unityAdsDidFinish ((char*)[placementId UTF8String], (int)state);
}

@end

@interface DefUnityAdsBannerDelegate: NSObject <UnityAdsBannerDelegate>
@end

@interface DefUnityAdsBannerDelegate ()
@end

@implementation DefUnityAdsBannerDelegate

-(void) unityAdsBannerDidClick: (NSString *) placementId {
  
}

-(void) unityAdsBannerDidError: (NSString *) message {

}

-(void) unityAdsBannerDidHide: (NSString *) placementId {
}

-(void) unityAdsBannerDidShow: (NSString *) placementId {
}

-(void) unityAdsBannerDidLoad: (NSString *) placementId view: (UIView *) view {
  [uiViewController.view addSubview:view];
}

-(void) unityAdsBannerDidUnload: (NSString *) placementId {
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
  [UnityAdsBanner setBannerPosition:position];
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

#endif
