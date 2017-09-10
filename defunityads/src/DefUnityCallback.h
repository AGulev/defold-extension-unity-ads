#pragma once

#include <dmsdk/sdk.h>

enum DefUnityAdsCallbackType
{
    TYPE_IS_READY,
    TYPE_DID_START,
    TYPE_DID_ERROR,
    TYPE_DID_FINISH
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

struct DefUnityAdsListener {
    DefUnityAdsListener() {
        m_L = 0;
        m_Callback = LUA_NOREF;
        m_Self = LUA_NOREF;
    }
    lua_State* m_L;
    int        m_Callback;
    int        m_Self;
};

struct DispatchToLua {
    DefUnityAdsListener listener;
};

void set_callback(lua_State* L, int pos);
void send_callback(int type, char*key_1, char*value_1, char*key_2, int value_2);
void callback_updates();
void finalize();

void lua_unityAdsReady(char*placementId);
void lua_unityAdsDidStart(char*placementId);
void lua_unityAdsDidError(int error, char* message);
void lua_unityAdsDidFinish (char *placementId, int state);
