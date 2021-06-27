#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>
/* Header for class com_agulev_defunityads_DefUnityAdsJNI */

#ifndef COM_AGULEV_DEFUNITYADS_DEFUNITYADSJNI_H
#define COM_AGULEV_DEFUNITYADS_DEFUNITYADSJNI_H
#ifdef __cplusplus
extern "C" {
    #endif
    /*
    * Class:     com_agulev_defunityads_DefUnityAdsJNI
    * Method:    unityadsAddToQueue_first_arg
    * Signature: (ILjava/lang/String;I)V
    */
    JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAdsJNI_unityadsAddToQueue
    (JNIEnv *, jclass, jint, jstring);

    #ifdef __cplusplus
}
#endif
#endif

#endif