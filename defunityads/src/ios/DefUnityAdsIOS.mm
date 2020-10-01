#if defined(DM_PLATFORM_IOS)
#include "../private_DefUnityAds.h"
#include "../private_DefUnityCallback.h"

#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

@interface DefUnityAdsDelegate : NSObject<UnityAdsDelegate>
@end

@implementation DefUnityAdsDelegate

-(void)unityAdsReady:(NSString *)placementId {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_IS_READY,(char*)"placementId", (char*)[placementId UTF8String], NULL, 0);
}

-(void)unityAdsDidStart:(NSString *)placementId {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_START,(char*)"placementId", (char*)[placementId UTF8String], NULL, 0);
}

-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_ERROR,(char*)"message", (char*)[message UTF8String], (char*)"error", (int)error);
}

-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_FINISH,(char*)"placementId", (char*)[placementId UTF8String], (char*)"state", (int)state);
}

@end

//Banner:
static UADSBannerView *gBannerView;

@interface DefUnityAdsBannerDelegate: NSObject<UADSBannerViewDelegate>
@end

@implementation DefUnityAdsBannerDelegate
- (void)bannerViewDidLoad:(UADSBannerView *)bannerView {
    gBannerView = bannerView;
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)[bannerView.placementId UTF8String], (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_LOAD);
}

- (void)bannerViewDidClick:(UADSBannerView *)bannerView {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)[bannerView.placementId UTF8String], (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_CLICK);
}

- (void)bannerViewDidLeaveApplication:(UADSBannerView *)bannerView {
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)[bannerView.placementId UTF8String], (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_LEAVE_APP);
}

- (void)bannerViewDidError:(UADSBannerView *)bannerView error:(UADSBannerError *)error{
    dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER_ERROR,(char*)"message", (char*)[[error localizedDescription] UTF8String], (char*)"error", (int)error.code);
}
@end

namespace dmUnityAds {

static UIViewController *uiViewController;
    
void initialize(const char*game_id, bool is_debug) {
    NSString* gameId = [NSString stringWithUTF8String:game_id];
    DefUnityAdsDelegate* unityAds = [[DefUnityAdsDelegate alloc] init];
    [UnityAds initialize:gameId testMode:is_debug ? YES : NO];
    [UnityAds addDelegate:unityAds];
    
    UIWindow* window = dmGraphics::GetNativeiOSUIWindow();
    uiViewController = window.rootViewController;
}

void show(char* placementId) {
    if ((placementId != NULL) && (placementId[0] == '\0')) {
        [UnityAds show:uiViewController];
    }
    else {
        NSString* placementId_s = [NSString stringWithUTF8String:placementId];
        [UnityAds show:uiViewController placementId:placementId_s];
    }
}

void setDebugMode(bool is_debug) {
    BOOL enableDebugMode = is_debug ? YES : NO;
    [UnityAds setDebugMode:enableDebugMode];
}

bool isReady(char* placementId) {
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

bool isSupported() {
    BOOL status = [UnityAds isSupported];
    return status == YES;
}

bool isInitialized() {
    BOOL status = [UnityAds isInitialized];
    return status == YES;
}

bool getDebugMode() {
    BOOL status = [UnityAds getDebugMode];
    return status == YES;
}

char const* getVersion() {
    NSString *version = [UnityAds getVersion];
    const char *version_lua = [version UTF8String];
    return version_lua;
}

int getPlacementState(char* placementId) {
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
static NSMutableArray *constraints;
static DefUnityBannerPosition currentPosition;
static bool isBannerVisible;

static void ApplyBannerPosition() {
    if (gBannerView){
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
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gBannerView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_LEFT:
            case BANNER_POSITION_TOP_LEFT:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gBannerView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_RIGHT:
            case BANNER_POSITION_TOP_RIGHT:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gBannerView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeRight multiplier:1.0 constant:0]];
                break;
            case kUnityAdsBannerPositionNone:
                break;
        }
        // position vertically
        switch (currentPosition) {
            case BANNER_POSITION_CENTER:
                [constraints addObject:[NSLayoutConstraint constraintWithItem:gBannerView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:uiViewController.view attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0]];
                break;
            case BANNER_POSITION_BOTTOM_CENTER:
            case BANNER_POSITION_BOTTOM_LEFT:
            case BANNER_POSITION_BOTTOM_RIGHT:
                if (@available(iOS 11.0, *)) {
                    // we can use the safeAreaLayoutGuide
                    [constraints addObject:[gBannerView.bottomAnchor constraintEqualToAnchor:uiViewController.view.safeAreaLayoutGuide.bottomAnchor]];
                } else {
                    // fall back to anchors
                    [constraints addObject:[gBannerView.bottomAnchor constraintEqualToAnchor:uiViewController.view.bottomAnchor]];
                }
                break;
            case BANNER_POSITION_TOP_CENTER:
            case BANNER_POSITION_TOP_LEFT:
            case BANNER_POSITION_TOP_RIGHT:
                if (@available(iOS 11.0, *)) {
                    // we can use the safeAreaLayoutGuide
                    [constraints addObject:[gBannerView.topAnchor constraintEqualToAnchor:uiViewController.view.safeAreaLayoutGuide.topAnchor]];
                } else {
                    // fall back to anchors
                    [constraints addObject:[gBannerView.topAnchor constraintEqualToAnchor:uiViewController.view.topAnchor]];
                }
                break;
        }
        [uiViewController.view addConstraints:constraints];
    }
}

void loadBanner(char* placementId, int width, int height) {
    if (!gBannerView){
        NSString* placementId_s = [NSString stringWithUTF8String:placementId];
        UADSBannerView *localBannerView = [[UADSBannerView alloc] initWithPlacementId: placementId_s size: CGSizeMake(width, height)];
        localBannerView.delegate = [[DefUnityAdsBannerDelegate alloc] init];
        [localBannerView load];
    }
}

void unloadBanner() {
    hideBanner();
    if (gBannerView){
        [gBannerView release];
        gBannerView = nil;
    }
}

void showBanner() {
    if (gBannerView){
        isBannerVisible = true;
        gBannerView.translatesAutoresizingMaskIntoConstraints = NO;
        [uiViewController.view addSubview:gBannerView];
        ApplyBannerPosition();
    }
}

void hideBanner() {
    if (gBannerView) {
        isBannerVisible = false;
        [gBannerView removeFromSuperview];
    }
}

void setBannerPosition(DefUnityBannerPosition bannerPosition) {
    currentPosition = bannerPosition;
    if (isBannerVisible) {
        ApplyBannerPosition();
    }
}

void InitExtension() {
    isBannerVisible = false;
    setBannerPosition(BANNER_POSITION_TOP_CENTER);
}

void FinalizeExtension() {
    if (constraints){
        [uiViewController.view removeConstraints:constraints];
        [constraints release];
        constraints = nil;
    }
    if (gBannerView) {
        hideBanner();
        [gBannerView release];
        gBannerView = nil;
    }
}

} //namespace

#endif
