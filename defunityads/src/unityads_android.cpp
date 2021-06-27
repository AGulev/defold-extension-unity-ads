#if defined(DM_PLATFORM_ANDROID)
#include "unityads_callback_private.h"
#include "unityads_private.h"
#include "com_agulev_defunityads_DefUnityAdsJNI.h"
#include "unityads_jni.h"

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAdsJNI_unityadsAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
  const char* json = env->GetStringUTFChars(jjson, 0);
  dmUnityAds::AddToQueueCallback((dmUnityAds::MessageId)jmsg, json);
  env->ReleaseStringUTFChars(jjson, json);
}

//--------------------------------------------

namespace dmUnityAds {

struct DefUnityAdsClass
{
  jobject                 m_DUADS_JNI;

  jmethodID               m_initialize;
  jmethodID               m_show;
  jmethodID               m_load;
  jmethodID               m_setDebugMode;
  jmethodID               m_isReady;
  jmethodID               m_isSupported;
  jmethodID               m_isInitialized;
  jmethodID               m_getDebugMode;
  jmethodID               m_getVersion;
  jmethodID               m_getPlacementState;
  jmethodID               m_setBannerPosition;
  jmethodID               m_loadBanner;
  jmethodID               m_unloadBanner;
  jmethodID               m_showBanner;
  jmethodID               m_hideBanner;
};

DefUnityAdsClass g_duads;

void Initialize_Ext() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  ClassLoader class_loader = ClassLoader(env);
  jclass cls = class_loader.load("com/agulev/defunityads/DefUnityAds");
  
  g_duads.m_initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;ZZ)V");
  g_duads.m_show = env->GetMethodID(cls, "show", "(Ljava/lang/String;)V");
  g_duads.m_load = env->GetMethodID(cls, "load", "(Ljava/lang/String;)V");
  g_duads.m_setDebugMode = env->GetMethodID(cls, "setDebugMode", "(Z)V");
  g_duads.m_isReady = env->GetMethodID(cls, "isReady", "(Ljava/lang/String;)Z");
  g_duads.m_isSupported = env->GetMethodID(cls, "isSupported", "()Z");
  g_duads.m_isInitialized = env->GetMethodID(cls, "isInitialized", "()Z");
  g_duads.m_getDebugMode = env->GetMethodID(cls, "getDebugMode", "()Z");
  g_duads.m_getVersion = env->GetMethodID(cls, "getVersion", "()Ljava/lang/String;");
  g_duads.m_getPlacementState = env->GetMethodID(cls, "getPlacementState", "(Ljava/lang/String;)I");
  g_duads.m_setBannerPosition = env->GetMethodID(cls, "setBannerPosition", "(Ljava/lang/String;)V");
  g_duads.m_loadBanner = env->GetMethodID(cls, "loadBanner", "(Ljava/lang/String;II)V");
  g_duads.m_unloadBanner = env->GetMethodID(cls, "unloadBanner", "()V");
  g_duads.m_showBanner = env->GetMethodID(cls, "showBanner", "()V");
  g_duads.m_hideBanner = env->GetMethodID(cls, "hideBanner", "()V");

  jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
  g_duads.m_DUADS_JNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, dmGraphics::GetNativeAndroidActivity()));
}

void Initialize(const char*game_id, bool isDebug, bool enablePerPlacementLoad) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring appid = env->NewStringUTF(game_id);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_initialize, appid, isDebug ? JNI_TRUE : JNI_FALSE,
    enablePerPlacementLoad ? JNI_TRUE : JNI_FALSE);
  env->DeleteLocalRef(appid);
}

void Finalize_Ext() {
  UnloadBanner();
}

void Show(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_show, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

void Load(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_load, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

void SetDebugMode(bool is_debug) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setDebugMode, is_debug ? JNI_TRUE : JNI_FALSE);
}

bool IsReady(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring jplacementId = env->NewStringUTF(placementId);
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isReady, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

bool IsSupported() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isSupported);

  return JNI_TRUE == return_value;
}

bool IsInitialized() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isInitialized);

  return JNI_TRUE == return_value;
}

bool GetDebugMode() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_getDebugMode);

  return JNI_TRUE == return_value;
}

char const* GetVersion() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring return_value = (jstring)env->CallObjectMethod(g_duads.m_DUADS_JNI, g_duads.m_getVersion);
  
  const char* new_char = env->GetStringUTFChars(return_value, 0);
  env->DeleteLocalRef(return_value);

  return new_char;
}

int GetPlacementState(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  jint return_value = (jint)env->CallIntMethod(g_duads.m_DUADS_JNI, g_duads.m_getPlacementState, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

static const char *positions[] = { "topleft", "topcenter", 
  "topright", "bottomleft", "bottomcenter", "bottomright", "center"};

void SetBannerPosition(DefUnityBannerPosition position) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jposition = env->NewStringUTF(positions[(int)position]);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setBannerPosition, jposition);
  env->DeleteLocalRef(jposition);
}

void LoadBanner(char* placementId, int width, int height) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_loadBanner, jplacementId, width, height);
  env->DeleteLocalRef(jplacementId);
}

void UnloadBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_unloadBanner);
}

void ShowBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_showBanner);
}

void HideBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_hideBanner);
}

} //namespaces

#endif
