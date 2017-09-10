#include "DefUnityCallback.h"
#include "utils/LuaUtils.h"

DispatchToLua g_DefUAds;
DispatchToLua* defUtoLua;

struct CallbackData
{
    int msg_type;
    char* key_1;
    char* value_1;
    char* key_2;
    int value_2;
};

dmArray<CallbackData> m_callbacksQueue;

void finalize(){
	defUtoLua->listener.m_Callback = LUA_NOREF;
}

void set_callback(lua_State* L, int pos){
    defUtoLua = &g_DefUAds;
    luaL_checktype(L, pos, LUA_TFUNCTION);
    lua_pushvalue(L, pos);
    int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);
    
    if (defUtoLua->listener.m_Callback != LUA_NOREF) {
        dmScript::Unref(defUtoLua->listener.m_L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
        dmScript::Unref(defUtoLua->listener.m_L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
    }
    
    defUtoLua->listener.m_L = dmScript::GetMainThread(L);
    defUtoLua->listener.m_Callback = cb;
    dmScript::GetInstance(L);
    defUtoLua->listener.m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
}

void send_callback(int type, char*key_1, char*value_1, char*key_2, int value_2){
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
    dmScript::SetInstance(L);
    lua_pushnumber(L, type);
    int count_table_elements = 1;
    if (key_2 != NULL){
        count_table_elements = 2;
    }
    lua_createtable(L, 0, count_table_elements);
    luaL_push_pair_str_str(L, key_1, value_1);
    if (key_2 != NULL){
        luaL_push_pair_str_num(L, key_2, value_2);
    }
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}

void add_to_queue(int type, char*key_1, char*value_1, char*key_2, int value_2){
    CallbackData data;
    data.msg_type = type;
    data.key_1 = key_1;
    data.value_1 = value_1 ? strdup(value_1) : NULL;
    data.key_2 = key_2;
    data.value_2 = value_2;
    
    if(m_callbacksQueue.Full())
    {
        m_callbacksQueue.OffsetCapacity(8);
    }
    m_callbacksQueue.Push(data);
}

void lua_unityAdsReady(char*placementId) {
    add_to_queue((int)TYPE_IS_READY,(char*)"placementId", placementId, NULL, 0);
}

void lua_unityAdsDidStart(char*placementId) {
    add_to_queue((int)TYPE_DID_START,(char*)"placementId", placementId, NULL, 0);
}

void lua_unityAdsDidError(int error, char* message) {
    add_to_queue((int)TYPE_DID_ERROR,(char*)"message", message, (char*)"error", error);
}

void lua_unityAdsDidFinish (char *placementId, int state) {
    add_to_queue((int)TYPE_DID_FINISH,(char*)"placementId", placementId, (char*)"state", state);
}

void callback_updates(){
    for(uint32_t i = 0; i != m_callbacksQueue.Size(); ++i)
    {
        CallbackData* data = &m_callbacksQueue[i];
        send_callback(data->msg_type, data->key_1, data->value_1, data->key_2, data->value_2);
        if( data->value_1 )
            free(data->value_1);
        data->value_1 = 0;
        m_callbacksQueue.EraseSwap(i--);
    }
}
