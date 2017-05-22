package com.agulev.defunityads;

import com.unity3d.ads.IUnityAdsListener;
import com.unity3d.ads.UnityAds;

public class DefUnityAdsListener implements IUnityAdsListener {
    
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
