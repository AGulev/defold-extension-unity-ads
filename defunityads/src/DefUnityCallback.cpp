#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "private_DefUnityCallback.h"
#include "utils/LuaUtils.h"

DefUnityAdsListener defUtoLua;
dmArray<CallbackData> m_callbacksQueue;

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

static void DefUnityCallback_invoke_callback(int type, char*key_1, char*value_1, char*key_2, int value_2, DefUnityAdsListener* cbk)
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
    int count_table_elements = 1;
    if (key_2 != NULL) {
      count_table_elements = 2;
    }
    lua_createtable(L, 0, count_table_elements);
    luaL_push_pair_str_str(L, key_1, value_1);
    if (key_2 != NULL) {
      luaL_push_pair_str_num(L, key_2, value_2);
    }

    int number_of_arguments = 3;
    int ret = lua_pcall(L, number_of_arguments, 0, 0);
    if(ret != 0) {
      dmLogError("Error running callback: %s", lua_tostring(L, -1));
      lua_pop(L, 1);
    }
  }
  assert(top == lua_gettop(L));
}

void DefUnityCallback_finalize(){
  UnregisterCallback(&defUtoLua);
}

void DefUnityCallback_set_callback(lua_State* L, int pos){
  int type = lua_type(L, pos);
  if (type == LUA_TNONE || type == LUA_TNIL) {
    UnregisterCallback(&defUtoLua);
  }
  else{
    RegisterCallback(L, pos, &defUtoLua);
  }
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
    m_callbacksQueue.OffsetCapacity(4);
  }
  m_callbacksQueue.Push(data);
}

void DefUnityCallback_lua_unityAdsReady(char*placementId) {
  add_to_queue((int)TYPE_IS_READY,(char*)"placementId", placementId, NULL, 0);
}

void DefUnityCallback_lua_unityAdsDidStart(char*placementId) {
  add_to_queue((int)TYPE_DID_START,(char*)"placementId", placementId, NULL, 0);
}

void DefUnityCallback_lua_unityAdsDidError(int error, char* message) {
  add_to_queue((int)TYPE_DID_ERROR,(char*)"message", message, (char*)"error", error);
}

void DefUnityCallback_lua_unityAdsDidFinish (char *placementId, int state) {
  add_to_queue((int)TYPE_DID_FINISH,(char*)"placementId", placementId, (char*)"state", state);
}

void DefUnityCallback_callback_updates(){
  for(uint32_t i = 0; i != m_callbacksQueue.Size(); ++i)
  {
    CallbackData* data = &m_callbacksQueue[i];
    DefUnityCallback_invoke_callback(data->msg_type, data->key_1, data->value_1, data->key_2, data->value_2, &defUtoLua);
    if(data->value_1)
      free(data->value_1);
    data->value_1 = 0;
    m_callbacksQueue.EraseSwap(i--);
  }
}
#endif
