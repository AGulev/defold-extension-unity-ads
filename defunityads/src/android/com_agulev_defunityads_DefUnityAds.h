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
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerLoaded
  (JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerUnloaded
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerUnloaded
  (JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerShow
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerShow
(JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerClick
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerClick
(JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerHide
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerHide
(JNIEnv *, jclass, jint, jstring);

/*
* Class:     com_agulev_defunityads_DefUnityAds
* Method:    onUnityBannerError
* Signature: (ILjava/lang/String;)V
*/
JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerError
(JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
