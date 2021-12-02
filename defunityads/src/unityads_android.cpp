#if defined(DM_PLATFORM_ANDROID)
#include <dmsdk/dlib/android.h>

#include "unityads_callback_private.h"
#include "unityads_private.h"
#include "com_agulev_defunityads_DefUnityAdsJNI.h"

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAdsJNI_unityadsAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmUnityAds::AddToQueueCallback((dmUnityAds::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

//--------------------------------------------

namespace dmUnityAds {

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}

static bool CallBoolMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method);
    return JNI_TRUE == return_value;
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
}

static bool CallBoolMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
    return JNI_TRUE == return_value;
}

struct DefUnityAdsClass
{
    jobject                 m_DUADS_JNI;

    jmethodID               m_initialize;
    jmethodID               m_show;
    jmethodID               m_load;
    jmethodID               m_setDebugMode;
    jmethodID               m_isSupported;
    jmethodID               m_isInitialized;
    jmethodID               m_getDebugMode;
    jmethodID               m_getVersion;
    jmethodID               m_setBannerPosition;
    jmethodID               m_loadBanner;
    jmethodID               m_unloadBanner;
    jmethodID               m_showBanner;
    jmethodID               m_hideBanner;
    jmethodID               m_requestIDFA;
};

DefUnityAdsClass g_duads;

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com/agulev/defunityads/DefUnityAdsJNI");
    
    g_duads.m_initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;Z)V");
    g_duads.m_show = env->GetMethodID(cls, "show", "(Ljava/lang/String;)V");
    g_duads.m_load = env->GetMethodID(cls, "load", "(Ljava/lang/String;)V");
    g_duads.m_setDebugMode = env->GetMethodID(cls, "setDebugMode", "(Z)V");
    g_duads.m_isSupported = env->GetMethodID(cls, "isSupported", "()Z");
    g_duads.m_isInitialized = env->GetMethodID(cls, "isInitialized", "()Z");
    g_duads.m_getDebugMode = env->GetMethodID(cls, "getDebugMode", "()Z");
    g_duads.m_getVersion = env->GetMethodID(cls, "getVersion", "()Ljava/lang/String;");
    g_duads.m_setBannerPosition = env->GetMethodID(cls, "setBannerPosition", "(Ljava/lang/String;)V");
    g_duads.m_loadBanner = env->GetMethodID(cls, "loadBanner", "(Ljava/lang/String;II)V");
    g_duads.m_unloadBanner = env->GetMethodID(cls, "unloadBanner", "()V");
    g_duads.m_showBanner = env->GetMethodID(cls, "showBanner", "()V");
    g_duads.m_hideBanner = env->GetMethodID(cls, "hideBanner", "()V");
    g_duads.m_requestIDFA = env->GetMethodID(cls, "requestIDFA", "()V");

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_duads.m_DUADS_JNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize(const char*game_id, bool isDebug)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring appid = env->NewStringUTF(game_id);
    env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_initialize, appid, isDebug ? JNI_TRUE : JNI_FALSE);
    env->DeleteLocalRef(appid);
}

void Finalize_Ext()
{
    UnloadBanner();
}

void Show(char* placementId)
{
    CallVoidMethodChar(g_duads.m_DUADS_JNI, g_duads.m_show, placementId);
}

void Load(char* placementId)
{
    CallVoidMethodChar(g_duads.m_DUADS_JNI, g_duads.m_load, placementId);
}

void SetDebugMode(bool is_debug)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    
    env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setDebugMode, is_debug ? JNI_TRUE : JNI_FALSE);
}

bool IsSupported()
{
    return CallBoolMethod(g_duads.m_DUADS_JNI, g_duads.m_isSupported);
}

bool IsInitialized()
{
    return CallBoolMethod(g_duads.m_DUADS_JNI, g_duads.m_isInitialized);
}

bool GetDebugMode()
{
    return CallBoolMethod(g_duads.m_DUADS_JNI, g_duads.m_getDebugMode);
}

char const* GetVersion()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    
    jstring return_value = (jstring)env->CallObjectMethod(g_duads.m_DUADS_JNI, g_duads.m_getVersion);
    
    const char* new_char = env->GetStringUTFChars(return_value, 0);
    env->DeleteLocalRef(return_value);

    return new_char;
}

static const char *positions[] = { "topleft", "topcenter", 
    "topright", "bottomleft", "bottomcenter", "bottomright", "center"};

void SetBannerPosition(DefUnityBannerPosition position)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jposition = env->NewStringUTF(positions[(int)position]);
    env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setBannerPosition, jposition);
    env->DeleteLocalRef(jposition);
}

void LoadBanner(char* placementId, int width, int height)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jplacementId = env->NewStringUTF(placementId);
    env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_loadBanner, jplacementId, width, height);
    env->DeleteLocalRef(jplacementId);
}

void UnloadBanner()
{
    CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_unloadBanner);
}

void ShowBanner()
{
    CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_showBanner);
}

void HideBanner()
{
    CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_hideBanner);
}

void RequestIDFA()
{
    CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_requestIDFA);
}

} //namespaces

#endif
