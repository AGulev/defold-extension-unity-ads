#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)
#pragma once

#include <dmsdk/sdk.h>

namespace dmUnityAds {

// The same events and messages are in DefUnityAdsJNI.java
// If you change enums here, pls nake sure you update the constants there as well

enum MessageId
{
    MSG_INIT=                        1,
    MSG_SHOW =                       2,
    MSG_LOAD =                       3,
    MSG_BANNER =                     4,
    MSG_IDFA =                       5
};

enum MessageEvent
{
    EVENT_COMPLETED =                1,
    EVENT_SDK_ERROR =                2,
    EVENT_JSON_ERROR =               3,
    EVENT_CLICKED =                  4,
    EVENT_START =                    5,
    EVENT_LOADED =                   6,
    EVENT_LEFT_APPLICATION =         7,
    EVENT_SKIPPED =                  8,
    EVENT_NOT_SUPPORTED =            9,
    EVENT_STATUS_AUTORIZED =        10,
    EVENT_STATUS_DENIED =           11,
    EVENT_STATUS_NOT_DETERMINED =   12,
    EVENT_STATUS_RESTRICTED =       13,
    EVENT_DID_SHOW =                14
};

enum Errors
{
    ERROR_INTERNAL =                 1,
    ERROR_INVALID_ARGUMENT =         2,
    ERROR_NOT_INITIALIZED =          3,
    ERROR_NOT_READY =                4,
    ERROR_VIDEO_PLAYER =             5,
    ERROR_NO_CONNECTION =            6,
    ERROR_ALREADY_SHOWING =          7,
    ERROR_NO_FILL =                  8,
    ERROR_TIMEOUT =                  9,
    ERROR_UNKNOWN =                 10,
    ERROR_NATIVE =                  11,
    ERROR_WEBVIEW =                 12,
    ERROR_AD_BLOCKER_DETECTED =     13
};

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char*json);

} //namespace

#endif