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

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.IUnityAdsInitializationListener;
import com.unity3d.ads.UnityAds;

import com.unity3d.services.banners.view.BannerPosition;
import com.unity3d.services.banners.BannerView;
import com.unity3d.services.banners.UnityBannerSize;
import com.unity3d.services.banners.BannerErrorInfo;

public class DefUnityAds {

    public static native void onUnityAdsReady(String placementId);
    public static native void onUnityAdsStart(String placementId);
    public static native void onUnityAdsError(int error, String message);
    public static native void onUnityAdsFinish(String placementId, int result);

    public static native void onUnityBannerLoaded(String placementId);
    public static native void onUnityBannerClick(String placementId);
    public static native void onUnityBannerError(int error, String message);
    public static native void onUnityBannerDidLeaveApp(String placementId);

    public static native void onUnityAdsInitializationError(int error, String message);
    public static native void onUnityAdsInitialized();

    //-----

    private DefUnityAdsListener defUnityAdsListener;
    private DefUnityAdsInitializationListener defUnityAdsInitListener;
    private Activity activity;

    public DefUnityAds(Activity appActivity) {
        activity = appActivity;
        defUnityAdsListener = new DefUnityAdsListener();
        defUnityAdsInitListener = new DefUnityAdsInitializationListener();
    }

    public void initialize(String gameId, boolean testMode) {
        UnityAds.initialize(activity, gameId, testMode, false, defUnityAdsInitListener);
        UnityAds.setListener(defUnityAdsListener);
    }

    public void show(String placementId) {
        if (placementId == null || placementId.isEmpty()) {
            UnityAds.show(activity);
        } else {
            UnityAds.show(activity, placementId);
        }
    }

    public void setDebugMode(boolean debugMode) {
        UnityAds.setDebugMode(debugMode);
    }

    public boolean getDebugMode() {
        return UnityAds.getDebugMode();
    }

    public boolean isReady(String placementId) {
        if (placementId == null || placementId.isEmpty()) {
            return UnityAds.isReady();
        }
        return UnityAds.isReady(placementId);
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

    public int getPlacementState(String placementId) {
        if (placementId == null || placementId.isEmpty()) {
            return UnityAds.getPlacementState().ordinal();
        }
        return UnityAds.getPlacementState(placementId).ordinal();
    }

    private class DefUnityAdsListener implements IUnityAdsListener {
        @Override
        public void onUnityAdsReady(final String placementId) {
            DefUnityAds.onUnityAdsReady(placementId);
        }

        @Override
        public void onUnityAdsStart(String placementId) {
            DefUnityAds.onUnityAdsStart(placementId);
        }

        @Override
        public void onUnityAdsError(UnityAds.UnityAdsError error, String message) {
            DefUnityAds.onUnityAdsError(error.ordinal(), message);
        }

        @Override
        public void onUnityAdsFinish(String placementId, UnityAds.FinishState result) {
            DefUnityAds.onUnityAdsFinish(placementId, result.ordinal());
        }
    }

    private class DefUnityAdsInitializationListener implements IUnityAdsInitializationListener {
        @Override
        public void onInitializationComplete() {
            DefUnityAds.onUnityAdsInitialized();
        }

        @Override
        public void onInitializationFailed(UnityAds.UnityAdsInitializationError error, String message) {
            DefUnityAds.onUnityAdsInitializationError(error.ordinal(), message);
        }
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
            banner.setListener(new DefUnityBannerListener());
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

    private class DefUnityBannerListener implements BannerView.IListener {

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

            DefUnityAds.onUnityBannerLoaded(bannerAdView.getPlacementId());
        }

        @Override
        public void onBannerFailedToLoad(BannerView bannerAdView, BannerErrorInfo errorInfo) {
            DefUnityAds.onUnityBannerError(errorInfo.errorCode.ordinal(), errorInfo.errorMessage);
        }

        @Override
        public void onBannerClick(BannerView bannerAdView) {
            DefUnityAds.onUnityBannerClick(bannerAdView.getPlacementId());
        }

        @Override
        public void onBannerLeftApplication(BannerView bannerAdView) {
            DefUnityAds.onUnityBannerDidLeaveApp(bannerAdView.getPlacementId());
        }
    }
}
