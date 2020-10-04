#if defined(DM_PLATFORM_ANDROID)
#include "../private_DefUnityCallback.h"
#include "../private_DefUnityAds.h"
#include "com_agulev_defunityads_DefUnityAds.h"
#include "jni.h"

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsReady(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_IS_READY,(char*)"placementId", (char*)ch, NULL, 0);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsStart(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_START,(char*)"placementId", (char*)ch, NULL, 0);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsError(JNIEnv *env, jclass jcls, jint type, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_ERROR,(char*)"message", (char*)ch, (char*)"error", (int)type);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsFinish(JNIEnv *env, jclass jcls, jstring jstr, jint type)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_DID_FINISH,(char*)"placementId", (char*)ch, (char*)"state", (int)type);
  env->ReleaseStringUTFChars(jstr, ch);
}

//----

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerLoaded(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)ch, (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_LOAD);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerClick(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)ch, (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_CLICK);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerError(JNIEnv *env, jclass jcls, jint type, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER_ERROR,(char*)"message", (char*)ch, (char*)"error", (int)type);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityBannerDidLeaveApp(JNIEnv *env, jclass jcls, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_BANNER,(char*)"placementId", (char*)ch, (char*)"event", (int)dmUnityAds::BANNER_EVENT_DID_LEAVE_APP);
  env->ReleaseStringUTFChars(jstr, ch);
}

//----

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsInitializationError(JNIEnv *env, jclass jcls, jint type, jstring jstr)
{
  const char* ch = env->GetStringUTFChars(jstr, 0);
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_INIT_ERROR,(char*)"message", (char*)ch, (char*)"error", (int)type);
  env->ReleaseStringUTFChars(jstr, ch);
}

JNIEXPORT void JNICALL Java_com_agulev_defunityads_DefUnityAds_onUnityAdsInitialized(JNIEnv *env, jclass jcls)
{
  dmUnityAds::AddToQueue((int)dmUnityAds::TYPE_INITIALIZED, NULL, NULL, NULL, 0);
}

//--------------------------------------------

namespace dmUnityAds {

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
  jmethodID               m_setBannerPosition;
  jmethodID               m_loadBanner;
  jmethodID               m_unloadBanner;
  jmethodID               m_showBanner;
  jmethodID               m_hideBanner;
};

DefUnityAdsClass g_duads;

void InitExtension() {
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
  g_duads.m_setBannerPosition = env->GetMethodID(cls, "setBannerPosition", "(Ljava/lang/String;)V");
  g_duads.m_loadBanner = env->GetMethodID(cls, "loadBanner", "(Ljava/lang/String;II)V");
  g_duads.m_unloadBanner = env->GetMethodID(cls, "unloadBanner", "()V");
  g_duads.m_showBanner = env->GetMethodID(cls, "showBanner", "()V");
  g_duads.m_hideBanner = env->GetMethodID(cls, "hideBanner", "()V");

  jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
  g_duads.m_DUADS_JNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, dmGraphics::GetNativeAndroidActivity()));
}

void initialize(const char*game_id, bool is_debug) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring appid = env->NewStringUTF(game_id);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_initialize, appid, is_debug ? JNI_TRUE : JNI_FALSE);
  env->DeleteLocalRef(appid);
}

void FinalizeExtension() {
  unloadBanner();
}

void show(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_show, jplacementId);
  env->DeleteLocalRef(jplacementId);
}

void setDebugMode(bool is_debug) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setDebugMode, is_debug ? JNI_TRUE : JNI_FALSE);
}

bool isReady(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring jplacementId = env->NewStringUTF(placementId);
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isReady, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

bool isSupported() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isSupported);

  return JNI_TRUE == return_value;
}

bool isInitialized() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_isInitialized);

  return JNI_TRUE == return_value;
}

bool getDebugMode() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jboolean return_value = (jboolean)env->CallBooleanMethod(g_duads.m_DUADS_JNI, g_duads.m_getDebugMode);

  return JNI_TRUE == return_value;
}

char const* getVersion() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;
  
  jstring return_value = (jstring)env->CallObjectMethod(g_duads.m_DUADS_JNI, g_duads.m_getVersion);
  
  const char* new_char = env->GetStringUTFChars(return_value, 0);
  env->DeleteLocalRef(return_value);

  return new_char;
}

int getPlacementState(char* placementId) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  jint return_value = (jint)env->CallIntMethod(g_duads.m_DUADS_JNI, g_duads.m_getPlacementState, jplacementId);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

static const char *positions[] = { "topleft", "topcenter", 
  "topright", "bottomleft", "bottomcenter", "bottomright", "center"};

void setBannerPosition(DefUnityBannerPosition position) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jposition = env->NewStringUTF(positions[(int)position]);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_setBannerPosition, jposition);
  env->DeleteLocalRef(jposition);
}

void loadBanner(char* placementId, int width, int height) {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  jstring jplacementId = env->NewStringUTF(placementId);
  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_loadBanner, jplacementId, width, height);
  env->DeleteLocalRef(jplacementId);
}

void unloadBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_unloadBanner);
}

void showBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_showBanner);
}

void hideBanner() {
  ThreadAttacher attacher;
  JNIEnv *env = attacher.env;

  env->CallVoidMethod(g_duads.m_DUADS_JNI, g_duads.m_hideBanner);
}

} //namespaces

#endif
