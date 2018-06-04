_“This plugin is not endorsed or sponsored by Unity Technologies. This is an independent, unofficial plugin. UNITY and the Unity logo are Unity Technologies’ registered trademarks in the US and other countries--All rights reserved.“_

![DefVideoAds (plugin for Unity ADS)](https://user-images.githubusercontent.com/2209596/40907996-32afc3ec-67ee-11e8-987f-9b536a8820a3.jpg)

# DefVideoAds (plugin for Unity ADS)

This is [UnityAds](https://unity3d.com/ru/services/ads) native extension for [Defold engine](http://www.defold.com).
Extension supported IOS and Android.

## Installation

You can use the DefVideoAds extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).
Open your game.project file and in the dependencies field under project add:

>https://github.com/AGulev/DefVideoAds/archive/master.zip

##### Android installation info
Set `defunityads/AndroindManifest.xml` as default manifest for your project or add the next Activities to your manifest:
```xml
<!-- For DefVideoAds -->
<activity
android:name="com.unity3d.ads.adunit.AdUnitActivity"
android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
android:hardwareAccelerated="true"
android:theme="@android:style/Theme.NoTitleBar.Fullscreen" />
<activity
android:name="com.unity3d.ads.adunit.AdUnitSoftwareActivity"
android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
android:hardwareAccelerated="false"
android:theme="@android:style/Theme.NoTitleBar.Fullscreen" />
```

## Example

See the [example folder](https://github.com/AGulev/DefVideoAds/tree/master/example) for understand how to use extension. Especially [ui.gui_script](https://github.com/AGulev/DefVideoAds/blob/master/example/ui.gui_script) file.

![Example screenshot](https://user-images.githubusercontent.com/2209596/40448649-cf08e002-5ede-11e8-9681-c20d17c0512a.jpg)


## LUA Api
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
    pprint(message) -- message = {state = ERROR_*, message = "string"}
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
#### Error types
[Original doc about error types](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_errors)
```lua
--possible message.error :
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

If you have any questions or suggestions contact: me@agulev.com
