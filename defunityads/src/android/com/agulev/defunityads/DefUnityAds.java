package com.agulev.defunityads;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.view.Gravity;
import android.os.Build;

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;
import com.unity3d.services.banners.IUnityBannerListener;
import com.unity3d.services.banners.UnityBanners;
import com.unity3d.services.banners.view.BannerPosition;

public class DefUnityAds {

    private DefUnityAdsListener defUnityAdsListener;
    private DefUnityBannerListener defUnityAdsBannerListener;
    private View bannerView;

    public static native void onUnityAdsReady(String placementId);
    public static native void onUnityAdsStart(String placementId);
    public static native void onUnityAdsError(int error, String message);
    public static native void onUnityAdsFinish(String placementId, int result);

    public static native void onUnityBannerLoaded(String placementId);
    public static native void onUnityBannerUnloaded(String placementId);
    public static native void onUnityBannerShow(String placementId);
    public static native void onUnityBannerClick(String placementId);
    public static native void onUnityBannerHide(String placementId);
    public static native void onUnityBannerError(String message);

    //-----

    private Activity activity;
    private LinearLayout layout;
    private WindowManager.LayoutParams windowParams;
    private BannerPosition m_bannerPosition = BannerPosition.BOTTOM_CENTER;

    private boolean isShown = false;

    public DefUnityAds(Activity appActivity) {
        activity = appActivity;
        defUnityAdsListener = new DefUnityAdsListener();
        defUnityAdsBannerListener = new DefUnityBannerListener();
    }

    public void initialize(String gameId, boolean testMode) {
        UnityBanners.setBannerListener(defUnityAdsBannerListener);
        UnityAds.initialize(activity, gameId, defUnityAdsListener, testMode);
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

    public void setBannerPosition(String position) {
        m_bannerPosition = BannerPosition.fromString(position);
    }

    public void loadBanner(String placementId) {
        UnityBanners.setBannerPosition(m_bannerPosition);
        UnityBanners.loadBanner(activity, placementId);
    }

    public void unloadBanner() {
        _hideBanner();
        UnityBanners.destroy();
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

    private class DefUnityBannerListener implements IUnityBannerListener {

        @Override
        public void onUnityBannerLoaded(String placementId, View view) {
            bannerView = view;

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

            DefUnityAds.onUnityBannerLoaded(placementId);
        }

        @Override 
        public void onUnityBannerUnloaded(String placementId) {
            layout = null;
            bannerView = null;
            windowParams = null;
            isShown = false;
            DefUnityAds.onUnityBannerUnloaded(placementId);
        }

        @Override
        public void onUnityBannerShow(String placementId) {
            isShown = true;
            DefUnityAds.onUnityBannerShow(placementId);
        }

        @Override
        public void onUnityBannerClick(String placementId) {
            DefUnityAds.onUnityBannerClick(placementId);
        }

        @Override
        public void onUnityBannerHide(String placementId) {
            DefUnityAds.onUnityBannerHide(placementId);
        }

        @Override
        public void onUnityBannerError(String message) {
            DefUnityAds.onUnityBannerError(message);
        }
    }

}