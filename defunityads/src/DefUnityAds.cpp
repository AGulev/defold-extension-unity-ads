#define EXTENSION_NAME DefUnityAds
#define LIB_NAME "DefUnityAds"
#define MODULE_NAME "unityads"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "utils/LuaUtils.h"
#include "private_DefUnityCallback.h"
#include "private_DefUnityAds.h"

static int Initialize(lua_State* L) {
  const char *gameId_lua = luaL_checkstring(L, 1);
  bool enableDebugMode_lua = false;
  DefUnityCallback_set_callback(L, 2);
  if (lua_type(L, 3) != LUA_TNONE) {
    enableDebugMode_lua = luaL_checkbool(L, 3);
  }
  DefUnityAds_Initialize(gameId_lua, enableDebugMode_lua);
  return 0;
}

static int setCallback(lua_State* L) {
  DefUnityCallback_set_callback(L, 1);
  return 0;
}

static int Show(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  DefUnityAds_Show(placementId_lua);
  return 0;
}

static int isReady(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  bool status = DefUnityAds_isReady(placementId_lua);
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

static int getPlacementState(lua_State* L) {
  char *placementId_lua = "";
  if (lua_type(L, 1) != LUA_TNONE) {
    placementId_lua = (char*)luaL_checkstring(L, 1);
  }
  int state = DefUnityAds_getPlacementState(placementId_lua);
  lua_pushnumber(L, state);
  return 1;
}

static int setDebugMode(lua_State* L) {
  bool enableDebugMode_lua = luaL_checkbool(L, 1);
  DefUnityAds_setDebugMode(enableDebugMode_lua);
  return 0;
}

static int setBannerPosition(lua_State* L) {
  int position_lua = luaL_checknumber(L, 1);
  DefUnityAds_setBannerPosition((DefUnityBannerPosition)position_lua);
  return 0;
}

static int loadBanner(lua_State* L) {
  char *placementId_lua = (char*)luaL_checkstring(L, 1);
  int width_lua = 320;
  int height_lua = 50;
  if (lua_type(L, 2) != LUA_TNONE) {
    width_lua = luaL_checknumber(L, 2);
  }
  if (lua_type(L, 3) != LUA_TNONE) {
    height_lua = luaL_checknumber(L, 3);
  }
  DefUnityAds_loadBanner(placementId_lua, width_lua, height_lua);
  return 0;
}

static int unloadBanner(lua_State* L) {
  DefUnityAds_unloadBanner();
  return 0;
}

static int showBanner(lua_State* L) {
  DefUnityAds_showBanner();
  return 0;
}

static int hideBanner(lua_State* L) {
  DefUnityAds_hideBanner();
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
  {"getPlacementState", getPlacementState},
  {"setDebugMode", setDebugMode},
  {"setCallback", setCallback},
  {"setBannerPosition", setBannerPosition},
  {"loadBanner", loadBanner},
  {"unloadBanner", unloadBanner},
  {"showBanner", showBanner},
  {"hideBanner", hideBanner},
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
  DefUnityAds_InitExtension();
  DefUnityCallback_initialize();
  return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeUnityAds(dmExtension::AppParams* params)
{
  DefUnityAds_FinalizeExtension();
  return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeUnityAds(dmExtension::Params* params)
{
  DefUnityCallback_finalize();
  return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateUnityAds(dmExtension::Params* params)
{
  DefUnityCallback_callback_updates();
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
