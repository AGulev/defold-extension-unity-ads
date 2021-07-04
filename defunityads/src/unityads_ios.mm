#if defined(DM_PLATFORM_IOS)
#include "unityads_callback_private.h"
#include "unityads_private.h"

#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

#if __has_include(<AppTrackingTransparency/ATTrackingManager.h>)
#import <AppTrackingTransparency/ATTrackingManager.h>
#endif

@interface DefUnityAdsDelegate : NSObject<UnityAdsDelegate>
@end

@interface DefUnityAdsInitializationDelegate : NSObject<UnityAdsInitializationDelegate>
@end

@interface DefUnityAdsBannerDelegate: NSObject<UADSBannerViewDelegate>
@end

@interface DefUnityShowDelegate: NSObject<UnityAdsShowDelegate>
@end

@interface DefUnityAdsLoadDelegate: NSObject<UnityAdsLoadDelegate>
@end

namespace dmUnityAds {

static UIViewController *uiViewController;

void SendSimpleMessage(MessageId msg, id obj) {
    NSError* error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:obj options:(NSJSONWritingOptions)0 error:&error];
    if (jsonData)
    {
        NSString* nsstring = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        AddToQueueCallback(msg, (const char*)[nsstring UTF8String]);
        [nsstring release];
    }
    else
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        [dict setObject:error.localizedDescription forKey:@"error"];
        [dict setObject:[NSNumber numberWithInt:EVENT_JSON_ERROR] forKey:@"event"];
        NSError* error2;
        NSData* errorJsonData = [NSJSONSerialization dataWithJSONObject:dict options:(NSJSONWritingOptions)0 error:&error2];
        if (errorJsonData)
        {
            NSString* nsstringError = [[NSString alloc] initWithData:errorJsonData encoding:NSUTF8StringEncoding];
            AddToQueueCallback(msg, (const char*)[nsstringError UTF8String]);
            [nsstringError release];
        }
        else
        {
            AddToQueueCallback(msg, [[NSString stringWithFormat:@"{ \"error\": \"Error while converting simple message to JSON.\", \"event\": %d }", EVENT_JSON_ERROR] UTF8String]);
        }
    }
}

void SendSimpleMessage(MessageId msg, MessageEvent event) {
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    [dict setObject:[NSNumber numberWithInt:event] forKey:@"event"];
    SendSimpleMessage(msg, dict);
}

void SendSimpleMessage(MessageId msg, MessageEvent event, NSString *key_2, NSString *value_2) {
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    [dict setObject:[NSNumber numberWithInt:event] forKey:@"event"];
    [dict setObject:value_2 forKey:key_2];
    SendSimpleMessage(msg, dict);
}

void SendSimpleMessage(MessageId msg, MessageEvent event, NSString *key_2, int value_2, NSString *key_3, NSString *value_3) {
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    [dict setObject:[NSNumber numberWithInt:event] forKey:@"event"];
    [dict setObject:[NSNumber numberWithInt:value_2] forKey:key_2];
    [dict setObject:value_3 forKey:key_3];
    SendSimpleMessage(msg, dict);
}
    
void Initialize(const char*game_id, bool is_debug, bool enablePerPlacementLoad) {
    NSString* gameId = [NSString stringWithUTF8String:game_id];
    if (!enablePerPlacementLoad) {
        DefUnityAdsDelegate* unityAdsDelegate = [[DefUnityAdsDelegate alloc] init];
        [UnityAds addDelegate:unityAdsDelegate];
    }
    DefUnityAdsInitializationDelegate* unityAdsInitDelegate = [[DefUnityAdsInitializationDelegate alloc] init];
    [UnityAds initialize:gameId testMode:is_debug ? YES : NO enablePerPlacementLoad:enablePerPlacementLoad ? YES : NO initializationDelegate:unityAdsInitDelegate];
    
    UIWindow* window = dmGraphics::GetNativeiOSUIWindow();
    uiViewController = window.rootViewController;
}

void RequestIDFA() {
    if (@available(iOS 14, *))
    {
        [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
            switch (status) {
                case ATTrackingManagerAuthorizationStatusAuthorized:
                    SendSimpleMessage(MSG_IDFA, EVENT_STATUS_AUTORIZED);
                    break;
                case ATTrackingManagerAuthorizationStatusDenied:
                    SendSimpleMessage(MSG_IDFA, EVENT_STATUS_DENIED);
                    break;
                case ATTrackingManagerAuthorizationStatusNotDetermined:
                    SendSimpleMessage(MSG_IDFA, EVENT_STATUS_NOT_DETERMINED);
                    break;
                case ATTrackingManagerAuthorizationStatusRestricted:
                    SendSimpleMessage(MSG_IDFA, EVENT_STATUS_RESTRICTED);
                    break;
            }
        }];
    }
    else
    {
        SendSimpleMessage(MSG_IDFA, EVENT_NOT_SUPPORTED);
    }
}

static DefUnityAdsLoadDelegate* unityLoadDelegate;

void Load(char* placementId) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    if (!unityLoadDelegate) {
        unityLoadDelegate = [[DefUnityAdsLoadDelegate alloc] init];
    }
    [UnityAds load:placementId_s loadDelegate:unityLoadDelegate];
}

static DefUnityShowDelegate* unityShowDelegate;

void Show(char* placementId) {
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    if (!unityShowDelegate) {
        unityShowDelegate = [[DefUnityShowDelegate alloc] init];
    }
    [UnityAds show:uiViewController placementId:placementId_s showDelegate:unityShowDelegate];
}

void SetDebugMode(bool is_debug) {
    BOOL enableDebugMode = is_debug ? YES : NO;
    [UnityAds setDebugMode:enableDebugMode];
}

bool IsReady(char* placementId) {
    BOOL status;
    NSString* placementId_s = [NSString stringWithUTF8String:placementId];
    status = [UnityAds isReady:placementId_s];
    return status == YES;
}

bool IsSupported() {
    BOOL status = [UnityAds isSupported];
    return status == YES;
}

bool IsInitialized() {
    BOOL status = [UnityAds isInitialized];
    return status == YES;
}

bool GetDebugMode() {
    BOOL status = [UnityAds getDebugMode];
    return status == YES;
}

char const* GetVersion() {
    NSString *version = [UnityAds getVersion];
    const char *version_lua = [version UTF8String];
    return version_lua;
}

int GetPlacementState(char* placementId) {
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

//Banner:

static UADSBannerView *gDefVideoAdsBannerView;
static NSMutableArray *constraints;
static DefUnityBannerPosition currentPosition;
static bool isBannerVisible;
static DefUnityAdsBannerDelegate* unityBannerDelegate;

static void ApplyBannerPosition() {
    if (gDefVideoAdsBannerView){
        if (constraints){
            [uiViewController.view removeConstraints:constraints];
            [constraints release];
            constraints = nil;
        }
        constraints = [[NSMutableArray alloc] init];
        // position horizontally
        switch (currentPosition) {
            case BANNER_POSITION_CENTER:
            case BANNER_POSITION_BOTTOM_CENTER:
            case BANNER_POSITION_TOP_CENTER:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gDefVideoAdsBannerView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_LEFT:
            case BANNER_POSITION_TOP_LEFT:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gDefVideoAdsBannerView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_RIGHT:
            case BANNER_POSITION_TOP_RIGHT:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gDefVideoAdsBannerView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeRight multiplier:1.0 constant:0]];
                break;
        }
        // position vertically
        switch (currentPosition) {
            case BANNER_POSITION_CENTER:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gDefVideoAdsBannerView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_CENTER:
            case BANNER_POSITION_BOTTOM_LEFT:
            case BANNER_POSITION_BOTTOM_RIGHT:
                if (@available(iOS 11.0, *)) {
                    // we can use the safeAreaLayoutGuide
                    [constraints addObject:[gDefVideoAdsBannerView.bottomAnchor constraintEqualToAnchor:uiViewController.view.safeAreaLayoutGuide.bottomAnchor]];
                } else {
                    // fall back to anchors
                    [constraints addObject:[gDefVideoAdsBannerView.bottomAnchor constraintEqualToAnchor:uiViewController.view.bottomAnchor]];
                }
                break;
            case BANNER_POSITION_TOP_CENTER:
            case BANNER_POSITION_TOP_LEFT:
            case BANNER_POSITION_TOP_RIGHT:
                if (@available(iOS 11.0, *)) {
                    // we can use the safeAreaLayoutGuide
                    [constraints addObject:[gDefVideoAdsBannerView.topAnchor constraintEqualToAnchor:uiViewController.view.safeAreaLayoutGuide.topAnchor]];
                } else {
                    // fall back to anchors
                    [constraints addObject:[gDefVideoAdsBannerView.topAnchor constraintEqualToAnchor:uiViewController.view.topAnchor]];
                }
                break;
        }
        [uiViewController.view addConstraints:constraints];
    }
}

void LoadBanner(char* placementId, int width, int height) {
    if (!gDefVideoAdsBannerView){
        NSString* placementId_s = [NSString stringWithUTF8String:placementId];
        UADSBannerView *localBannerView = [[UADSBannerView alloc] initWithPlacementId: placementId_s size: CGSizeMake(width, height)];
        if (!unityBannerDelegate) {
            unityBannerDelegate = [[DefUnityAdsBannerDelegate alloc] init];
        }
        localBannerView.delegate = unityBannerDelegate;
        [localBannerView load];
    }
}

void UnloadBanner() {
    HideBanner();
    if (gDefVideoAdsBannerView){
        [gDefVideoAdsBannerView release];
        gDefVideoAdsBannerView = nil;
    }
}

void ShowBanner() {
    if (gDefVideoAdsBannerView){
        isBannerVisible = true;
        gDefVideoAdsBannerView.translatesAutoresizingMaskIntoConstraints = NO;
        [uiViewController.view addSubview:gDefVideoAdsBannerView];
        ApplyBannerPosition();
    }
}

void HideBanner() {
    if (gDefVideoAdsBannerView) {
        isBannerVisible = false;
        [gDefVideoAdsBannerView removeFromSuperview];
    }
}

void SetBannerPosition(DefUnityBannerPosition bannerPosition) {
    currentPosition = bannerPosition;
    if (isBannerVisible) {
        ApplyBannerPosition();
    }
}

void Initialize_Ext() {
    isBannerVisible = false;
    SetBannerPosition(BANNER_POSITION_TOP_CENTER);
}

void Finalize_Ext() {
    if (constraints){
        [uiViewController.view removeConstraints:constraints];
        [constraints release];
        constraints = nil;
    }
    if (gDefVideoAdsBannerView) {
        HideBanner();
        [gDefVideoAdsBannerView release];
        gDefVideoAdsBannerView = nil;
    }
}

} //namespace

@implementation DefUnityAdsBannerDelegate
- (void)bannerViewDidLoad:(UADSBannerView *)bannerView {
    dmUnityAds::gDefVideoAdsBannerView = bannerView;
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_BANNER, dmUnityAds::EVENT_LOADED, @"placement_id", bannerView.placementId);
}

- (void)bannerViewDidClick:(UADSBannerView *)bannerView {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_BANNER, dmUnityAds::EVENT_CLICKED, @"placement_id", bannerView.placementId);
}

- (void)bannerViewDidLeaveApplication:(UADSBannerView *)bannerView {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_BANNER, dmUnityAds::EVENT_LEFT_APPLICATION, @"placement_id", bannerView.placementId);
}

- (void)bannerViewDidError:(UADSBannerView *)bannerView error:(UADSBannerError *)error{
    int code;
    switch (error.code) {
        case UADSBannerErrorCodeUnknown:
            code = dmUnityAds::ERROR_UNKNOWN;
            break;
        case UADSBannerErrorCodeNativeError:
            code = dmUnityAds::ERROR_NATIVE;
            break;
        case UADSBannerErrorCodeWebViewError:
            code = dmUnityAds::ERROR_WEBVIEW;
            break;
        case UADSBannerErrorCodeNoFillError:
            code = dmUnityAds::ERROR_NO_FILL;
            break;
    }
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_BANNER, dmUnityAds::EVENT_SDK_ERROR, @"code", code, @"error", error.localizedDescription);
}
@end

@implementation DefUnityAdsDelegate

-(void)unityAdsReady:(NSString *)placementId {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_LOAD, dmUnityAds::EVENT_LOADED, @"placement_id", placementId);
}

-(void)unityAdsDidStart:(NSString *)placementId {
    // this logic is in UnityAdsShowDelegate
}

-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
    // this logic is in UnityAdsShowDelegate
}

-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
    // this logic is in UnityAdsShowDelegate
}

@end

@implementation DefUnityAdsInitializationDelegate

-(void)initializationComplete {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_INIT, dmUnityAds::EVENT_COMPLETED);
}

-(void)initializationFailed:(UnityAdsInitializationError)error withMessage:(NSString *)message {
    int code;
    switch (error) {
        case kUnityInitializationErrorInternalError:
            code = dmUnityAds::ERROR_INTERNAL;
            break;
        case kUnityInitializationErrorInvalidArgument:
            code = dmUnityAds::ERROR_INVALID_ARGUMENT;
            break;
        case kUnityInitializationErrorAdBlockerDetected:
            code = dmUnityAds::ERROR_AD_BLOCKER_DETECTED;
            break;
    }
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_INIT, dmUnityAds::EVENT_SDK_ERROR, @"code", code, @"error", message);
}

@end

@implementation DefUnityShowDelegate

-(void)unityAdsShowFailed:(NSString *)placementId withError:(UnityAdsShowError)error  withMessage:(NSString *)message {
    int code;
    switch (error) {
        case kUnityShowErrorNotInitialized:
            code = dmUnityAds::ERROR_NOT_INITIALIZED;
            break;
        case kUnityShowErrorNotReady:
            code = dmUnityAds::ERROR_NOT_READY;
            break;
        case kUnityShowErrorVideoPlayerError:
            code = dmUnityAds::ERROR_VIDEO_PLAYER;
            break;
        case kUnityShowErrorInvalidArgument:
            code = dmUnityAds::ERROR_INVALID_ARGUMENT;
            break;
        case kUnityShowErrorNoConnection:
            code = dmUnityAds::ERROR_NO_CONNECTION;
            break;
        case kUnityShowErrorAlreadyShowing:
            code = dmUnityAds::ERROR_ALREADY_SHOWING;
            break;
        case kUnityShowErrorInternalError:
            code = dmUnityAds::ERROR_INTERNAL;
            break;
    }
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_SHOW, dmUnityAds::EVENT_SDK_ERROR, @"code", code, @"error", message);
}

-(void)unityAdsShowStart:(NSString *)placementId {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_SHOW, dmUnityAds::EVENT_START, @"placement_id", placementId);
}

-(void)unityAdsShowClick:(NSString *)placementId {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_SHOW, dmUnityAds::EVENT_CLICKED, @"placement_id", placementId);
}

-(void)unityAdsShowComplete:(NSString *)placementId  withFinishState:(UnityAdsShowCompletionState)state {
    dmUnityAds::MessageEvent event;
    switch (state) {
        case kUnityShowCompletionStateSkipped:
        event = dmUnityAds::EVENT_SKIPPED;
        break;
        case kUnityShowCompletionStateCompleted:
        event = dmUnityAds::EVENT_COMPLETED;
        break;
    }
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_SHOW, event, @"placement_id", placementId);
}

@end

@implementation DefUnityAdsLoadDelegate

-(void)unityAdsAdLoaded:(NSString *)placementId {
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_LOAD, dmUnityAds::EVENT_LOADED, @"placement_id", placementId);
}

-(void)unityAdsAdFailedToLoad:(NSString *)placementId withError:(UnityAdsLoadError)error withMessage:(NSString *)message {
    int code;
    switch (error) {
        case kUnityAdsLoadErrorInitializeFailed:
            code = dmUnityAds::ERROR_NOT_INITIALIZED;
            break;
        case kUnityAdsLoadErrorInternal:
            code = dmUnityAds::ERROR_INTERNAL;
            break;
        case kUnityAdsLoadErrorInvalidArgument:
            code = dmUnityAds::ERROR_INVALID_ARGUMENT;
            break;
        case kUnityAdsLoadErrorNoFill:
            code = dmUnityAds::ERROR_NO_FILL;
            break;
        case kUnityAdsLoadErrorTimeout:
            code = dmUnityAds::ERROR_TIMEOUT;
            break;
    }
    dmUnityAds::SendSimpleMessage(dmUnityAds::MSG_LOAD, dmUnityAds::EVENT_SDK_ERROR, @"code", code, @"error", message);
}

@end

#endif
