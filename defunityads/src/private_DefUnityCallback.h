#pragma once

#include <dmsdk/sdk.h>

enum DefUnityAdsCallbackType
{
  TYPE_IS_READY,
  TYPE_DID_START,
  TYPE_DID_ERROR,
  TYPE_DID_FINISH,
  TYPE_BANNER,
  TYPE_BANNER_ERROR
};

enum DefUnityAdsFinishState
{
  FINISH_STATE_ERROR,
  FINISH_STATE_SKIPPED,
  FINISH_STATE_COMPLETED
};

enum DefUnityAdsError
{
  ERROR_NOT_INITIALIZED,
  ERROR_INITIALIZED_FAILED,
  ERROR_INVALID_ARGUMENT,
  ERROR_VIDEO_PLAYER,
  ERROR_INIT_SANITY_CHECK_FAIL,
  ERROR_AD_BLOCKER_DETECTED,
  ERROR_FILE_IO,
  ERROR_DEVICE_ID,
  ERROR_SHOW,
  ERROR_INTERNAL
};

enum DefUnityAdsBannerEvent
{
  BANNER_EVENT_DID_LOAD,
  BANNER_EVENT_DID_CLICK,
  BANNER_EVENT_DID_LEAVE_APP
};

enum DefUnityAdsBannerError
{
  BANNER_ERROR_UNKNOWN,
  BANNER_ERROR_NATIVE,
  BANNER_ERROR_WEBVIEW,
  BANNER_ERROR_NOFILL
};

struct DefUnityAdsListener {
  DefUnityAdsListener() : m_L(0), m_Callback(LUA_NOREF), m_Self(LUA_NOREF) {
  }
  lua_State* m_L;
  int m_Callback;
  int m_Self;
};

struct CallbackData
{
  int msg_type;
  char* key_1;
  char* value_1;
  char* key_2;
  int value_2;
};

void DefUnityCallback_set_callback(lua_State* L, int pos);
void DefUnityCallback_callback_updates();
void DefUnityCallback_initialize();
void DefUnityCallback_finalize();

void DefUnityCallback_add_to_queue(int type, char*key_1, char*value_1, char*key_2, int value_2);