#if defined(DM_PLATFORM_ANDROID)
#include "../DefUnityCallback.h"
#include "com_agulev_defunityads_DefUnityAds.h"

const char* unity_jar_path = "com/agulev/defunityads/DefUnityAds";

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

static JNIEnv* Attach()
{
  JNIEnv* env;
  JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
  vm->AttachCurrentThread(&env, NULL);
  return env;
}

static bool Detach(JNIEnv* env)
{
  bool exception = (bool) env->ExceptionCheck();
  env->ExceptionClear();
  JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
  vm->DetachCurrentThread();
  return !exception;
}

namespace {
struct AttachScope
{
  JNIEnv* m_Env;
  AttachScope() : m_Env(Attach())
  {
  }
  ~AttachScope()
  {
    Detach(m_Env);
  }
};
}

static jclass GetClass(JNIEnv* env, const char* classname)
{
  jclass activity_class = env->FindClass("android/app/NativeActivity");
  jmethodID get_class_loader = env->GetMethodID(activity_class,"getClassLoader", "()Ljava/lang/ClassLoader;");
  jobject cls = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
  jclass class_loader = env->FindClass("java/lang/ClassLoader");
  jmethodID find_class = env->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

  jstring str_class_name = env->NewStringUTF(classname);
  jclass outcls = (jclass)env->CallObjectMethod(cls, find_class, str_class_name);

  env->DeleteLocalRef(str_class_name);
  env->DeleteLocalRef(activity_class);
  env->DeleteLocalRef(class_loader);
  env->DeleteLocalRef(cls);

  return outcls;
}

void DefUnityAds_Initialize(const char*game_id, bool is_debug) {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);

  jmethodID method = env->GetStaticMethodID(cls, "sdk_pre_init", "(Landroid/app/Activity;)V");
  env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity());

  jstring appid = env->NewStringUTF(game_id);
  method = env->GetStaticMethodID(cls, "DefUnityAds_Initialize", "(Ljava/lang/String;Z)V");
  env->CallStaticVoidMethod(cls, method, appid, is_debug ? JNI_TRUE : JNI_FALSE);

  env->DeleteLocalRef(cls);
  env->DeleteLocalRef(appid);
}

void DefUnityAds_Show(char* placementId) {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);

  jstring jplacementId = env->NewStringUTF(placementId);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_Show", "(Ljava/lang/String;)V");
  env->CallStaticVoidMethod(cls, method, jplacementId);

  env->DeleteLocalRef(cls);
  env->DeleteLocalRef(jplacementId);
}

void DefUnityAds_setDebugMode(bool is_debug) {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_setDebugMode", "(Z)V");
  env->CallStaticVoidMethod(cls, method, is_debug ? JNI_TRUE : JNI_FALSE);

  env->DeleteLocalRef(cls);
}

bool DefUnityAds_isReady(char* placementId) {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);

  jstring jplacementId = env->NewStringUTF(placementId);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_isReady", "(Ljava/lang/String;)Z");

  jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, jplacementId);

  env->DeleteLocalRef(cls);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_isSupported() {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_isSupported", "()Z");
  jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);

  env->DeleteLocalRef(cls);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_isInitialized() {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_isInitialized", "()Z");
  jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);

  env->DeleteLocalRef(cls);

  return JNI_TRUE == return_value;
}

bool DefUnityAds_getDebugMode() {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_getDebugMode", "()Z");
  jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);

  env->DeleteLocalRef(cls);

  return JNI_TRUE == return_value;
}

char const* DefUnityAds_getVersion() {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_getVersion", "()Ljava/lang/String;");
  jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method);
  const char* new_char = env->GetStringUTFChars(return_value, 0);

  env->DeleteLocalRef(cls);
  env->DeleteLocalRef(return_value);

  return new_char;
}

int DefUnityAds_getPlacementState(char* placementId) {
  AttachScope attachscope;
  JNIEnv* env = attachscope.m_Env;
  jclass cls = GetClass(env, unity_jar_path);

  jstring jplacementId = env->NewStringUTF(placementId);
  jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_getPlacementState", "(Ljava/lang/String;)I");

  jint return_value = (jint)env->CallStaticIntMethod(cls, method, jplacementId);

  env->DeleteLocalRef(cls);
  env->DeleteLocalRef(jplacementId);

  return JNI_TRUE == return_value;
}

#endif
