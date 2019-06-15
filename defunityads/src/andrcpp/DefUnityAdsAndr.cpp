#if defined(DM_PLATFORM_ANDROID)
#include "../private_DefUnityCallback.h"
#include "com_agulev_defunityads_DefUnityAds.h"
#include "jni.h"

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsReady(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  lua_unityAdsReady((char*)ch);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsStart(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  lua_unityAdsDidStart((char*)ch);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsError(JNIEnv *env, jclass jcls, jint type, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  lua_unityAdsDidError((int)type, (char*)ch);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsFinish(JNIEnv *env, jclass jcls, jstring jstr, jint type)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  lua_unityAdsDidFinish((char*)ch, (int)type);
  env->ReleaseStringUTFChars(jstr, ch);
}

//--------------------------------------------

struct DefUnityAdsClass
{
  jobject                 m_DUADS_JNI;

  jmethodID               m_initialize;
  jmethodID               m_show;
  jmethodID               m_setDebugMode;
  jmethodID               m_isReady;
  jmethodID               m_isSupported;
  jmethodID               m_isInitialized;
  jmethodID               m_getDebugMode;
  jmethodID               m_getVersion;
  jmethodID               m_getPlacementState;
};

DefUnityAdsClass g_duads;

void DefUnityAds_InitExtension() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  ClassLoader class_loader = ClassLoader(env);
  jclass cls = class_loader.load("com/agulev/defunityads/DefUnityAds");
  
  g_duads.m_initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;Z)V");
  g_duads.m_show = env->GetMethodID(cls, "show", "(Ljava/lang/String;)V");
  g_duads.m_setDebugMode = env->GetMethodID(cls, "setDebugMode", "(Z)V");
  g_duads.m_isReady = env->GetMethodID(cls, "isReady", "(Ljava/lang/String;)Z");
  g_duads.m_isSupported = env->GetMethodID(cls, "isSupported", "()Z");
  g_duads.m_isInitialized = env->GetMethodID(cls, "isInitialized", "()Z");
  g_duads.m_getDebugMode = env->GetMethodID(cls, "getDebugMode", "()Z");
  g_duads.m_getVersion = env->GetMethodID(cls, "getVersion", "()Ljava/lang/String;");
  g_duads.m_getPlacementState = env->GetMethodID(cls, "getPlacementState", "(Ljava/lang/String;)I");

  jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
  g_duads.m_DUADS_JNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, dmGraphics::GetNativeAndroidActivity()));
}

void DefUnityAds_Initialize(const char*game_id, bool is_debug) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring appid = env->NewStringUTF(game_id);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_initialize, appid, is_debug ? JNI_TRUE : JNI_FALSE);
  env->DeleteLocalRef(appid);
}

void DefUnityAds_Show(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_show, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

void DefUnityAds_setDebugMode(bool is_debug) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setDebugMode, is_debug ? JNI_TRUE : JNI_FALSE);
}

bool DefUnityAds_isReady(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring jplacementId = env->NewStringUTF(placementId);
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isReady, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_isSupported() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isSupported);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_isInitialized() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isInitialized);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_getDebugMode() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_getDebugMode);

  return JNI_TRUE == return_value;
}

char const* DefUnityAds_getVersion() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring return_value = (jstring)env->CallObjectMethod(g_duads.m_DUADS_JNI, g_duads.m_getVersion);
  
  const char* new_char = env->GetStringUTFChars(return_value, 0);
  env->DeleteLocalRef(return_value);

  return new_char;
}

int DefUnityAds_getPlacementState(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  jint return_value = (jint)env->CallIntMethod(g_duads.m_DUADS_JNI, g_duads.m_getPlacementState, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

#endif
