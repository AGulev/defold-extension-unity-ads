#include <jni.h>
/* Header for class com_agulev_defunityads_DefUnityAds */

#ifndef _Included_com_agulev_defunityads_DefUnityAds
#define _Included_com_agulev_defunityads_DefUnityAds
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityAdsReady
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsReady
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityAdsStart
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsStart
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityAdsError
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsError
  (JNIEnv *, jclass, jint, jstring);

/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityAdsFinish
 * Signature: (Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsFinish
  (JNIEnv *, jclass, jstring, jint);

//------
  
/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityBannerLoaded
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerLoaded
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityBannerClick
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerClick
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_agulev_defunityads_DefUnityAds
 * Method:    onUnityBannerError
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerError
(JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerDidLeaveApp
* Signature: (Ljava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerDidLeaveApp
(JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
