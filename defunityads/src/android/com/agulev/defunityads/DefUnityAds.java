package com.agulev.defunityads;

import android.app.Activity;

import com.unity3d.ads.UnityAds;

public class DefUnityAds {

public static DefUnityAdsListener defUnityAdsListener;

public static native void onUnityAdsReady(String placementId);
public static native void onUnityAdsStart(String placementId);
public static native void onUnityAdsError(int error, String message);
public static native void onUnityAdsFinish(String placementId, int result);

//-----

private Activity activity;

public DefUnityAds(Activity appActivity) {
  activity = appActivity;
  defUnityAdsListener = new DefUnityAdsListener();
}

public void initialize(String gameId, boolean testMode) {
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

}
