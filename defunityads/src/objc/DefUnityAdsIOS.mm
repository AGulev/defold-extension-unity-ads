#if defined(DM_PLATFORM_IOS)
#include "../DefUnityAds.h"
#include "../DefUnityCallback.h"

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>


@interface DefUnityAdsDelegate : NSObject<UnityAdsDelegate>{
}
@end

@interface DefUnityAdsDelegate ()
@end

@implementation DefUnityAdsDelegate

-(void)unityAdsReady:(NSString *)placementId {
  lua_unityAdsReady((char*)[placementId UTF8String]);
}

-(void)unityAdsDidStart:(NSString *)placementId {
  lua_unityAdsDidStart((char*)[placementId UTF8String]);
}

-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
  lua_unityAdsDidError((int)error, (char*)[message UTF8String]);
}

-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
  lua_unityAdsDidFinish ((char*)[placementId UTF8String], (int)state);
}

@end

UIViewController *uiViewController;

void DefUnityAds_Initialize(const char*game_id, bool is_debug) {
  NSString* gameId = [NSString stringWithUTF8String:game_id];
  DefUnityAdsDelegate* unityAds = [[DefUnityAdsDelegate alloc] init];
  [UnityAds initialize:gameId delegate:unityAds testMode:is_debug ? YES : NO];

  UIWindow* window = dmGraphics::GetNativeiOSUIWindow();
  uiViewController = window.rootViewController;
}

void DefUnityAds_Show(char* placementId) {
  if (placementId != NULL) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    [UnityAds show:uiViewController placementId:placementId_s];
  }
  else{
    [UnityAds show:uiViewController];
  }
}

void DefUnityAds_setDebugMode(bool is_debug) {
  BOOL enableDebugMode = is_debug ? YES : NO;
  [UnityAds setDebugMode:enableDebugMode];
}

bool DefUnityAds_isReady(char* placementId) {
  BOOL status;
  if (placementId != NULL) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    status = [UnityAds isReady:placementId_s];
  }
  else{
    status = [UnityAds isReady];
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
  if (placementId != NULL) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    state =[UnityAds getPlacementState:placementId_s];
  }
  else{
    state =[UnityAds getPlacementState];
  }
  return (int)state;
}

#endif
