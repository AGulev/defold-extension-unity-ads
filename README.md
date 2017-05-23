# DefUnityAds

This is [UnityAds](https://unity3d.com/ru/services/ads) native extension for [Defold engine](http://www.defold.com).
Extension supported IOS and Android.

## Installation

You can use the DefUnityAds extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).
Open your game.project file and in the dependencies field under project add:

>https://github.com/AGulev/DefUnityAds/archive/master.zip

##### Android only
Set `defunityads/AndroindManifest.xml` as default manifest for your project or add the next Activities to your manifest:
```xml
<!-- For DefUnityAds -->
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
## Known issues

- Extension do not support [getPlacementState](https://github.com/Unity-Technologies/unity-ads-ios/wiki/sdk_ios_api_reference#getplacementstate) method.

## Example

See the [example folder](https://github.com/AGulev/DefUnityAds/tree/master/example) for understand how to use extension. Especially [def_unity_ads.script](https://github.com/AGulev/DefUnityAds/blob/master/example/def_unity_ads.script) file.

![Example screenshot](https://cdn.rawgit.com/AGulev/DefUnityAds/2f17110e/example/example_screenshot.png)


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

If you have any questions or suggestions contact me: me@agulev.com
