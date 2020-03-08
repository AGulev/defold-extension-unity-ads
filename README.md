_“This plugin is not endorsed or sponsored by Unity Technologies. This is an independent, unofficial plugin. UNITY and the Unity logo are Unity Technologies’ registered trademarks in the US and other countries--All rights reserved.“_

![defvideoads-01](https://user-images.githubusercontent.com/2209596/50695591-6086b080-103d-11e9-9a94-77929169199e.png)

# DefVideoAds (plugin for Unity ADS)

This is [UnityAds](https://unity3d.com/ru/services/ads) native extension for [Defold engine](http://www.defold.com).
Extension supported IOS (minimum iOS version is 9.0) and Android.

## Installation

You can use the DefVideoAds extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).
Open your game.project file and in the dependencies field under project add:

>https://github.com/AGulev/DefVideoAds/archive/master.zip

or point to the ZIP file of a [specific release](https://github.com/AGulev/DefVideoAds/releases).

## Example

See the [example folder](https://github.com/AGulev/DefVideoAds/tree/master/example) for understand how to use extension. Especially [ui.gui_script](https://github.com/AGulev/DefVideoAds/blob/master/example/ui.gui_script) file.

![Example screenshot](https://user-images.githubusercontent.com/2209596/60367270-1b40ab80-99ee-11e9-87e8-7dc9f8108615.gif)


## LUA Api
Please, read [Android API docs](https://docs.unity3d.com/Packages/com.unity.ads@3.4/manual/MonetizationResourcesApiAndroid.html) and [iOS API docs](https://docs.unity3d.com/Packages/com.unity.ads@3.4/manual/MonetizationResourcesApiIos.html)
### Methods
#### unityads.initialize(gameID, callback)
#### unityads.initialize(gameID, callback, testMode)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#initialize)
```lua
local function defunityads_callback(self, msg_type, message)
...
end
...
unityads.initialize("1401815", defunityads_callback) -- testMode is optional parameter
unityads.initialize("1401815", defunityads_callback, true) -- testMode is optional parameter
```


#### unityads.setCallback(callback)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_android_api_reference#unityadssetlistener)
```lua
unityads.setCallback(defunityads_callback) -- set callback
unityads.setCallback(nil) -- remove callback
unityads.setCallback() -- remove callback
```


#### unityads.setDebugMode(isDebug)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#setdebugmode)
```lua
unityads.setDebugMode(true) -- set debug mod
```

#### unityads.getDebugMode()
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#getdebugmode)
```lua
unityads.getDebugMode() -- Returns true if current mod is debug
```

#### unityads.getPlacementState()
#### unityads.getPlacementState(placementId)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#getplacementstate)
```lua
unityads.getPlacementState() -- Returns a default ad state
unityads.getPlacementState("rewardedVideo") -- Returns rewardedVideo ad state

--possible states:
unityads.PLACEMENT_STATE_READY
unityads.PLACEMENT_STATE_NOT_AVAILABLE
unityads.PLACEMENT_STATE_DISABLED
unityads.PLACEMENT_STATE_WAITING
unityads.PLACEMENT_STATE_NO_FILL
```

#### unityads.isReady()
#### unityads.isReady(placementId)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#isready)
```lua
unityads.isReady() -- Returns true if default ad is ready
unityads.isReady("rewardedVideo") -- Returns true if rewardedVideo is ready
```

#### unityads.isInitialized()
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#isinitialized)
```lua
unityads.isInitialized() -- Returns true if Unity ADS initialized
```

#### unityads.isSupported()
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#issupported)
```lua
unityads.isSupported() -- Returns true if Unity Ads is supported by the current device
```

#### unityads.getVersion()
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#getversion)
```lua
unityads.getVersion() -- Returns the Unity Ads SDK version as a string.
```

#### unityads.show()
#### unityads.show(placementId)
[original doc](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#show)
```lua
unityads.show() -- show default ad
unityads.show("rewardedVideo") -- show rewardedVideo
```
#### unityads.loadBanner(placementId)
#### unityads.loadBanner(placementId, banner_width, banner_height)
```lua
unityads.loadBanner("banner") -- load banner, by defaulf width = 320, height = 50
unityads.loadBanner("banner", 320, 50) -- load banner
```
#### unityads.unloadBanner()
```lua
unityads.unloadBanner() -- unload banner
```
#### unityads.showBanner()
```lua
unityads.showBanner() -- show loaded banner
```
#### unityads.hideBanner()
```lua
unityads.hideBanner() -- hide banner
```
#### unityads.setBannerPosition(position)
```lua
unityads.setBannerPosition(position) -- set position of the banner
-- default value is unityads.BANNER_POSITION_TOP_CENTER
--possible positions:
unityads.BANNER_POSITION_TOP_LEFT
unityads.BANNER_POSITION_TOP_CENTER
unityads.BANNER_POSITION_TOP_RIGHT
unityads.BANNER_POSITION_BOTTOM_LEFT
unityads.BANNER_POSITION_BOTTOM_CENTER
unityads.BANNER_POSITION_BOTTOM_RIGHT
unityads.BANNER_POSITION_CENTER
```

### Constants
```lua
local function defunityads_callback(self, msg_type, message)
...
end
```
#### Message types
```lua
--possible msg_type :
unityads.TYPE_IS_READY
unityads.TYPE_DID_START
unityads.TYPE_DID_ERROR
unityads.TYPE_DID_FINISH
unityads.TYPE_BANNER
unityads.TYPE_BANNER_ERROR
```
##### unityads.TYPE_IS_READY
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_IS_READY then
    pprint(message) -- message = {placementId = "string"}
  end
end
```
##### unityads.TYPE_DID_START
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_DID_START then
    pprint(message) -- message = {placementId = "string"}
  end
end
```
##### unityads.TYPE_DID_ERROR
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_DID_ERROR then
    pprint(message) -- message = {error = ERROR_*, message = "string"}
  end
end
```
##### unityads.TYPE_DID_FINISH
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_DID_FINISH then
    pprint(message) -- message = {state = FINISH_STATE_*, placementId = "string"}
  end
end
```
##### unityads.TYPE_BANNER
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_BANNER then
      if message.event == BANNER_EVENT_DID_LOAD then
        pprint(message) -- message = {event = BANNER_EVENT_*, placementId = "string"}
      end
  end
end
```
##### unityads.TYPE_BANNER_ERROR
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_BANNER_ERROR then
      pprint(message) -- message = {error = BANNER_ERROR_*, message = "string"}
  end
end
```
#### Error types
[Original doc about error types](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_errors)
```lua
--possible message.error for unityads.TYPE_DID_ERROR:
unityads.ERROR_NOT_INITIALIZED --kUnityAdsErrorNotInitialized
unityads.ERROR_INITIALIZED_FAILED --kUnityAdsErrorInitializedFailed
unityads.ERROR_INVALID_ARGUMENT --kUnityAdsErrorInvalidArgument
unityads.ERROR_VIDEO_PLAYER --kUnityAdsErrorVideoPlayerError
unityads.ERROR_INIT_SANITY_CHECK_FAIL --kUnityAdsErrorInitSanityCheckFail
unityads.ERROR_AD_BLOCKER_DETECTED --kUnityAdsErrorAdBlockerDetected
unityads.ERROR_FILE_IO --kUnityAdsErrorFileIoError
unityads.ERROR_DEVICE_ID --kUnityAdsErrorDeviceIdError
unityads.ERROR_SHOW --kUnityAdsErrorShowError
unityads.ERROR_INTERNAL --kUnityAdsErrorInternalError
```
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_DID_ERROR then
    if message.error == unityads.ERROR_NOT_INITIALIZED then
      ...
    elseif message.error == unityads.ERROR_INITIALIZED_FAILED then
    ...
  end
end
```
#### Banner error types
[Original doc about error types](https://docs.unity3d.com/Packages/com.unity.ads@3.4/manual/MonetizationResourcesApiAndroid.html#bannerview)
```lua
--possible message.error for unityads.TYPE_BANNER_ERROR:
unityads.BANNER_ERROR_UNKNOWN --
unityads.BANNER_ERROR_NATIVE
unityads.BANNER_ERROR_WEBVIEW
unityads.BANNER_ERROR_NOFILL
```
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_BANNER_ERROR then
    if message.error == unityads.BANNER_ERROR_UNKNOWN then
      ...
    elseif message.error == unityads.BANNER_ERROR_NATIVE then
    ...
  end
end
```
#### Finish states
[Original doc about finish states](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_finishstates)
```lua
--possible message.state :
unityads.FINISH_STATE_ERROR --kUnityAdsFinishStateError
unityads.FINISH_STATE_SKIPPED --kUnityAdsFinishStateSkipped
unityads.FINISH_STATE_COMPLETED --kUnityAdsFinishStateCompleted
```
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_DID_FINISH then
    if message.state == unityads.FINISH_STATE_ERROR then
      ...
    elseif message.state == unityads.FINISH_STATE_SKIPPED then
    ...
  end
end
```
#### Banner events
```lua
--possible banner events:
unityads.BANNER_EVENT_DID_LOAD
unityads.BANNER_EVENT_DID_CLICK
unityads.BANNER_EVENT_DID_LEAVE_APP
```
```lua
local function defunityads_callback(self, msg_type, message)
  if msg_type == unityads.TYPE_BANNER then
    if message.event == unityads.BANNER_EVENT_DID_LOAD then
      ...
    elseif message.event == unityads.BANNER_EVENT_DID_CLICK then
    ...
  end
end
```

---

If you have any issues, questions or suggestions please [create an issue](https://github.com/AGulev/DefVideoAds/issues) or contact me: me@agulev.com
