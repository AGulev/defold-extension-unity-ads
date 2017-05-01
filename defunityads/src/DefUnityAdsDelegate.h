#pragma once

#if defined(DM_PLATFORM_IOS)
#include <Foundation/Foundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

@protocol DispatchToLuaDelegate

-(void)dispatchUnityAdsReady:(NSString *)placementId;
-(void)dispatchUnityAdsDidStart:(NSString *)placementId;
-(void)dispatchUnityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message;
-(void)dispatchUnityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state;

@end

@interface DefUnityAdsDelegate : UIViewController<UnityAdsDelegate>

@property (strong, nonatomic) id<DispatchToLuaDelegate> delegate;

@end



#endif
