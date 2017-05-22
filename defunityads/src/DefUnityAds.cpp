#define EXTENSION_NAME DefUninyAds
#define LIB_NAME "DefUninyAds"
#define MODULE_NAME "unityads"

// Defold SDK
#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS)

#include "DefUnityAds_private.h"

static int Initialize(lua_State* L) {
    DefUnityAds_Initialize(L);
    return 0;
}

static int Show(lua_State* L) {
    DefUnityAds_Show(L);
    return 0;
}

static int isReady(lua_State* L) {
    bool status = DefUnityAds_isReady(L);
    lua_pushboolean(L, status);
    return 1;
}

static int isInitialized(lua_State* L) {
    bool status = DefUnityAds_isInitialized();
    lua_pushboolean(L, status);
    return 1;
}

static int isSupported(lua_State* L) {
    bool status = DefUnityAds_isSupported();
    lua_pushboolean(L, status);
    return 1;
}

static int getDebugMode(lua_State* L) {
    bool status = DefUnityAds_getDebugMode();
    lua_pushboolean(L, status);
    return 1;
}

static int getVersion(lua_State* L) {
    const char *version = DefUnityAds_getVersion();
    lua_pushstring(L, version);
    return 1;
}

static int setDebugMode(lua_State* L) {
    DefUnityAds_setDebugMode(L);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Initialize},
    {"show", Show},
    {"isReady", isReady},
    {"isSupported", isSupported},
    {"isInitialized", isInitialized},
    {"getDebugMode", getDebugMode},
    {"getVersion", getVersion},
    {"setDebugMode", setDebugMode},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name);\

    SETCONSTANT(TYPE_IS_READY)
    SETCONSTANT(TYPE_DID_START)
    SETCONSTANT(TYPE_DID_ERROR)
    SETCONSTANT(TYPE_DID_FINISH)
    
    SETCONSTANT(FINISH_STATE_ERROR)
    SETCONSTANT(FINISH_STATE_COMPLETED)
    SETCONSTANT(FINISH_STATE_SKIPPED)
    
    SETCONSTANT(ERROR_NOT_INITIALIZED)
    SETCONSTANT(ERROR_INITIALIZED_FAILED)
    SETCONSTANT(ERROR_INVALID_ARGUMENT)
    SETCONSTANT(ERROR_VIDEO_PLAYER)
    SETCONSTANT(ERROR_INIT_SANITY_CHECK_FAIL)
    SETCONSTANT(ERROR_AD_BLOCKER_DETECTED)
    SETCONSTANT(ERROR_FILE_IO)
    SETCONSTANT(ERROR_DEVICE_ID)
    SETCONSTANT(ERROR_SHOW)
    SETCONSTANT(ERROR_INTERNAL)

    #undef SETCONSTANT
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#elif defined(DM_PLATFORM_ANDROID)

const char* unity_jar_path = "com/agulev/defunityads/DefUnityAds";

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
    return outcls;
}

//static int Initialize(lua_State* L) {
//    DefUnityAds_Initialize(L);
//    return 0;
//}
//
//static int Show(lua_State* L) {
//    DefUnityAds_Show(L);
//    return 0;
//}

static int isReady(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    
    const char *placementId_lua = luaL_checkstring(L, 1);
    jstring placementId = env->NewStringUTF(placementId_lua);
    jmethodID method = env->GetStaticMethodID(cls, "DefUnityAds_isReady", "(Ljava/lang/String;)Z");
    if (method == NULL){
        dmLogInfo("SOMETHING WRONG");
    }

    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, placementId);
    lua_pushboolean(L, JNI_TRUE == return_value);
    return 1;
}

static int isInitialized(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "isInitialized", "()Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);
    bool status = false;
    if (JNI_TRUE == return_value) status = true;
    lua_pushboolean(L, status);
    return 1;
}

static int isSupported(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "isSupported", "()Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);
    bool status = false;
    if (JNI_TRUE == return_value) status = true;
    lua_pushboolean(L, status);
    return 1;
}

static int getDebugMode(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "getDebugMode", "()Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method);
    bool status = false;
    if (JNI_TRUE == return_value) status = true;
    lua_pushboolean(L, status);
    return 1;
}

static int getVersion(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "getVersion", "()Ljava/lang/String;");
    jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method);
    lua_pushstring(L, env->GetStringUTFChars(return_value, 0));
    env->DeleteLocalRef(return_value);
    return 1;
}

static bool luaL_checkbool(lua_State *L, int numArg)
{
    bool b = false;
    if (lua_isboolean(L, numArg))
    {
        b = lua_toboolean(L, numArg);
    }
    else
    {
        luaL_typerror(L, numArg, lua_typename(L, LUA_TBOOLEAN));
    }
    return b;
}

static int setDebugMode(lua_State* L) {
    bool enableDebugMode = luaL_checkbool(L, 1);
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, unity_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "setDebugMode", "(Z)V");
    env->CallStaticVoidMethod(cls, method, enableDebugMode? JNI_TRUE : JNI_FALSE);
    return 0;
}

static const luaL_reg Module_methods[] =
{
//    {"initialize", Initialize},
//    {"show", Show},
    {"isReady", isReady},
    {"isSupported", isSupported},
    {"isInitialized", isInitialized},
    {"getDebugMode", getDebugMode},
    {"getVersion", getVersion},
    {"setDebugMode", setDebugMode},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
//    #define SETCONSTANT(name) \
//    lua_pushnumber(L, (lua_Number) name); \
//    lua_setfield(L, -2, #name);\
//
//    SETCONSTANT(TYPE_IS_READY)
//    SETCONSTANT(TYPE_DID_START)
//    SETCONSTANT(TYPE_DID_ERROR)
//    SETCONSTANT(TYPE_DID_FINISH)
//    
//    SETCONSTANT(FINISH_STATE_ERROR)
//    SETCONSTANT(FINISH_STATE_COMPLETED)
//    SETCONSTANT(FINISH_STATE_SKIPPED)
//    
//    SETCONSTANT(ERROR_NOT_INITIALIZED)
//    SETCONSTANT(ERROR_INITIALIZED_FAILED)
//    SETCONSTANT(ERROR_INVALID_ARGUMENT)
//    SETCONSTANT(ERROR_VIDEO_PLAYER)
//    SETCONSTANT(ERROR_INIT_SANITY_CHECK_FAIL)
//    SETCONSTANT(ERROR_AD_BLOCKER_DETECTED)
//    SETCONSTANT(ERROR_FILE_IO)
//    SETCONSTANT(ERROR_DEVICE_ID)
//    SETCONSTANT(ERROR_SHOW)
//    SETCONSTANT(ERROR_INTERNAL)
//
//    #undef SETCONSTANT
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static int isSupported(lua_State* L) {
    bool status = false;
    lua_pushboolean(L, status);
    return 1;
}

static int Show(lua_State* L) {
    return 0;
}

static int Initialize(lua_State* L) {
    return 0;
}

static int isReady(lua_State* L) {
    bool status = false;
    lua_pushboolean(L, status);
    return 1;
}

static int isInitialized(lua_State* L) {
    bool status = false;
    lua_pushboolean(L, status);
    return 1;
}

static int getDebugMode(lua_State* L) {
    bool status = true;
    lua_pushboolean(L, status);
    return 1;
}

static int getVersion(lua_State* L) {
    bool status = true;
    lua_pushstring(L, "0.0.0");
    return 1;
}

static int setDebugMode(lua_State* L) {
    bool status = true;
    lua_pushboolean(L, status);
    return 1;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Initialize},
    {"show", Show},
    {"isReady", isReady},
    {"isSupported", isSupported},
    {"isInitialized", isInitialized},
    {"getDebugMode", getDebugMode},
    {"getVersion", getVersion},
    {"setDebugMode", setDebugMode},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}


static dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif // platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeUnityAds, AppFinalizeUnityAds, InitializeUnityAds, 0, 0, FinalizeUnityAds)
