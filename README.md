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

`Minimum SDK version` in `game.project->Android` should be 19 or above.

<img width="791" alt="image" src="https://user-images.githubusercontent.com/2209596/119895871-8ed2f680-bf3e-11eb-90bc-cf3159a76d0a.png">


## Example

See the [example folder](https://github.com/AGulev/DefVideoAds/tree/master/example) for understand how to use extension. Especially [ui.gui_script](https://github.com/AGulev/DefVideoAds/blob/master/example/ui.gui_script) file.

![Example](https://user-images.githubusercontent.com/2209596/124395653-8ae88000-dd05-11eb-99e3-ed09bfadc850.gif)



## LUA Api
Please, read [Android API docs](https://unityads.unity3d.com/help/android/api-android#iunityadsshowlistener) and [iOS API docs](https://unityads.unity3d.com/help/ios/api-ios#unityadsloaddelegate)
### Methods

#### unityads.request_idfa()
```lua
unityads.request_idfa()
-- iOS only method that shows IDFA request popup.
-- On Android it always fire callback with MSG_IDFA/EVENT_NOT_SUPPORTED
-- should be called before initialization
```

#### unityads.initialize(game_id, callback)
#### unityads.initialize(game_id, callback, test_mode)
#### unityads.initialize(game_id, callback, test_mode, enable_per_placement_load)

Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#initialize) [Android](https://unityads.unity3d.com/help/android/api-android#initialize)
```lua
local function defunityads_callback(self, message_id, message)
...
end
...
unityads.initialize("1401815", defunityads_callback)
 -- `test_mode` is optional parameter:
unityads.initialize("1401815", defunityads_callback, true)
 -- `enable_per_placement_load` is optional parameter:
unityads.initialize("1401815", defunityads_callback, true, true)
-- When `enable_per_placement_load` set to true,
-- this parameter allows you to load content for a specific Placement prior to displaying it 
-- using `load(placement_id)` method
```

#### unityads.set_callback(callback)

```lua
unityads.set_callback(defunityads_callback) -- set callback
unityads.set_callback(nil) -- remove callback
unityads.set_callback() -- remove callback
```


#### unityads.set_debug_mode(is_debug)
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#setdebugmode) [Android](https://unityads.unity3d.com/help/android/api-android#setdebugmode)
```lua
unityads.set_debug_mode(true) -- set debug mode
unityads.set_debug_mode(false) -- set debug mode
```

#### unityads.get_debug_mode()
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#setdebugmode) [Android](https://unityads.unity3d.com/help/android/api-android#setdebugmode)
```lua
local is_debig_mode = unityads.getDebugMode() -- Returns true if current mod is debug
```

#### unityads.get_placement_state()
#### unityads.get_placement_state(placement_id)
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#unityadsplacementstate) [Android](https://unityads.unity3d.com/help/android/api-android#placementstate)
```lua
```lua
local state = unityads.get_placement_state("rewardedVideo") -- Returns `rewardedVideo` ad state

--possible states:
unityads.PLACEMENT_STATE_READY -- The Placement is ready to show ads.
unityads.PLACEMENT_STATE_NOT_AVAILABLE -- The Placement is not available.
unityads.PLACEMENT_STATE_DISABLED -- The Placement was disabled.
unityads.PLACEMENT_STATE_WAITING --  The Placement is waiting to be ready.
unityads.PLACEMENT_STATE_NO_FILL -- The Placement has no advertisements to show.
```

#### unityads.is_ready()
#### unityads.is_ready(placement_id)
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#isready) [Android](https://unityads.unity3d.com/help/android/api-android#isready)
```lua
local is_ready = unityads.is_ready("rewardedVideo") -- Returns `true` if rewardedVideo is ready
```

#### unityads.is_initialized()
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#initialize) [Android](https://unityads.unity3d.com/help/android/api-android#initialize)
```lua
local is_initialized = unityads.is_initialized() -- Returns `true` if Unity ADS initialized
```

#### unityads.is_supported()
Original Docs [iOS](https://unityads.unity3d.com/help/ios/api-ios#initialize) [Android](https://unityads.unity3d.com/help/android/api-android#initialize)
```lua
local is_supported = unityads.is_supported() -- Returns `true` if Unity Ads is supported by the current device
```

#### unityads.get_version()
```lua
local version = unityads.get_version() -- Returns the Unity Ads SDK version as a string.
```

#### unityads.show(placement_id)
```lua
unityads.show("rewardedVideo") -- show rewardedVideo
```

#### unityads.load(placement_id)
```lua
unityads.load("rewardedVideo") -- load rewardedVideo
```

#### unityads.load_banner(placement_id)
#### unityads.load_banner(placement_id, banner_width, banner_height)
```lua
unityads.load_banner("banner") -- load banner, by defaulf width = 320, height = 50
unityads.load_banner("banner", 320, 50) -- load banner
```

#### unityads.unload_banner()
```lua
unityads.unload_banner() -- unload banner
```

#### unityads.show_banner()
```lua
unityads.show_banner() -- show banner
```

#### unityads.hide_banner()
```lua
unityads.hide_banner() -- hide banner
```

#### unityads.set_banner_position(position)
```lua
unityads.set_banner_position(position) -- set position of the banner
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
local function defunityads_callback(self, message_id, message)
...
end
```
#### Message types
```lua
--possible values for `message_id` :
unityads.MSG_INIT
unityads.MSG_SHOW
unityads.MSG_LOAD
unityads.MSG_BANNER
unityads.MSG_IDFA
```
##### unityads.MSG_INIT
```lua
local function defunityads_callback(self, message_id, message)
  if message_id == unityads.MSG_INIT then
    if message.event == unityads.EVENT_COMPLETED then
        -- message = {placement_id = "string", ...}
    elseif message.event == unityads.EVENT_SDK_ERROR then
        -- message = {code = int, error = "error message string"}
        if message.code == unityads.ERROR_INTERNAL then
            -- initialization failed due to environment or internal services
        elseif message.code == unityads.ERROR_INVALID_ARGUMENT then
            -- initialization failed due to invalid argument(e.g. game ID)
        elseif message.code == unityads.ERROR_AD_BLOCKER_DETECTED then
            -- initialization failed due to url being blocked
        end
    elseif message.event == unityads.EVENT_JSON_ERROR then
        -- message = {error = "error message string"}
    end
  end
end
```

##### unityads.MSG_SHOW
```lua
local function defunityads_callback(self, message_id, message)
  if message_id == unityads.MSG_SHOW then
    if message.event == unityads.EVENT_COMPLETED then
      -- message = {placement_id = "string"}
      -- An event that indicates that the ad was played entirely.
    elseif message.event == unityads.EVENT_SKIPPED then
        -- message = {placement_id = "string"}
        -- An event that indicates that the user skipped the ad.
    elseif message.event == unityads.EVENT_START then
        -- message = {placement_id = "string"}
        -- UnityAds has started to show ad with a specific placement.
    elseif message.event == unityads.EVENT_CLICKED then
        -- message = {placement_id = "string"}
        -- UnityAds has received a click while showing ad with a specific placement.
    elseif message.event == unityads.EVENT_SDK_ERROR then
        -- message = {code = int, error = "error message string"}
        if message.code == unityads.ERROR_NOT_INITIALIZED then
            -- show failed due to SDK not initialized.
        elseif message.code == unityads.ERROR_NOT_READY then
            --show failed due to placement not being ready.
        elseif message.code == unityads.ERROR_VIDEO_PLAYER then
            -- show failed due to video player.
        elseif message.code == unityads.ERROR_INVALID_ARGUMENT then
            -- show failed due to invalid arguments.
        elseif message.code == unityads.ERROR_NO_CONNECTION then
            -- show failed due to internet connection.
        elseif message.code == unityads.ERROR_ALREADY_SHOWING then
            -- show failed due to ad is already being showen.
        elseif message.code == unityads.ERROR_INTERNAL then
            -- show failed due to environment or internal services.
        end
    elseif message.event == unityads.EVENT_JSON_ERROR then
        -- message = {error = "error message string"}
    end
  end
end
```

##### unityads.MSG_LOAD
```lua
local function defunityads_callback(self, message_id, message)
  if message.event == unityads.EVENT_LOADED then
      -- message = {placement_id = "string"}
      -- Load request has successfully filled the specified placementId with an ad that is ready to show.
  elseif message.event == unityads.EVENT_SDK_ERROR then
      -- message = {code = int, error = "error message string"}
      if message.code == unityads.ERROR_NOT_INITIALIZED then
          -- Error related to SDK not initialized
      elseif message.code == unityads.ERROR_INTERNAL then
          -- Error related to environment or internal services
      elseif message.code == unityads.ERROR_INVALID_ARGUMENT then
          -- Error related to invalid arguments
      elseif message.code == unityads.ERROR_NO_FILL then
          -- Error related to there being no ads available
      elseif message.code == unityads.ERROR_TIMEOUT then
          -- Error related to there being no ads available
      end
  elseif message.event == unityads.EVENT_JSON_ERROR then
      -- message = {error = "error message string"}
  end
end
```

##### unityads.MSG_BANNER
```lua
local function defunityads_callback(self, message_id, message)
  if message.event == unityads.EVENT_LOADED then
      -- message = {placement_id = "string"}
      -- Banner is loaded and ready to be placed in the view hierarchy.
  elseif message.event == unityads.EVENT_LEFT_APPLICATION then
      -- message = {placement_id = "string"}
      -- Banner links outside the application.
  elseif message.event == unityads.EVENT_CLICKED then
      -- message = {placement_id = "string"}
      -- Banner is clicked.
  elseif message.event == unityads.EVENT_SDK_ERROR then
      -- message = {code = int, error = "error message string"}
      if message.code == unityads.ERROR_UNKNOWN then
          -- Unknown error 
      elseif message.code == unityads.ERROR_NATIVE then
          -- Error related to native
      elseif message.code == unityads.ERROR_WEBVIEW then
          -- Error related to webview
      elseif message.code == unityads.ERROR_NO_FILL then
          -- Error related to there being no ads available
      end
  elseif message.event == unityads.EVENT_JSON_ERROR then
      -- message = {error = "error message string"}
  end
end
```

##### unityads.MSG_IDFA
```lua
local function defunityads_callback(self, message_id, message)
  if message.event == unityads.EVENT_NOT_SUPPORTED then
      -- IDFA isn't supported
  elseif message.event == unityads.EVENT_STATUS_AUTORIZED then
  elseif message.event == unityads.EVENT_STATUS_DENIED then
  elseif message.event == unityads.EVENT_STATUS_NOT_DETERMINED then
  elseif message.event == unityads.EVENT_STATUS_RESTRICTED then
  elseif message.event == unityads.EVENT_JSON_ERROR then
      -- message = {error = "error message string"}
  end
end
```

---

If you have any issues, questions or suggestions please [create an issue](https://github.com/AGulev/DefVideoAds/issues) or contact me: me@agulev.com
