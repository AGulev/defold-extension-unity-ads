#include "DefUnityCallback.h"
#include "utils/LuaUtils.h"

DispatchToLua g_DefUAds;
DispatchToLua* defUtoLua;

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

void lua_unityAdsReady(char*placementId) {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_IS_READY);
    lua_createtable(L, 0, 1);
    luaL_push_pair_str_str(L, (char*)"placementId", placementId);
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}

void lua_unityAdsDidStart(char*placementId) {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_DID_START);
    lua_createtable(L, 0, 1);
    luaL_push_pair_str_str(L, (char*)"placementId", placementId);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}

void lua_unityAdsDidError(int error, char* message) {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
    lua_pushnumber(L, (int)TYPE_DID_ERROR);
    lua_createtable(L, 0, 2);
    luaL_push_pair_str_str(L, (char*)"message", message);
    luaL_push_pair_str_num(L, (char*)"error", error);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}
void lua_unityAdsDidFinish (char *placementId, int state) {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_DID_FINISH);
    lua_createtable(L, 0, 2);
    luaL_push_pair_str_str(L, (char*)"placementId", (char*)placementId);
    luaL_push_pair_str_num(L, (char*)"state", state);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}
