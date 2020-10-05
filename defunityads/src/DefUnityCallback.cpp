#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "private_DefUnityCallback.h"
#include "utils/LuaUtils.h"
#include <stdlib.h>

namespace dmUnityAds {
    
static DefUnityAdsListener     defUtoLua;
static dmArray<CallbackData>   m_callbacksQueue;
static dmMutex::HMutex         m_mutex;

static void RegisterCallback(lua_State* L, int index, DefUnityAdsListener* cbk)
{
    if(cbk->m_Callback != LUA_NOREF)
    {
        dmScript::Unref(cbk->m_L, LUA_REGISTRYINDEX, cbk->m_Callback);
        dmScript::Unref(cbk->m_L, LUA_REGISTRYINDEX, cbk->m_Self);
    }

    cbk->m_L = dmScript::GetMainThread(L);

    luaL_checktype(L, index, LUA_TFUNCTION);
    lua_pushvalue(L, index);
    cbk->m_Callback = dmScript::Ref(L, LUA_REGISTRYINDEX);

    dmScript::GetInstance(L);
    cbk->m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
}

static void UnregisterCallback(DefUnityAdsListener* cbk)
{
    if(cbk->m_Callback != LUA_NOREF)
    {
        dmScript::Unref(cbk->m_L, LUA_REGISTRYINDEX, cbk->m_Callback);
        dmScript::Unref(cbk->m_L, LUA_REGISTRYINDEX, cbk->m_Self);
        cbk->m_Callback = LUA_NOREF;
    }
}

static void InvokeCallback(int type, char*key_1, char*value_1, char*key_2, int value_2, DefUnityAdsListener* cbk)
{
    if(cbk->m_Callback == LUA_NOREF)
    {
        dmLogInfo("DefUnityAds callback do not exist.");
        return;
    }

    lua_State* L = cbk->m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, cbk->m_Callback);
    lua_rawgeti(L, LUA_REGISTRYINDEX, cbk->m_Self);
    lua_pushvalue(L, -1);
    dmScript::SetInstance(L);

    if (!dmScript::IsInstanceValid(L)) {
        UnregisterCallback(&defUtoLua);
        dmLogError("Could not run DefUnityAds callback because the instance has been deleted.");
        lua_pop(L, 2);
    }
    else {
        lua_pushnumber(L, type);
        int count_table_elements = 0;
        if (key_1 != NULL) {
            count_table_elements = 1;
        }
        if (key_2 != NULL) {
            count_table_elements = 2;
        }
        if (count_table_elements > 0) {
            lua_createtable(L, 0, count_table_elements);
            luaL_push_pair_str_str(L, key_1, value_1);
            if (key_2 != NULL) {
                luaL_push_pair_str_num(L, key_2, value_2);
            }
        }

        int number_of_arguments = 3;
        if (count_table_elements == 0) {
            number_of_arguments -= 1;
        }
        int ret = lua_pcall(L, number_of_arguments, 0, 0);
        if(ret != 0) {
            dmLogError("Error running callback: %s", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    assert(top == lua_gettop(L));
}

void Initialize(){
    m_mutex = dmMutex::New();
}

void Finalize(){
    dmMutex::Delete(m_mutex);
    UnregisterCallback(&defUtoLua);
}

void SetLuaCallback(lua_State* L, int pos){
    int type = lua_type(L, pos);
    if (type == LUA_TNONE || type == LUA_TNIL) {
        UnregisterCallback(&defUtoLua);
    }
    else{
        RegisterCallback(L, pos, &defUtoLua);
    }
}

void AddToQueue(int type, char*key_1, char*value_1, char*key_2, int value_2){
    DM_MUTEX_SCOPED_LOCK(m_mutex);
    
    CallbackData data;
    data.msg_type = type;
    data.key_1 = key_1;
    data.value_1 = value_1 ? strdup(value_1) : NULL;
    data.key_2 = key_2;
    data.value_2 = value_2;

    if(m_callbacksQueue.Full())
    {
        m_callbacksQueue.OffsetCapacity(4);
    }
    m_callbacksQueue.Push(data);
}

void CallbackUpdate(){
    if (m_callbacksQueue.Empty()) {
        return;
    }

    DM_MUTEX_SCOPED_LOCK(m_mutex);
    
    for(uint32_t i = 0; i != m_callbacksQueue.Size(); ++i)
    {
        CallbackData* data = &m_callbacksQueue[i];
        InvokeCallback(data->msg_type, data->key_1, data->value_1, data->key_2, data->value_2, &defUtoLua);
        if(data->value_1)
            free(data->value_1);
        data->value_1 = 0;
    }
    m_callbacksQueue.SetSize(0);
}

} //namespace

#endif
