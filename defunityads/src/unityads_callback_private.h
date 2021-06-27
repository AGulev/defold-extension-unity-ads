#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)
#pragma once

#include <dmsdk/sdk.h>

namespace dmUnityAds {

enum DefUnityAdsCallbackType
{
    TYPE_IS_READY,
    TYPE_DID_START,
    TYPE_DID_ERROR,
    TYPE_DID_FINISH,
    TYPE_BANNER,
    TYPE_BANNER_ERROR,
    TYPE_INITIALIZED,
    TYPE_INIT_ERROR
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

enum DefUnityInitializeAdsError
{
    INIT_ERROR_INTERNAL_ERROR,
    INIT_ERROR_INVALID_ARGUMENT,
    INIT_ERROR_AD_BLOCKER_DETECTED,
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

// The same events and messages are in DefUnityAdsJNI.java
// If you change enums here, pls nake sure you update the constants there as well

enum MessageId
{
    MSG_INITIALIZATION =            1,
    MSG_INTERSTITIAL =              2,
    MSG_REWARDED =                  3,
    MSG_BANNER =                    4,
    MSG_IDFA =                      5
};

enum MessageEvent
{
    EVENT_CLOSED =                  1,
    EVENT_FAILED_TO_SHOW =          2,
    EVENT_OPENING =                 3,
    EVENT_FAILED_TO_LOAD =          4,
    EVENT_LOADED =                  5,
    EVENT_NOT_LOADED =              6,
    EVENT_EARNED_REWARD =           7,
    EVENT_COMPLETE =                8,
    EVENT_CLICKED =                 9,
    EVENT_DESTROYED =               10,
    EVENT_JSON_ERROR =              11,
    EVENT_IMPRESSION_RECORDED =     12,
    EVENT_STATUS_AUTORIZED =        13,
    EVENT_STATUS_DENIED =           14,
    EVENT_STATUS_NOT_DETERMINED =   15,
    EVENT_STATUS_RESTRICTED =       16,
    EVENT_NOT_SUPPORTED =           17
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