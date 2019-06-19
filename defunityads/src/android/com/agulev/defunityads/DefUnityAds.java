package com.agulev.defunityads;

import android.app.Activity;
import android.view.ViewGroup;
import android.view.View;

import com.unity3d.ads.UnityAds;
import com.unity3d.ads.IUnityAdsListener;

import com.unity3d.services.banners.UnityBanners;
import com.unity3d.services.banners.IUnityBannerListener;
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
    private BannerPosition m_bannerPosition = BannerPosition.BOTTOM_CENTER;

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
        UnityBanners.destroy();
    }

    public void showBanner() {
        if (bannerView == null) {
            return;
        }

        activity.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                ((ViewGroup)activity.findViewById(android.R.id.content).getParent()).addView(bannerView);
            }
        });    

    }

    public void hideBanner() {
        if (bannerView == null) {
            return;
        }
            
        activity.runOnUiThread(new Runnable() {

            @Override
            public void run() {
                ((ViewGroup)activity.findViewById(android.R.id.content).getParent()).removeView(bannerView);
            }
        });

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
            DefUnityAds.onUnityBannerLoaded(placementId);
        }

        @Override
        public void onUnityBannerUnloaded(String placementId) {
            bannerView = null;
            DefUnityAds.onUnityBannerUnloaded(placementId);
        }

        @Override
        public void onUnityBannerShow(String placementId) {
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