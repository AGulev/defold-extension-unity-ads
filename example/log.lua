local M ={}
if unityads then
    
local MSGS = {
    [unityads.MSG_INIT] = "MSG_INIT",
    [unityads.MSG_SHOW] = "MSG_SHOW",
    [unityads.MSG_LOAD] = "MSG_LOAD",
    [unityads.MSG_BANNER] = "MSG_BANNER",
    [unityads.MSG_IDFA] = "MSG_IDFA",
}

local EVENTS = {
    [unityads.EVENT_COMPLETED] = "EVENT_COMPLETED",
    [unityads.EVENT_SDK_ERROR] = "EVENT_SDK_ERROR",
    [unityads.EVENT_JSON_ERROR] = "EVENT_JSON_ERROR",
    [unityads.EVENT_CLICKED] = "EVENT_CLICKED",
    [unityads.EVENT_START] = "EVENT_START",
    [unityads.EVENT_LOADED] = "EVENT_LOADED",
    [unityads.EVENT_LEFT_APPLICATION] = "EVENT_LEFT_APPLICATION",
    [unityads.EVENT_SKIPPED] = "EVENT_SKIPPED",
    [unityads.EVENT_NOT_SUPPORTED] = "EVENT_NOT_SUPPORTED",
    [unityads.EVENT_STATUS_AUTORIZED] = "EVENT_STATUS_AUTORIZED",
    [unityads.EVENT_STATUS_DENIED] = "EVENT_STATUS_DENIED",
    [unityads.EVENT_STATUS_NOT_DETERMINED] = "EVENT_STATUS_NOT_DETERMINED",
    [unityads.EVENT_STATUS_RESTRICTED] = "EVENT_STATUS_RESTRICTED",
}

local ERRORS = {
    [unityads.ERROR_INTERNAL] = "ERROR_INTERNAL",
    [unityads.ERROR_INVALID_ARGUMENT] = "ERROR_INVALID_ARGUMENT",
    [unityads.ERROR_NOT_INITIALIZED] = "ERROR_NOT_INITIALIZED",
    [unityads.ERROR_NOT_READY] = "ERROR_NOT_READY",
    [unityads.ERROR_VIDEO_PLAYER] = "ERROR_VIDEO_PLAYER",
    [unityads.ERROR_NO_CONNECTION] = "ERROR_NO_CONNECTION",
    [unityads.ERROR_ALREADY_SHOWING] = "ERROR_ALREADY_SHOWING",
    [unityads.ERROR_NO_FILL] = "ERROR_NO_FILL",
    [unityads.ERROR_TIMEOUT] = "ERROR_TIMEOUT",
    [unityads.ERROR_UNKNOWN] = "ERROR_UNKNOWN",
    [unityads.ERROR_NATIVE] = "ERROR_NATIVE",
    [unityads.ERROR_WEBVIEW] = "ERROR_WEBVIEW",
    [unityads.ERROR_AD_BLOCKER_DETECTED] = "ERROR_AD_BLOCKER_DETECTED",
}

function M.get_msg_log(message_id, message)
    local str = MSGS[message_id].." "..EVENTS[message.event]
    if message.placement_id then
        str = str.. " placement_id:"..message.placement_id
    end
    if message.code then
        str = str.. " error_code:"..ERRORS[message.code]
    end
    if message.error then
        str = str.. " error:"..message.error
    end
    return str
end
end

return M
