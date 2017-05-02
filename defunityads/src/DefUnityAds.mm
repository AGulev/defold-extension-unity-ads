#include <dmsdk/sdk.h>
#include "DefUnityAds_private.h"

#if defined(DM_PLATFORM_IOS)

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>
#include <UnityAds/UnityAds.h>

struct DispatchToLua {
    DefUnityAdsListener listener;
} g_DefUAds;

DispatchToLua* defUtoLua;

@interface DefUnityAdsDelegate : UIViewController<UnityAdsDelegate>{
}

@end

@interface DefUnityAdsDelegate ()
-(int)error_convert:(UnityAdsError)error;
-(int)finish_state_convert:(UnityAdsFinishState)state;
@end

@implementation DefUnityAdsDelegate

-(int)error_convert:(UnityAdsError)error {
    switch(error){
        case kUnityAdsErrorNotInitialized:
            return (int)ERROR_NOT_INITIALIZED;
            break;
        case kUnityAdsErrorInitializedFailed:
            return (int)ERROR_INITIALIZED_FAILED;
            break;
        case kUnityAdsErrorInvalidArgument:
            return (int)ERROR_INVALID_ARGUMENT;
            break;
        case kUnityAdsErrorVideoPlayerError:
            return (int)ERROR_VIDEO_PLAYER;
            break;
        case kUnityAdsErrorInitSanityCheckFail:
            return (int)ERROR_INIT_SANITY_CHECK_FAIL;
            break;
        case kUnityAdsErrorAdBlockerDetected:
            return (int)ERROR_AD_BLOCKER_DETECTED;
            break;
        case kUnityAdsErrorFileIoError:
            return (int)ERROR_FILE_IO;
            break;
        case kUnityAdsErrorDeviceIdError:
            return (int)ERROR_DEVICE_ID;
            break;
        case kUnityAdsErrorShowError:
            return (int)ERROR_SHOW;
            break;
        case kUnityAdsErrorInternalError:
            return (int)ERROR_INTERNAL;
            break;
    }
    return(-1);
}

-(int)finish_state_convert:(UnityAdsFinishState)state {
    switch(state){
        case kUnityAdsFinishStateError:
            return (int)FINISH_STATE_ERROR;
            break;
        case kUnityAdsFinishStateSkipped:
            return (int)FINISH_STATE_SKIPPED;
            break;
        case kUnityAdsFinishStateCompleted:
            return (int)FINISH_STATE_COMPLETED;
            break;
    }
    return(-1);
}

- (void)didReceiveMemoryWarning {
    NSLog(@"didReceiveMemoryWarning\n");
}

-(void)unityAdsReady:(NSString *)placementId {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
    
    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_IS_READY);
    
    const char *placementId_lua = [placementId UTF8String];
    lua_createtable(L, 0, 1);
    lua_pushstring(L, "placementId");
   	lua_pushstring(L, placementId_lua);
    lua_settable(L, -3);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}
-(void)unityAdsDidStart:(NSString *)placementId {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
    
    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_DID_START);
    
    const char *placementId_lua = [placementId UTF8String];
    lua_createtable(L, 0, 1);
    lua_pushstring(L, "placementId");
   	lua_pushstring(L, placementId_lua);
    lua_settable(L, -3);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}
-(void)unityAdsDidError:(UnityAdsError)error withMessage:(NSString *)message {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
    
    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_DID_ERROR);
    
    const char *message_lua = [message UTF8String];
    lua_createtable(L, 0, 2);
    lua_pushstring(L, "message");
   	lua_pushstring(L, message_lua);
    lua_settable(L, -3);
    lua_pushstring(L, "error");
   	lua_pushnumber(L, [self error_convert:error]);
    lua_settable(L, -3);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}
-(void)unityAdsDidFinish:(NSString *)placementId withFinishState:(UnityAdsFinishState)state {
    lua_State* L = defUtoLua->listener.m_L;
    int top = lua_gettop(L);
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
    
    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushnumber(L, (int)TYPE_DID_FINISH);
    
    const char *placementId_lua = [placementId UTF8String];
    lua_createtable(L, 0, 2);
    lua_pushstring(L, "placementId");
   	lua_pushstring(L, placementId_lua);
    lua_settable(L, -3);
    lua_pushstring(L, "state");
   	lua_pushnumber(L, [self finish_state_convert:state]);
    lua_settable(L, -3);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defUtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}

@end

DefUnityAdsDelegate *unityAds;

void DefUnityAds_Initialize(lua_State* L) {
    const char *gameId_lua = luaL_checkstring(L, 1);
    NSString* gameId = [NSString stringWithUTF8String:gameId_lua];
    
    UIView *view = dmGraphics::GetNativeiOSUIView();
    unityAds = [[DefUnityAdsDelegate alloc] init];
    unityAds.view.bounds = view.bounds;
    [view addSubview:unityAds.view];
    
    [UnityAds initialize:gameId delegate:unityAds];
    
    defUtoLua = &g_DefUAds;
    
    luaL_checktype(L, 2, LUA_TFUNCTION);
    lua_pushvalue(L, 2);
    int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);
    
    if (defUtoLua->listener.m_Callback != LUA_NOREF) {
        dmScript::Unref(defUtoLua->listener.m_L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Callback);
        dmScript::Unref(defUtoLua->listener.m_L, LUA_REGISTRYINDEX, defUtoLua->listener.m_Self);
    }
    
    defUtoLua->listener.m_L = dmScript::GetMainThread(L);
    defUtoLua->listener.m_Callback = cb;
    dmScript::GetInstance(L);
    defUtoLua->listener.m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
    
    if (lua_type(L, 3) != LUA_TNONE){
        bool enableDebugMode_lua = luaL_checkbool(L, 3);
        BOOL enableDebugMode = enableDebugMode_lua ? YES : NO;
        [UnityAds setDebugMode:enableDebugMode];
    }
}

void DefUnityAds_Show(lua_State* L) {
    if (lua_type(L, 1) != LUA_TNONE){
        const char *placementId_lua = luaL_checkstring(L, 1);
        NSString* placementId = [NSString stringWithUTF8String:placementId_lua];
        [UnityAds show:unityAds placementId:placementId];
    }
    else{
        [UnityAds show:unityAds];
    }
}

void DefUnityAds_setDebugMode(lua_State* L) {
    bool enableDebugMode_lua = luaL_checkbool(L, 1);
    BOOL enableDebugMode = enableDebugMode_lua ? YES : NO;
    [UnityAds setDebugMode:enableDebugMode];
}

bool DefUnityAds_isReady(lua_State* L) {
    BOOL status;
    if (lua_type(L, 1) != LUA_TNONE){
        const char *placementId_lua = luaL_checkstring(L, 1);
        NSString* placementId = [NSString stringWithUTF8String:placementId_lua];
        status = [UnityAds isReady:placementId];
    }
    else{
        status = [UnityAds isReady];
    }
    return status == YES;
}

bool DefUnityAds_isSupported() {
    BOOL status = [UnityAds isSupported];
    return status == YES;
}

bool DefUnityAds_isInitialized() {
    BOOL status = [UnityAds isInitialized];
    return status == YES;
}

bool DefUnityAds_getDebugMode() {
    BOOL status = [UnityAds getDebugMode];
    return status == YES;
}

char const* DefUnityAds_getVersion() {
    NSString *version = [UnityAds getVersion];
    const char *version_lua = [version UTF8String];
    return version_lua;
}

bool luaL_checkbool(lua_State *L, int numArg)
{
    bool b = false;
    if (lua_isboolean(L, numArg))
    {
        b = lua_toboolean(L, numArg);
    }
    else
    {
        luaL_typerror(L, numArg, lua_typename(L, LUA_TBOOLEAN));
    }
    return b;
}

#endif
