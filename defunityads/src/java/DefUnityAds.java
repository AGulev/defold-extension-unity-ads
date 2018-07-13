package com.agulev.defunityads;

import android.app.Activity;

import com.unity3d.ads.UnityAds;

public class DefUnityAds {

public static Activity activity;
public static DefUnityAdsListener defUnityAdsListener;

public static native void onUnityAdsReady(String placementId);
public static native void onUnityAdsStart(String placementId);
public static native void onUnityAdsError(int error, String message);
public static native void onUnityAdsFinish(String placementId, int result);

public static void sdk_pre_init(Activity appActivity) {
  activity = appActivity;
  defUnityAdsListener = new DefUnityAdsListener();
}

public static void DefUnityAds_Initialize(String gameId, boolean testMode) {
  UnityAds.initialize(activity, gameId, defUnityAdsListener, testMode);
}

public static void DefUnityAds_Show(String placementId) {
  if (placementId == null || placementId.isEmpty()) {
    UnityAds.show(activity);
  } else {
    UnityAds.show(activity, placementId);
  }
}

public static void DefUnityAds_setDebugMode(boolean debugMode) {
  UnityAds.setDebugMode(debugMode);
}

public static boolean DefUnityAds_getDebugMode() {
  return UnityAds.getDebugMode();
}

public static boolean DefUnityAds_isReady(String placementId) {
  if (placementId == null || placementId.isEmpty()) {
    return UnityAds.isReady();
  }
  return UnityAds.isReady(placementId);
}

public static boolean DefUnityAds_isInitialized() {
  return UnityAds.isInitialized();
}

public static boolean DefUnityAds_isSupported() {
  return UnityAds.isSupported();
}

public static String DefUnityAds_getVersion() {
  return UnityAds.getVersion();
}

public static int DefUnityAds_getPlacementState(String placementId) {
  if (placementId == null || placementId.isEmpty()) {
    return UnityAds.getPlacementState().ordinal();
  }
  return UnityAds.getPlacementState(placementId).ordinal();
}

}
