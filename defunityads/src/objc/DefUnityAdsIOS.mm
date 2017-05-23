#if defined(DM_PLATFORM_IOS)
#include "DefUnityAdsIOS.h"
#include "../DefUnityCallback.h"

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>


@interface DefUnityAdsDelegate : UIViewController<UnityAdsDelegate>{
}
@end

@interface DefUnityAdsDelegate ()
@end

@implementation DefUnityAdsDelegate

-(void)didReceiveMemoryWarning {
    NSLog(@"didReceiveMemoryWarning\n");
}

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

DefUnityAdsDelegate *unityAds;

void DefUnityAds_Initialize(const char*game_id, bool is_debug) {
    NSString* gameId = [NSString stringWithUTF8String:game_id];
    
    UIView *view = dmGraphics::GetNativeiOSUIView();
    unityAds = [[DefUnityAdsDelegate alloc] init];
    unityAds.view.bounds = view.bounds;
    [view addSubview:unityAds.view];
    
    [UnityAds initialize:gameId delegate:unityAds testMode:is_debug?YES:NO];
}

void DefUnityAds_Show(char* placementId) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    if ([placementId_s length] != 0){
        [UnityAds show:unityAds placementId:placementId_s];
    }
    else{
        [UnityAds show:unityAds];
    }
}

void DefUnityAds_setDebugMode(bool is_debug) {
    BOOL enableDebugMode = is_debug ? YES : NO;
    [UnityAds setDebugMode:enableDebugMode];
}

bool DefUnityAds_isReady(char* placementId) {
    BOOL status;
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    if ([placementId_s length] != 0){
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
#endif