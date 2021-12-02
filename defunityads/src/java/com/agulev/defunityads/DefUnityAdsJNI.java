package com.agulev.defunityads;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.view.Gravity;
import android.os.Build;

import com.unity3d.ads.IUnityAdsInitializationListener;
import com.unity3d.ads.IUnityAdsShowListener;
import com.unity3d.ads.IUnityAdsLoadListener;
import com.unity3d.ads.UnityAds;

import com.unity3d.services.banners.view.BannerPosition;
import com.unity3d.services.banners.BannerView;
import com.unity3d.services.banners.UnityBannerSize;
import com.unity3d.services.banners.BannerErrorInfo;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

public class DefUnityAdsJNI {

    private static final String TAG = "DefUnityAdsJNI";

    public static native void unityadsAddToQueue(int msg, String json);

    // duplicate of enums from unityads_callback_private.h:
    // CONSTANTS:

    private static final int MSG_INIT=                    1;
    private static final int MSG_SHOW =                   2;
    private static final int MSG_LOAD =                   3;
    private static final int MSG_BANNER =                 4;
    private static final int MSG_IDFA =                   5;

    private static final int EVENT_COMPLETED =            1;
    private static final int EVENT_SDK_ERROR =            2;
    private static final int EVENT_JSON_ERROR =           3;
    private static final int EVENT_CLICKED =              4;
    private static final int EVENT_START =                5;
    private static final int EVENT_LOADED =               6;
    private static final int EVENT_LEFT_APPLICATION =     7;
    private static final int EVENT_SKIPPED =              8;
    private static final int EVENT_NOT_SUPPORTED =        9;

    private static final int ERROR_INTERNAL =             1;
    private static final int ERROR_INVALID_ARGUMENT =     2;
    private static final int ERROR_NOT_INITIALIZED =      3;
    private static final int ERROR_NOT_READY =            4;
    private static final int ERROR_VIDEO_PLAYER =         5;
    private static final int ERROR_NO_CONNECTION =        6;
    private static final int ERROR_ALREADY_SHOWING =      7;
    private static final int ERROR_NO_FILL =              8;
    private static final int ERROR_TIMEOUT =              9;
    private static final int ERROR_UNKNOWN =             10;
    private static final int ERROR_NATIVE =              11;
    private static final int ERROR_WEBVIEW =             12;
    private static final int ERROR_AD_BLOCKER_DETECTED = 13;


    // END CONSTANTS

    //-----

    private Activity activity;

    public DefUnityAdsJNI(Activity appActivity) {
        activity = appActivity;
    }

    // https://www.baeldung.com/java-json-escaping
    private String getJsonConversionErrorMessage(String messageText) {
        String message = null;
          try {
              JSONObject obj = new JSONObject();
              obj.put("error", messageText);
              obj.put("event", EVENT_JSON_ERROR);
              message = obj.toString();
          } catch (JSONException e) {
              message = "{ \"error\": \"Error while converting simple message to JSON.\", \"event\": "+EVENT_JSON_ERROR+" }";
          }
        return message;
    }

    private void sendSimpleMessage(int msg, int eventId) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      unityadsAddToQueue(msg, message);
    }

    private void sendSimpleMessage(int msg, int eventId, String key_2, String value_2) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          obj.put(key_2, value_2);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      unityadsAddToQueue(msg, message);
    }

    private void sendSimpleMessage(int msg, int eventId, String key_2, int value_2, String key_3, String value_3) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          obj.put(key_2, value_2);
          obj.put(key_3, value_3);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      unityadsAddToQueue(msg, message);
    }

    private void sendSimpleMessage(int msg, int eventId, String key_2, int value_2, String key_3, String value_3, String key_4, String value_4) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          obj.put(key_2, value_2);
          obj.put(key_3, value_3);
          obj.put(key_4, value_4);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      unityadsAddToQueue(msg, message);
    }

    public void initialize(String gameId, boolean testMode) {
        UnityAds.initialize(activity.getApplicationContext(), gameId, testMode, new IUnityAdsInitializationListener() {
            @Override
            public void onInitializationComplete() {
                sendSimpleMessage(MSG_INIT, EVENT_COMPLETED);
            }

            @Override
            public void onInitializationFailed(UnityAds.UnityAdsInitializationError error, String message) {
                int code = 1;
                switch (error) {
                    case INTERNAL_ERROR:
                        code = ERROR_INTERNAL;
                        break;
                    case INVALID_ARGUMENT:
                        code = ERROR_INVALID_ARGUMENT;
                        break;
                    case AD_BLOCKER_DETECTED:
                        code = ERROR_AD_BLOCKER_DETECTED;
                        break;
                }
                sendSimpleMessage(MSG_INIT, EVENT_SDK_ERROR, "code", code,"error", message);
            }
        });
    }

    public void show(String placementId) {
        UnityAds.show(activity, placementId, new IUnityAdsShowListener() {
            @Override
            public 
            void onUnityAdsShowFailure(String placementId, UnityAds.UnityAdsShowError error, String message) {
                int code = 1;
                switch (error) {
                    case NOT_INITIALIZED:
                        code = ERROR_NOT_INITIALIZED;
                        break;
                    case NOT_READY:
                        code = ERROR_NOT_READY;
                        break;
                    case VIDEO_PLAYER_ERROR:
                        code = ERROR_VIDEO_PLAYER;
                        break;
                    case INVALID_ARGUMENT:
                        code = ERROR_INVALID_ARGUMENT;
                        break;
                    case NO_CONNECTION:
                        code = ERROR_NO_CONNECTION;
                        break;
                    case ALREADY_SHOWING:
                        code = ERROR_ALREADY_SHOWING;
                        break;
                    case INTERNAL_ERROR:
                        code = ERROR_INTERNAL;
                        break;
                }
                sendSimpleMessage(MSG_SHOW, EVENT_SDK_ERROR, "code", code,"error", message, "placement_id", placementId);
            }

            @Override
            public void onUnityAdsShowStart(String placementId) {
                sendSimpleMessage(MSG_SHOW, EVENT_START, "placement_id", placementId);
            }

            @Override
            public void onUnityAdsShowClick(String placementId) {
                sendSimpleMessage(MSG_SHOW, EVENT_CLICKED, "placement_id", placementId);
            }

            @Override
            public void onUnityAdsShowComplete(String placementId, UnityAds.UnityAdsShowCompletionState state) {
               int event = 1;
                switch (state) {
                    case SKIPPED:
                        event = EVENT_SKIPPED;
                        break;
                    case COMPLETED:
                        event = EVENT_COMPLETED;
                        break;
                }
                sendSimpleMessage(MSG_SHOW, event, "placement_id", placementId);

            }
        });
    }

    public void load(String placementId) {
        UnityAds.load(placementId, new IUnityAdsLoadListener() {
            @Override
            public void onUnityAdsAdLoaded(String placementId) {
                sendSimpleMessage(MSG_LOAD, EVENT_LOADED, "placement_id", placementId);
            }

            @Override
            public void onUnityAdsFailedToLoad(String placementId, UnityAds.UnityAdsLoadError error, String message) {
                int code = 1;
                switch (error) {
                    case INITIALIZE_FAILED:
                        code = ERROR_NOT_INITIALIZED;
                        break;
                    case INTERNAL_ERROR:
                        code = ERROR_INTERNAL;
                        break;
                    case INVALID_ARGUMENT:
                        code = ERROR_INVALID_ARGUMENT;
                        break;
                    case NO_FILL:
                        code = ERROR_NO_FILL;
                        break;
                    case TIMEOUT:
                        code = ERROR_TIMEOUT;
                        break;
                }
                sendSimpleMessage(MSG_LOAD, EVENT_SDK_ERROR, "code", code,"error", message, "placement_id", placementId);
            }
        });
    }

    public void setDebugMode(boolean debugMode) {
        UnityAds.setDebugMode(debugMode);
    }

    public boolean getDebugMode() {
        return UnityAds.getDebugMode();
    }

    public boolean isInitialized() {
        return UnityAds.isInitialized();
    }

    public boolean isSupported() {
        return UnityAds.isSupported();
    }

    public String getVersion() {
        return UnityAds.getVersion();
    }

    public void requestIDFA() {
        sendSimpleMessage(MSG_IDFA, EVENT_NOT_SUPPORTED);
    }

//Banners:

    private BannerView bannerView;
    private LinearLayout layout;
    private WindowManager.LayoutParams windowParams;
    private BannerPosition m_bannerPosition = BannerPosition.TOP_CENTER;

    private boolean isShown = false;

    private void ApplyBannerPosition() {

    }

    public void setBannerPosition(String position) {
        m_bannerPosition = BannerPosition.fromString(position);
        if (isShown) {
            _hideBanner();
            showBanner();
        }
    }

    public void loadBanner(String placementId, int width, int height) {
        if (bannerView == null) {
            BannerView banner = new BannerView(activity, placementId, new UnityBannerSize(width, height));
            banner.setListener(new BannerView.IListener() {
                @Override
                public void onBannerLoaded(BannerView bannerAdView) {
                    bannerView = bannerAdView;

                    layout = new LinearLayout(activity);
                    layout.setOrientation(LinearLayout.VERTICAL);

                    MarginLayoutParams params = new MarginLayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
                    params.setMargins(0, 0, 0, 0);

                    layout.addView(bannerView, params);

                    windowParams = new WindowManager.LayoutParams();
                    windowParams.x = WindowManager.LayoutParams.WRAP_CONTENT;
                    windowParams.y = WindowManager.LayoutParams.WRAP_CONTENT;
                    windowParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
                    windowParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
                    windowParams.flags = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;

                    sendSimpleMessage(MSG_BANNER, EVENT_LOADED, "placement_id", bannerAdView.getPlacementId());
                }

                @Override
                public void onBannerFailedToLoad(BannerView bannerAdView, BannerErrorInfo errorInfo) {
                    int code = 1;
                    switch (errorInfo.errorCode) {
                        case UNKNOWN:
                            code = ERROR_UNKNOWN;
                            break;
                        case NATIVE_ERROR:
                            code = ERROR_NATIVE;
                            break;
                        case WEBVIEW_ERROR:
                            code = ERROR_WEBVIEW;
                            break;
                        case NO_FILL:
                            code = ERROR_NO_FILL;
                            break;
                        }
                    sendSimpleMessage(MSG_BANNER, EVENT_SDK_ERROR, "code", code,"error", errorInfo.errorMessage, "placement_id", bannerAdView.getPlacementId());
                }

                @Override
                public void onBannerClick(BannerView bannerAdView) {
                    sendSimpleMessage(MSG_BANNER, EVENT_CLICKED, "placement_id", bannerAdView.getPlacementId());
                }

                @Override
                public void onBannerLeftApplication(BannerView bannerAdView) {
                    sendSimpleMessage(MSG_BANNER, EVENT_LEFT_APPLICATION, "placement_id", bannerAdView.getPlacementId());
                }
            });
            banner.load();
        }
    }

    private void _unloadBanner() {
        bannerView.destroy();
        layout = null;
        bannerView = null;
        windowParams = null;
        isShown = false;
    }

    public void unloadBanner() {
        if (bannerView == null) {
            return;
        }
        if (!isShown) {
            _unloadBanner();
        } else {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    WindowManager wm = activity.getWindowManager();
                    wm.removeView(layout);
                    _unloadBanner();
                }

            });
        }
    }

    private void _hideBanner() {
        if (!isShown) {
            return;
        }

        isShown = false;
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                WindowManager wm = activity.getWindowManager();
                wm.removeView(layout);
            }

        });
    }

    public void showBanner() {
        if (isShown || bannerView == null) {
            return;
        }
        isShown = true;
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                WindowManager wm = activity.getWindowManager();
                windowParams.gravity = m_bannerPosition.getGravity();
                wm.addView(layout, windowParams);
            }
        });
    }

    public void hideBanner() {
        if (bannerView == null) {
            return;
        }

        _hideBanner();
    }
}
