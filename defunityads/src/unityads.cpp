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
  
  static int Lua_Initialize(lua_State* L) {
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

static int Lua_SetCallback(lua_State* L) {
  SetLuaCallback(L, 1);
  return 0;
}

static int Lua_Show(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  Show(placementId_lua);
  return 0;
}

static int Lua_Load(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  Load(placementId_lua);
  return 0;
}

static int Lua_IsReady(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  bool status = IsReady(placementId_lua);
  lua_pushboolean(L, status);
  return 1;
}

static int Lua_IsInitialized(lua_State* L) {
  bool status = IsInitialized();
  lua_pushboolean(L, status);
  return 1;
}

static int Lua_IsSupported(lua_State* L) {
  bool status = IsSupported();
  lua_pushboolean(L, status);
  return 1;
}

static int Lua_GetDebugMode(lua_State* L) {
  bool status = GetDebugMode();
  lua_pushboolean(L, status);
  return 1;
}

static int Lua_GetVersion(lua_State* L) {
  const char *version = GetVersion();
  lua_pushstring(L, version);
  return 1;
}

static int Lua_GetPlacementState(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  int state = GetPlacementState(placementId_lua);
  lua_pushnumber(L, state);
  return 1;
}

static int Lua_SetDebugMode(lua_State* L) {
  bool enableDebugMode_lua = luaL_checkbool(L, 1);
  SetDebugMode(enableDebugMode_lua);
  return 0;
}

static int Lua_SetBannerPosition(lua_State* L) {
  int position_lua = luaL_checknumber(L, 1);
  SetBannerPosition((DefUnityBannerPosition)position_lua);
  return 0;
}

static int Lua_LoadBanner(lua_State* L) {
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

static int Lua_UnloadBanner(lua_State* L) {
  UnloadBanner();
  return 0;
}

static int Lua_ShowBanner(lua_State* L) {
  ShowBanner();
  return 0;
}

static int Lua_HideBanner(lua_State* L) {
  HideBanner();
  return 0;
}

static const luaL_reg Module_methods[] =
{
  {"initialize", Lua_Initialize},
  {"show", Lua_Show},
  {"load", Lua_Load},
  {"isReady", Lua_IsReady},
  {"isSupported", Lua_IsSupported},
  {"isInitialized", Lua_IsInitialized},
  {"getDebugMode", Lua_GetDebugMode},
  {"getVersion", Lua_GetVersion},
  {"getPlacementState", Lua_GetPlacementState},
  {"setDebugMode", Lua_SetDebugMode},
  {"setCallback", Lua_SetCallback},
  {"setBannerPosition", Lua_SetBannerPosition},
  {"loadBanner", Lua_LoadBanner},
  {"unloadBanner", Lua_UnloadBanner},
  {"showBanner", Lua_ShowBanner},
  {"hideBanner", Lua_HideBanner},
  {0, 0}
};

static void LuaInit(lua_State* L)
{
  int top = lua_gettop(L);
  luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
  lua_pushnumber(L, (lua_Number) name); \
  lua_setfield(L, -2, #name); \

  SETCONSTANT(TYPE_IS_READY)
  SETCONSTANT(TYPE_DID_START)
  SETCONSTANT(TYPE_DID_ERROR)
  SETCONSTANT(TYPE_DID_FINISH)
  SETCONSTANT(TYPE_BANNER)
  SETCONSTANT(TYPE_BANNER_ERROR)
  SETCONSTANT(TYPE_INITIALIZED)
  SETCONSTANT(TYPE_INIT_ERROR)

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

  SETCONSTANT(BANNER_EVENT_DID_LOAD)
  SETCONSTANT(BANNER_EVENT_DID_CLICK)
  SETCONSTANT(BANNER_EVENT_DID_LEAVE_APP)

  SETCONSTANT(BANNER_ERROR_UNKNOWN)
  SETCONSTANT(BANNER_ERROR_NATIVE)
  SETCONSTANT(BANNER_ERROR_WEBVIEW)
  SETCONSTANT(BANNER_ERROR_NOFILL)

  SETCONSTANT(INIT_ERROR_INTERNAL_ERROR)
  SETCONSTANT(INIT_ERROR_INVALID_ARGUMENT)
  SETCONSTANT(INIT_ERROR_AD_BLOCKER_DETECTED)

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
