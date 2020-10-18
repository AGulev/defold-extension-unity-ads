#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "private_DefUnityCallback.h"
#include "utils/LuaUtils.h"
#include <stdlib.h>

namespace dmUnityAds {

static dmScript::LuaCallbackInfo* defUtoLua = 0x0;
static dmArray<CallbackData> m_callbacksQueue;
static dmMutex::HMutex m_mutex;

static void DestroyCallback()
{
    if (defUtoLua != 0x0) {
        dmScript::DestroyCallback(defUtoLua);
        defUtoLua = 0x0;
    }
}

static void InvokeCallback(int type, char*key_1, char*value_1, char*key_2, int value_2)
{
    if (!dmScript::IsCallbackValid(defUtoLua)) {
        dmLogError("DefUnityAds callback is invalid. Set new callback unsing `unityads.setCallback()` funciton.");
        return;
    }

    lua_State* L = dmScript::GetCallbackLuaContext(defUtoLua);
    int top = lua_gettop(L);

    if (!dmScript::SetupCallback(defUtoLua)) {
        return;
    }

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

    int ret = dmScript::PCall(L, number_of_arguments, 0);
    (void)ret;
    dmScript::TeardownCallback(defUtoLua);

    assert(top == lua_gettop(L));
}

void Initialize(){
    m_mutex = dmMutex::New();
}

void Finalize(){
    dmMutex::Delete(m_mutex);
    DestroyCallback();
}

void SetLuaCallback(lua_State* L, int pos){
    int type = lua_type(L, pos);
    if (type == LUA_TNONE || type == LUA_TNIL) {
        DestroyCallback();
    }
    else {
        defUtoLua = dmScript::CreateCallback(L, pos);
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
        InvokeCallback(data->msg_type, data->key_1, data->value_1, data->key_2, data->value_2);
        if(data->value_1)
            free(data->value_1);
        data->value_1 = 0;
    }
    m_callbacksQueue.SetSize(0);
}

} //namespace

#endif
