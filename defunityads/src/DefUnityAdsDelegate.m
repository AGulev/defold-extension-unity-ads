#if defined(DM_PLATFORM_IOS)

#include "DefUnityAdsDelegate.h"

@implementation DefUnityAdsDelegate

- (void)didReceiveMemoryWarning {
    NSLog(@"didReceiveMemoryWarning\n");
}

- (void)unityAdsReady:(NSString *)placementId{
    [self.delegate dispatchUnityAdsReady:placementId];
}

- (void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message{
    [self.delegate dispatchUnityAdsDidError:error withMessage:message];
}

- (void)unityAdsDidStart:(NSString *)placementId{
    [self.delegate dispatchUnityAdsDidStart:placementId];
}

- (void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state{
    [self.delegate dispatchUnityAdsDidFinish:placementId withFinishState:state];
}

@end
#endif
