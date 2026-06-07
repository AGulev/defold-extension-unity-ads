#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "unityads_callback_private.h"
#include "utils/LuaUtils.h"
#include <stdlib.h>
#include <string.h>

namespace dmUnityAds {

    static const dmhash_t MASTER_SOUND_GROUP = dmHashString64("master");

    static dmScript::LuaCallbackInfo* m_luaCallback = 0x0;
    static dmArray<CallbackData> m_callbacksQueue;
    static dmMutex::HMutex m_mutex;
    static bool m_wasMutedBeforeAd = false;
    static bool m_hasSavedMuteState = false;

    static bool GetEventFromJson(const char* json, int* event)
    {
        if (!json || !event)
        {
            return false;
        }

        const char* event_key = "\"event\"";
        const char* event_pos = strstr(json, event_key);
        if (!event_pos)
        {
            return false;
        }

        const char* event_value = strchr(event_pos + strlen(event_key), ':');
        if (!event_value)
        {
            return false;
        }

        char* end = 0;
        long parsed_event = strtol(event_value + 1, &end, 10);
        if (end == event_value + 1)
        {
            return false;
        }

        *event = (int)parsed_event;
        return true;
    }

    static void UpdateAdSoundState(MessageId type, const char* json)
    {
        if (type != MSG_SHOW)
        {
            return;
        }

        int event = 0;
        if (!GetEventFromJson(json, &event))
        {
            return;
        }

        switch ((MessageEvent)event)
        {
            case EVENT_START:
                if (!m_hasSavedMuteState)
                {
                    m_wasMutedBeforeAd = dmSound::IsGroupMuted(MASTER_SOUND_GROUP);
                    m_hasSavedMuteState = true;
                }
                dmSound::SetGroupMute(MASTER_SOUND_GROUP, true);
                break;
            case EVENT_COMPLETED:
            case EVENT_SDK_ERROR:
            case EVENT_JSON_ERROR:
            case EVENT_SKIPPED:
                if (m_hasSavedMuteState)
                {
                    dmSound::SetGroupMute(MASTER_SOUND_GROUP, m_wasMutedBeforeAd);
                    m_hasSavedMuteState = false;
                }
                break;
            default:
                break;
        }
    }

    static void DestroyCallback()
    {
        if (m_luaCallback != 0x0)
        {
            dmScript::DestroyCallback(m_luaCallback);
            m_luaCallback = 0x0;
        }
    }

    static void InvokeCallback(MessageId type, char*json)
    {
        if (!dmScript::IsCallbackValid(m_luaCallback))
        {
            dmLogError("UnityADS callback is invalid. Set new callback unsing `unityads.setCallback()` funciton.");
            return;
        }

        lua_State* L = dmScript::GetCallbackLuaContext(m_luaCallback);
        int top = lua_gettop(L);

        if (!dmScript::SetupCallback(m_luaCallback))
        {
            return;
        }

        lua_pushnumber(L, type);
        dmScript::JsonToLua(L, json, strlen(json)); // throws lua error if it fails

        int ret = dmScript::PCall(L, 3, 0);
        (void)ret;
        dmScript::TeardownCallback(m_luaCallback);

        assert(top == lua_gettop(L));
    }

    void InitializeCallback()
    {
        m_mutex = dmMutex::New();
    }

    void FinalizeCallback()
    {
        if (m_hasSavedMuteState)
        {
            dmSound::SetGroupMute(MASTER_SOUND_GROUP, m_wasMutedBeforeAd);
            m_hasSavedMuteState = false;
        }
        dmMutex::Delete(m_mutex);
        DestroyCallback();
    }

    void SetLuaCallback(lua_State* L, int pos)
    {
        int type = lua_type(L, pos);
        if (type == LUA_TNONE || type == LUA_TNIL)
        {
            DestroyCallback();
        }
        else
        {
            m_luaCallback = dmScript::CreateCallback(L, pos);
        }
    }

    void AddToQueueCallback(MessageId type, const char*json)
    {
        CallbackData data;
        data.msg = type;
        data.json = json ? strdup(json) : NULL;

        DM_MUTEX_SCOPED_LOCK(m_mutex);
        if(m_callbacksQueue.Full())
        {
            m_callbacksQueue.OffsetCapacity(2);
        }
        m_callbacksQueue.Push(data);
    }

    void UpdateCallback()
    {
        if (m_callbacksQueue.Empty())
        {
            return;
        }

        dmArray<CallbackData> tmp;
        {
            DM_MUTEX_SCOPED_LOCK(m_mutex);
            tmp.Swap(m_callbacksQueue);
        }

        for(uint32_t i = 0; i != tmp.Size(); ++i)
        {
            CallbackData* data = &tmp[i];
            UpdateAdSoundState(data->msg, data->json);
            InvokeCallback(data->msg, data->json);
            if(data->json)
            {
                free(data->json);
                data->json = 0;
            }
        }
    }

} //namespace

#endif
