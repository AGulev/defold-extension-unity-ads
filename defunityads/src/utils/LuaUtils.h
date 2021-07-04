#pragma once

#include <dmsdk/sdk.h>

namespace dmUnityAds {

    bool luaL_checkbool(lua_State *L, int numArg);
    void luaL_push_pair_str_num(lua_State *L, const char *key, int value);
    void luaL_push_pair_str_str(lua_State *L, const char *key, const char *value);

}//namespace dmUnityAds
