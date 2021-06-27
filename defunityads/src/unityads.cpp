#define EXTENSION_NAME DefUnityAds
#define LIB_NAME "DefUnityAds"
#define MODULE_NAME "unityads"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "utils/LuaUtils.h"
#include "unityads_callback_private.h"
#include "unityads_private.h"

namespace dmUnityAds {
    
static int Lua_Initialize(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    const char *gameId_lua = luaL_checkstring(L, 1);
    bool enableDebugMode_lua = false;
    bool enablePerPlacementLoad_lua = false;
    SetLuaCallback(L, 2);
    if (lua_type(L, 3) != LUA_TNONE) {
        enableDebugMode_lua = luaL_checkbool(L, 3);
    }
    if (lua_type(L, 4) != LUA_TNONE) {
        enablePerPlacementLoad_lua = luaL_checkbool(L, 4);
    }
    Initialize(gameId_lua, enableDebugMode_lua, enablePerPlacementLoad_lua);
    return 0;
}

static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Lua_Show(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    char *placementId_lua = (char*)luaL_checkstring(L, 1);
    Show(placementId_lua);
    return 0;
}

static int Lua_Load(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    char *placementId_lua = (char*)luaL_checkstring(L, 1);
    Load(placementId_lua);
    return 0;
}

static int Lua_IsReady(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    char *placementId_lua = (char*)luaL_checkstring(L, 1);
    bool status = IsReady(placementId_lua);
    lua_pushboolean(L, status);
    return 1;
}

static int Lua_IsInitialized(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    bool status = IsInitialized();
    lua_pushboolean(L, status);
    return 1;
}

static int Lua_IsSupported(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    bool status = IsSupported();
    lua_pushboolean(L, status);
    return 1;
}

static int Lua_GetDebugMode(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    bool status = GetDebugMode();
    lua_pushboolean(L, status);
    return 1;
}

static int Lua_GetVersion(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    const char *version = GetVersion();
    lua_pushstring(L, version);
    return 1;
}

static int Lua_GetPlacementState(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);
    char *placementId_lua = (char*)luaL_checkstring(L, 1);
    int state = GetPlacementState(placementId_lua);
    lua_pushnumber(L, state);
    return 1;
}

static int Lua_SetDebugMode(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    bool enableDebugMode_lua = luaL_checkbool(L, 1);
    SetDebugMode(enableDebugMode_lua);
    return 0;
}

static int Lua_SetBannerPosition(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    int position_lua = luaL_checknumber(L, 1);
    SetBannerPosition((DefUnityBannerPosition)position_lua);
    return 0;
}

static int Lua_LoadBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    char *placementId_lua = (char*)luaL_checkstring(L, 1);
    int width_lua = 320;
    int height_lua = 50;
    if (lua_type(L, 2) != LUA_TNONE) {
        width_lua = luaL_checknumber(L, 2);
    }
    if (lua_type(L, 3) != LUA_TNONE) {
        height_lua = luaL_checknumber(L, 3);
    }
    LoadBanner(placementId_lua, width_lua, height_lua);
    return 0;
}

static int Lua_UnloadBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    UnloadBanner();
    return 0;
}

static int Lua_ShowBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    ShowBanner();
    return 0;
}

static int Lua_HideBanner(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    HideBanner();
    return 0;
}

static int Lua_RequestIDFA(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    RequestIDFA();
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"initialize", Lua_Initialize},
    {"show", Lua_Show},
    {"load", Lua_Load},
    {"is_ready", Lua_IsReady},
    {"is_supported", Lua_IsSupported},
    {"is_initialized", Lua_IsInitialized},
    {"get_debug_mode", Lua_GetDebugMode},
    {"get_version", Lua_GetVersion},
    {"get_placement_state", Lua_GetPlacementState},
    {"set_debug_mode", Lua_SetDebugMode},
    {"set_callback", Lua_SetCallback},
    {"set_banner_position", Lua_SetBannerPosition},
    {"load_banner", Lua_LoadBanner},
    {"unload_banner", Lua_UnloadBanner},
    {"show_banner", Lua_ShowBanner},
    {"hide_banner", Lua_HideBanner},
    {"request_idfa", Lua_RequestIDFA},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(MSG_INIT)
    SETCONSTANT(MSG_SHOW)
    SETCONSTANT(MSG_LOAD)
    SETCONSTANT(MSG_BANNER)
    SETCONSTANT(MSG_IDFA)

    SETCONSTANT(EVENT_COMPLETED)
    SETCONSTANT(EVENT_SDK_ERROR)
    SETCONSTANT(EVENT_JSON_ERROR)
    SETCONSTANT(EVENT_CLICKED)
    SETCONSTANT(EVENT_START)
    SETCONSTANT(EVENT_LOADED)
    SETCONSTANT(EVENT_LEFT_APPLICATION)
    SETCONSTANT(EVENT_SKIPPED)
    SETCONSTANT(EVENT_NOT_SUPPORTED)
    
    SETCONSTANT(ERROR_INTERNAL)
    SETCONSTANT(ERROR_INVALID_ARGUMENT)
    SETCONSTANT(ERROR_NOT_INITIALIZED)
    SETCONSTANT(ERROR_NOT_READY)
    SETCONSTANT(ERROR_VIDEO_PLAYER)
    SETCONSTANT(ERROR_NO_CONNECTION)
    SETCONSTANT(ERROR_ALREADY_SHOWING)
    SETCONSTANT(ERROR_NO_FILL)
    SETCONSTANT(ERROR_TIMEOUT)
    SETCONSTANT(ERROR_UNKNOWN)
    SETCONSTANT(ERROR_NATIVE)
    SETCONSTANT(ERROR_WEBVIEW)
    SETCONSTANT(ERROR_AD_BLOCKER_DETECTED)

    SETCONSTANT(PLACEMENT_STATE_READY)
    SETCONSTANT(PLACEMENT_STATE_NOT_AVAILABLE)
    SETCONSTANT(PLACEMENT_STATE_DISABLED)
    SETCONSTANT(PLACEMENT_STATE_WAITING)
    SETCONSTANT(PLACEMENT_STATE_NO_FILL)

    SETCONSTANT(BANNER_POSITION_TOP_LEFT)
    SETCONSTANT(BANNER_POSITION_TOP_CENTER)
    SETCONSTANT(BANNER_POSITION_TOP_RIGHT)
    SETCONSTANT(BANNER_POSITION_BOTTOM_LEFT)
    SETCONSTANT(BANNER_POSITION_BOTTOM_CENTER)
    SETCONSTANT(BANNER_POSITION_BOTTOM_RIGHT)
    SETCONSTANT(BANNER_POSITION_CENTER)

#undef SETCONSTANT
    
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

}//namespace

dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
    dmUnityAds::LuaInit(params->m_L);
    dmUnityAds::Initialize_Ext();
    dmUnityAds::InitializeCallback();
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
    dmUnityAds::Finalize_Ext();
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
    dmUnityAds::FinalizeCallback();
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUnityAds(dmExtension::Params* params)
{
    dmUnityAds::UpdateCallback();
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static dmExtension::Result AppInitializeUnityAds(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeUnityAds(dmExtension::Params* params)
{
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

static dmExtension::Result UpdateUnityAds(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif // platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeUnityAds, AppFinalizeUnityAds, InitializeUnityAds, UpdateUnityAds, 0, FinalizeUnityAds)
