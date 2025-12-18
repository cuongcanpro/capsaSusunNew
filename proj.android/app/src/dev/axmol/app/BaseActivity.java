/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
package dev.axmol.app;

import com.google.android.gms.ads.RequestConfiguration;

import android.app.AlertDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.Toast;

import androidx.annotation.NonNull;

import com.facebook.ads.Ad;
import com.facebook.ads.AudienceNetworkAds;
import com.facebook.ads.InterstitialAdListener;
import com.facebook.ads.RewardedVideoAd;
import com.facebook.ads.RewardedVideoAdListener;
import com.google.ads.mediation.admob.AdMobAdapter;
import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.OnUserEarnedRewardListener;
import com.google.android.gms.ads.RequestConfiguration;
import com.google.android.gms.ads.identifier.AdvertisingIdClient;
import com.google.android.gms.ads.initialization.AdapterStatus;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;
import com.google.android.gms.ads.rewarded.RewardItem;
import com.google.android.gms.ads.rewarded.RewardedAd;
import com.google.android.gms.ads.rewarded.RewardedAdLoadCallback;
import com.google.android.gms.common.GooglePlayServicesNotAvailableException;
import com.google.android.gms.common.GooglePlayServicesRepairableException;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.games.GamesSignInClient;
import com.google.android.gms.games.PlayGames;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.analytics.FirebaseAnalytics;
import com.unity3d.ads.IUnityAdsInitializationListener;
import com.unity3d.ads.IUnityAdsLoadListener;
import com.unity3d.ads.IUnityAdsShowListener;
import com.unity3d.ads.UnityAds;
import com.unity3d.ads.UnityAdsShowOptions;
import com.unity3d.services.ads.operation.show.ShowOperation;
import com.unity3d.services.banners.BannerErrorInfo;
import com.unity3d.services.banners.BannerView;
import com.unity3d.services.banners.UnityBannerSize;



import java.io.IOException;
import java.util.Arrays;
import java.util.Map;

import dev.axmol.lib.AxmolActivity;

//import com.facebook.ads.AudienceNetworkAds;
//import com.crashlytics.android.Crashlytics;
//import com.google.firebase.crashlytics.FirebaseCrashlytics;

public class BaseActivity extends dev.axmol.lib.AxmolActivity {

    public boolean waitShowLeaderBoard = false;
    public int waitScore = 0;
    public int waitType = 0;
    public boolean rAds = false;
    // Client used to sign in with Google APIs
    //public GoogleSignInClient mGoogleSignInClient;
    public FirebaseAnalytics mFirebaseAnalytics;

    // 1 la admob, 2 la startapp
    public int idAdsFull = 1;
    public int idAdsBanner = 1;

    /**
     * Google Ads
     */
    public RewardedAd rewardedAdmob;
    public AdView adViewAdmob;
    // public com.facebook.ads.AdView adViewFacebook;
    public InterstitialAd interstitialAdmob;
    //  public com.facebook.ads.InterstitialAd interstitialAdFace;
    public boolean adsGoogleBannerFail = false;
    public boolean adsGoogleInterFail = false;
    long lastTimeClickBanner = 0;
    long lastTimeShowAdsFull = 0;

    /**
     * Facebook Ads
     */
    public com.facebook.ads.AdView adViewFacebook;
    public com.facebook.ads.InterstitialAd interFacebook;
    public RewardedVideoAd rewardFacebook;
    InterstitialAdListener interstitialAdListenerFacebook;
    RewardedVideoAdListener rewardAdListenerFacebook;

    /**
     * Unity Ads
     */
    public BannerView adViewUnity;
    public boolean isInitUnity = false;
    public boolean isLoadInter = false;
    public boolean isLoadReward = false;
    public int countLoadInter = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
        if (!isTaskRoot()) {
            return;
        }
    }

    public void initFirebase() {
        try {
            mFirebaseAnalytics = FirebaseAnalytics.getInstance(this);
        }
        catch (Exception e) {
            e.printStackTrace();;
        }
    }

    public void initAdjust() {
//        String appToken = ConfigGame.ADJUST_TOKEN;
//        String environment = AdjustConfig.ENVIRONMENT_PRODUCTION;
//        AdjustConfig config = new AdjustConfig(this, appToken, environment);
//        config.setLogLevel(LogLevel.WARN);
//        Adjust.initSdk(config);
    }

    public void sendEventBase(String name, String data) {
        try {
            Bundle params = new Bundle();
            params.putString("data", data);
            if (mFirebaseAnalytics != null)
                mFirebaseAnalytics.logEvent(name, params);
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public void initMyAds() {

        String locale = this.getResources().getConfiguration().locale.getCountry();
        if (locale.compareTo("RU") == 0 || locale.compareTo("RUS") == 0 || locale.compareTo("ru") == 0 || locale.compareTo("rus") == 0)
            rAds = true;

        rAds = false;
        /**
         * INIT ADMOB
         */
        System.out.println("INIT MY ADS " + idAdsBanner);
        if (idAdsFull == ConfigGame.ADMOB_ID || idAdsBanner == ConfigGame.ADMOB_ID)
            initAdmob();
        if (idAdsFull == ConfigGame.FACEBOOK_ID || idAdsBanner == ConfigGame.FACEBOOK_ID)
            initFacebook();
        if (idAdsFull == ConfigGame.UNITY_ID || idAdsBanner == ConfigGame.UNITY_ID)
            initUnity();
    }

    public void showAdsFullBase() {
        // TODO Auto-generated method stub
        System.out.println("SHOWAdsFull ============= ");
        long save = this.lastTimeShowAdsFull;
        long current = System.currentTimeMillis();
        long dis = current - save;
        if (dis < 20000) {
            // cheat
            // show nhieu ads full qua, khong cho hien lien tuc
            return;
        }
        this.lastTimeShowAdsFull = current;
        System.out.println("SHOW ADS FULL ");
        this.runOnUiThread(new Runnable() {
            public void run() {
                if (idAdsFull == ConfigGame.ADMOB_ID) {
                    showAdmobInter();
                }
                else if (idAdsFull == ConfigGame.FACEBOOK_ID) {
                    showFacebookInter();
                }
                else if (idAdsFull == ConfigGame.UNITY_ID) {
                    showUnityInter();
                }
            }
        });
    }

    public void showRewardBase() {
        this.runOnUiThread(new Runnable() {
            public void run() {
                if (idAdsFull == ConfigGame.ADMOB_ID) {
                    showAdmobReward();
                }
                else if (idAdsFull == ConfigGame.FACEBOOK_ID) {
                    showFacebookReward();
                }
                else if (idAdsFull == ConfigGame.UNITY_ID) {
                    showUnityReward();
                }
            }
        });
    }

    public void showBannerBase(int show) {
        this.runOnUiThread(new Runnable() {
            public void run() {
                if (idAdsBanner == ConfigGame.ADMOB_ID) {
                    showAdmobBanner(show);
                }
                else if (idAdsBanner == ConfigGame.FACEBOOK_ID) {
                    //showFacebookReward();
                }
                else if (idAdsBanner == ConfigGame.UNITY_ID) {
                    //showUnityReward();
                }
            }
        });
    }

    /** region Admob */

    public void initAdmob() {
        MobileAds.initialize(this, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(InitializationStatus initializationStatus) {
                RequestConfiguration requestConfiguration = new RequestConfiguration.Builder()
                    .setTestDeviceIds(Arrays.asList("F2673C9D2A859846C3412EFD820FF1A0,3FBF9C3BBAAFA6D8B26FF15449503069")) // Replace with your device ID
                    .build();
                MobileAds.setRequestConfiguration(requestConfiguration);
                Map<String, AdapterStatus> statusMap = initializationStatus.getAdapterStatusMap();
                for (String adapterClass : statusMap.keySet()) {
                    AdapterStatus status = statusMap.get(adapterClass);
                    Log.d("MyApp", String.format(
                        "Adapter name: %s, Description: %s, Latency: %d",
                        adapterClass, status.getDescription(), status.getLatency()));
                }

                // Start loading ads here...
                if (idAdsBanner == ConfigGame.ADMOB_ID) {
                    loadAdmobBanner();;
                }
                if (idAdsFull == ConfigGame.ADMOB_ID) {
                    loadAdmobInter();
                    loadAdmobReward();
                }
            }
        });
    }

    private AdSize getAdSize() {
        Display display = getWindowManager().getDefaultDisplay();
        DisplayMetrics outMetrics = new DisplayMetrics();
        display.getMetrics(outMetrics);

        float widthPixels = outMetrics.widthPixels;
        float density = outMetrics.density;

        int adWidth = (int) (widthPixels / density);
        return AdSize.getCurrentOrientationAnchoredAdaptiveBannerAdSize(this, adWidth);
    }

    public void loadAdmobBanner() {
        RequestConfiguration requestConfiguration = MobileAds.getRequestConfiguration().toBuilder()
            .setMaxAdContentRating("MAX_AD_CONTENT_RATING_G")
            .build();
        Bundle extras = new Bundle();
        //extras.putString("max_ad_content_rating", "G");

        AdRequest adRequest = new AdRequest.Builder()
            .addNetworkExtrasBundle(AdMobAdapter.class, extras)
            //   .addTestDevice(AdRequest.DEVICE_ID_EMULATOR) // Emulator
            //  .addTestDevice("5B186941B899A8CE8BF4CA06CAD9715B") // My Galaxy Nexus test phone
            .build();

        adViewAdmob = new AdView(BaseActivity.this);
//        adViewAdmob.setAdSize(AdSize.BANNER);
        adViewAdmob.setAdSize(getAdSize());
//        adViewAdmob.setAdSize(AdSize.getLandscapeInlineAdaptiveBannerAdSize(this, 600));
        adViewAdmob.setAdUnitId(ConfigGame.ADMOB_BANNER);

        adViewAdmob.loadAd(adRequest);
        adViewAdmob.setBackgroundColor(Color.BLACK);
        adViewAdmob.setBackgroundColor(0);

        adViewAdmob.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
                // Code to be executed when an ad finishes loading.
                System.out.println("onAdLoaded");
                rAds = false;
            }

            @Override
            public void onAdFailedToLoad(LoadAdError adError) {
                // Code to be executed when an ad request fails.
                System.out.println("onAdFailedToLoad " + adError.getMessage());
                if (rAds) {
                    idAdsBanner = ConfigGame.UNITY_ID;
                    idAdsFull = ConfigGame.UNITY_ID;
                    initUnity();
                    adViewAdmob.setVisibility(View.INVISIBLE);
                }
            }

            @Override
            public void onAdOpened() {
                // Code to be executed when an ad opens an overlay that
                // covers the screen.
                System.out.println("onAdOpened *****");
                long save = lastTimeClickBanner;
                lastTimeClickBanner = System.currentTimeMillis();
                long dis = lastTimeClickBanner - save;
                if (dis < 20000) {
                    // cheat
                    adViewAdmob.setVisibility(View.INVISIBLE);
                }
            }

            @Override
            public void onAdClicked() {
                // Code to be executed when the user clicks on an ad.
                super.onAdClicked();
                System.out.println("onAdClicked");
            }

            @Override
            public void onAdClosed() {
                // Code to be executed when the user is about to return
                // to the app after tapping on an ad.
                System.out.println("onAdClosed");
            }
        });
        RelativeLayout relativeLayout = new RelativeLayout(BaseActivity.this);
        mFrameLayout.addView(relativeLayout);

        RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
            AdView.LayoutParams.MATCH_PARENT,
            AdView.LayoutParams.WRAP_CONTENT);
        // align bottom
        adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        // align center
        adViewParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
        relativeLayout.addView(adViewAdmob, adViewParams);
    }

    public void loadAdmobInter() {
        System.out.println("LOAD ADS FULL *** ");
        if (this.interstitialAdmob == null) {
            this.runOnUiThread(new Runnable() {
                public void run() {
                    System.out.println("LOAD ADS MOI");
                    Bundle extras = new Bundle();
//                    extras.putString("max_ad_content_rating", "G");
                    AdRequest adRequest = new AdRequest.Builder().build();
                    InterstitialAd.load(BaseActivity.this, ConfigGame.ADMOB_INTER, adRequest,
                        new InterstitialAdLoadCallback() {
                            @Override
                            public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                                // The mInterstitialAd reference will be null until
                                // an ad is loaded.
                                interstitialAdmob = interstitialAd;
                                interstitialAdmob.setFullScreenContentCallback(new FullScreenContentCallback() {
                                    @Override
                                    public void onAdDismissedFullScreenContent() {
                                        // Called when fullscreen content is dismissed.
                                        Log.d("TAG", "The ad was dismissed.");
                                        BaseActivity.this.interstitialAdmob = null;
                                        BaseActivity.this.loadAdmobInter();
                                    }

                                    @Override
                                    public void onAdFailedToShowFullScreenContent(AdError adError) {
                                        // Called when fullscreen content failed to show.
                                        Log.d("TAG", "The ad failed to show.");
                                        BaseActivity.this.interstitialAdmob = null;
                                        BaseActivity.this.loadAdmobInter();
                                    }

                                    @Override
                                    public void onAdShowedFullScreenContent() {
                                        // Called when fullscreen content is shown.
                                        // Make sure to set your reference to null so you don't
                                        // show it a second time.
                                        //  instance.interstitialAdmob = null;
                                        //  instance.loadAdsFull();
                                        Log.d("TAG", "The ad was shown.");
                                    }
                                });
                            }

                            @Override
                            public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                                // Handle the error
                                System.out.println("onAdFailedToLoad Inter Google Fail " + loadAdError.getMessage());
                                BaseActivity.this.interstitialAdmob = null;
                            }
                        });
                }
            });
        }
        else {
            System.out.println("DUNG ADS CU");
        }
    }

    public void loadAdmobReward() {
        System.out.println("START LOAD REWARD");
        this.runOnUiThread(new Runnable() {
            public void run() {
                AdRequest adRequest = new AdRequest.Builder().build();
                RewardedAd.load(BaseActivity.this, ConfigGame.ADMOB_REWARD,
                    adRequest, new RewardedAdLoadCallback() {
                        @Override
                        public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                            // Handle the error.
                            System.out.println("LOAD REWARD FAIL " + loadAdError.getMessage());
                            rewardedAdmob = null;
                        }

                        @Override
                        public void onAdLoaded(@NonNull RewardedAd rewardedAd) {
                            System.out.println("onAdLoaded adreward ");
                            BaseActivity.this.rewardedAdmob = rewardedAd;
                            rewardedAd.setFullScreenContentCallback(new FullScreenContentCallback() {
                                @Override
                                public void onAdShowedFullScreenContent() {
                                    // Called when ad is shown.
                                    Log.i("REWARD ", "onAdShowedFullScreenContent");
                                    BaseActivity.this.rewardedAdmob = null;
                                    loadAdmobReward();
                                }

                                @Override
                                public void onAdFailedToShowFullScreenContent(AdError adError) {
                                    // Called when ad fails to show.
                                    BaseActivity.this.rewardedAdmob = null;
                                    loadAdmobReward();
                                    Log.i("REWARD ", "onAdShowedFullScreenContent");
                                }

                                @Override
                                public void onAdDismissedFullScreenContent() {
                                    // Called when ad is dismissed.
                                    // Set the ad reference to null so you don't show the ad a second time.
                                    BaseActivity.this.rewardedAdmob = null;
                                    loadAdmobReward();
                                    Log.i("REWARD ", "onAdShowedFullScreenContent");
                                }
                            });
                        }
                    });
            }
        });
    }

    public void showAdmobInter() {
        if (interstitialAdmob != null ) {
            System.out.println("SHOW ADS FULL GOOGLE");
            interstitialAdmob.show(BaseActivity.this);
        }
        else {
            System.out.println("SHOW ADS FULL NOT LOAD ");
            loadAdmobInter();
        }
    }

    public void showAdmobReward() {
        if (rewardedAdmob != null) {
            rewardedAdmob.show(BaseActivity.this, new OnUserEarnedRewardListener() {
                @Override
                public void onUserEarnedReward(@NonNull RewardItem rewardItem) {
                    // Handle the reward.
                    int rewardAmount = rewardItem.getAmount();
                    String rewardType = rewardItem.getType();
                    System.out.println("ON REWARD SUCCESS " + rewardAmount);
                    nativeOnReward(rewardAmount);
                }
            });
        }
        else {
            Log.d("TAG", "The rewarded ad wasn't loaded yet.");
            CharSequence text = "Can hoan thanh viec xem Quang cao de co Phan Thuong!";
            int duration = Toast.LENGTH_SHORT;

//            Toast toast = Toast.makeText(BaseActivity.this, text, duration);
//            toast.show();
            loadAdmobReward();
            nativeOnReward(0);
        }
    }

    public void showAdmobBanner(int show) {
        if (adViewAdmob != null) {
            if (show == 1) {
                adViewAdmob.setVisibility(View.VISIBLE);
            }
            else {
                adViewAdmob.setVisibility(View.INVISIBLE);
            }
        }
    }

    /** endregion Admob */

    /** region Facebook */
    public void initFacebook() {
        AudienceNetworkAds
            .buildInitSettings(this)
            .withInitListener(new AudienceNetworkAds.InitListener() {
                @Override
                public void onInitialized(AudienceNetworkAds.InitResult initResult) {
                    if (initResult.isSuccess()) {
                        if (idAdsBanner == ConfigGame.FACEBOOK_ID)
                            loadFacebookBanner();
                        if (idAdsFull == ConfigGame.FACEBOOK_ID) {
                            interFacebook = new com.facebook.ads.InterstitialAd(BaseActivity.this, ConfigGame.FACEBOOK_INTER);
                            loadFacebookInter();
                            rewardFacebook = new RewardedVideoAd(BaseActivity.this, ConfigGame.FACEBOOK_REWARD);
                            loadFacebookReward();
                        }
                    }
                }
            })
            .initialize();
        AudienceNetworkAds.initialize(this);
    }

    public void loadFacebookBanner() {
        this.adViewFacebook = new com.facebook.ads.AdView(this, ConfigGame.FACEBOOK_BANNER, com.facebook.ads.AdSize.BANNER_HEIGHT_50);
        this.adViewFacebook.loadAd(this.adViewFacebook.buildLoadAdConfig()
            .withAdListener(new com.facebook.ads.AdListener() {

                @Override
                public void onError(Ad ad, com.facebook.ads.AdError adError) {
                    Log.d("Facebook Banner ", "onError " + adError.getErrorCode() + " " + adError.getErrorMessage());
                }

                @Override
                public void onAdLoaded(Ad ad) {
                    Log.d("Facebook Banner ", "onAdLoaded");
                }

                @Override
                public void onAdClicked(Ad ad) {
                    Log.d("Facebook Banner ", "onAdClicked");
                }

                @Override
                public void onLoggingImpression(Ad ad) {
                    Log.d("Facebook Banner ", "onLoggingImpression");
                }
            } )
            .build());
        // instance.adViewUnity.setListener(instance);
        RelativeLayout relativeLayout = new RelativeLayout(this);
        this.mFrameLayout.addView(relativeLayout);

        RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
            AdView.LayoutParams.WRAP_CONTENT,
            AdView.LayoutParams.WRAP_CONTENT);
        // align bottom
        adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
        // align center
        adViewParams.addRule(RelativeLayout.CENTER_IN_PARENT,
            RelativeLayout.TRUE);
        relativeLayout.addView(this.adViewFacebook, adViewParams);
    }

    public void loadFacebookInter() {
        interFacebook.loadAd(
            interFacebook.buildLoadAdConfig()
                .withAdListener(new InterstitialAdListener() {
                    @Override
                    public void onInterstitialDisplayed(Ad ad) {
                        // Interstitial ad displayed callback
                        Log.e("Facebook Inter", "Interstitial ad displayed.");
                    }

                    @Override
                    public void onInterstitialDismissed(Ad ad) {
                        // Interstitial dismissed callback
                        Log.e("Facebook Inter", "Interstitial ad dismissed.");
                        BaseActivity.this.loadFacebookInter();
                    }

                    @Override
                    public void onError(Ad ad, com.facebook.ads.AdError adError) {
                        // Ad error callback
                        Log.e("Facebook Inter", "Interstitial ad failed to load: " + adError.getErrorMessage());
                        BaseActivity.this.loadFacebookInter();
                    }

                    @Override
                    public void onAdLoaded(Ad ad) {
                        // Interstitial ad is loaded and ready to be displayed
                        Log.d("Facebook Inter", "Interstitial ad is loaded and ready to be displayed!");
                        // Show the ad
                        //interstitialAd.show();
                    }

                    @Override
                    public void onAdClicked(Ad ad) {
                        // Ad clicked callback
                        Log.d("Facebook Inter", "Interstitial ad clicked!");
                    }

                    @Override
                    public void onLoggingImpression(Ad ad) {
                        // Ad impression logged callback
                        Log.d("Facebook Inter", "Interstitial ad impression logged!");
                    }
                })
                .build()
        );
    }

    public void loadFacebookReward() {
        rewardFacebook.loadAd(
            rewardFacebook.buildLoadAdConfig()
                .withAdListener(new RewardedVideoAdListener() {
                    @Override
                    public void onError(Ad ad, com.facebook.ads.AdError error) {
                        // Rewarded video ad failed to load
                        Log.e("Facebook Reward", "Rewarded video ad failed to load: " + error.getErrorMessage());
                    }

                    @Override
                    public void onAdLoaded(Ad ad) {
                        // Rewarded video ad is loaded and ready to be displayed
                        Log.d("Facebook Reward", "Rewarded video ad is loaded and ready to be displayed!");
                    }

                    @Override
                    public void onAdClicked(Ad ad) {
                        // Rewarded video ad clicked
                        Log.d("Facebook Reward", "Rewarded video ad clicked!");
                    }

                    @Override
                    public void onLoggingImpression(Ad ad) {
                        // Rewarded Video ad impression - the event will fire when the
                        // video starts playing
                        Log.d("Facebook Reward", "Rewarded video ad impression logged!");
                    }

                    @Override
                    public void onRewardedVideoCompleted() {
                        // Rewarded Video View Complete - the video has been played to the end.
                        // You can use this event to initialize your reward
                        Log.d("Facebook Reward", "Rewarded video completed!");

                        // Call method to give reward
                        // giveReward();
                        nativeOnReward(1);
                    }

                    @Override
                    public void onRewardedVideoClosed() {
                        // The Rewarded Video ad was closed - this can occur during the video
                        // by closing the app, or closing the end card.
                        Log.d("TAG", "Rewarded video ad closed!");
                        loadFacebookReward();
                    }
                })
                .build());
    }

    public void showFacebookInter() {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(interFacebook == null || !interFacebook.isAdLoaded()) {
                    System.out.println("GO INTER FACEBOOK HERE 1");
                    loadFacebookInter();
                    return;
                }
                // Check if ad is already expired or invalidated, and do not show ad if that is the case. You will not get paid to show an invalidated ad.
                if(interFacebook.isAdInvalidated()) {
                    System.out.println("GO INTER FACEBOOK HERE 2");
                    loadFacebookInter();
                    return;
                }
                // Show the ad
                System.out.println("GO INTER FACEBOOK HERE 3");
                interFacebook.show();
            }
        });
    }

    public void showFacebookReward() {
        // Check if rewardedVideoAd has been loaded successfully
        if (rewardFacebook == null || !rewardFacebook.isAdLoaded()) {
            loadFacebookReward();
            nativeOnReward(1);
            return;
        }
        // Check if ad is already expired or invalidated, and do not show ad if that is the case. You will not get paid to show an invalidated ad.
        if (rewardFacebook.isAdInvalidated()) {
            loadFacebookReward();
            nativeOnReward(1);
            return;
        }
        rewardFacebook.show();
    }
    /** endregion Facebook */

    /** region Unity */
    public void initUnity() {
        UnityAds.initialize(this, ConfigGame.UNITY_APP, false, new IUnityAdsInitializationListener() {
            @Override
            public void onInitializationComplete() {
                Log.i("UnityAds", "init unity finish");
                if (idAdsBanner == ConfigGame.UNITY_ID) {
                    loadUnityBanner();
                }
                if (idAdsFull == ConfigGame.UNITY_ID) {
                    loadUnityInter();
                }
            }

            @Override
            public void onInitializationFailed(UnityAds.UnityAdsInitializationError error, String message) {
                Log.i("UnityAds", "init unity fail");
            }
        });
    }

    public void loadUnityBanner() {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                adViewUnity = new BannerView(BaseActivity.this, ConfigGame.UNITY_BANNER, new UnityBannerSize(320, 50));
                adViewUnity.load();
                adViewUnity.setListener(new BannerView.IListener() {
                    @Override
                    public void onBannerLoaded(BannerView bannerAdView) {
                        Log.i("Unity Banner ", "onBannerLoaded");
                    }

                    @Override
                    public void onBannerShown(BannerView bannerAdView) {
                        Log.i("Unity Banner ", "onBannerShown");
                    }

                    @Override
                    public void onBannerClick(BannerView bannerAdView) {
                        Log.i("Unity Banner ", "onBannerClick");
                    }

                    @Override
                    public void onBannerFailedToLoad(BannerView bannerAdView, BannerErrorInfo errorInfo) {
                        Log.i("Unity Banner ", "onBannerFailedToLoad");
                    }

                    @Override
                    public void onBannerLeftApplication(BannerView bannerView) {
                        Log.i("Unity Banner ", "onBannerLeftApplication");
                    }
                });
                RelativeLayout relativeLayout = new RelativeLayout(BaseActivity.this);
                mFrameLayout.addView(relativeLayout);

                RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
                    AdView.LayoutParams.WRAP_CONTENT,
                    AdView.LayoutParams.WRAP_CONTENT);
                // align bottom
                adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
                // align center
                adViewParams.addRule(RelativeLayout.CENTER_IN_PARENT,
                    RelativeLayout.TRUE);
                relativeLayout.addView(adViewUnity, adViewParams);
            }
        });
    }

    public void loadUnityInter() {
        UnityAds.load(ConfigGame.UNITY_INTER, new IUnityAdsLoadListener() {
            @Override
            public void onUnityAdsAdLoaded(String placementId) {
                isLoadInter = true;
                Log.i("Unity Inter ", "onUnityAdsAdLoaded");
            }

            @Override
            public void onUnityAdsFailedToLoad(String placementId, UnityAds.UnityAdsLoadError error, String message) {
                isLoadInter = false;
                if (countLoadInter >= 3) {
                    countLoadInter = 0;
                    return;
                }
                countLoadInter++;
                loadUnityInter();
                Log.i("Unity Inter ", "onUnityAdsFailedToLoad");
            }
        });
    }

    // Implement a function to display an ad if the Ad Unit is ready:
    public void showUnityInter () {
        countLoadInter = 0;
        if (isLoadInter) {
            isLoadInter = false;
            UnityAds.show(this, ConfigGame.UNITY_INTER, new UnityAdsShowOptions(), new IUnityAdsShowListener() {
                @Override
                public void onUnityAdsShowFailure(String placementId, UnityAds.UnityAdsShowError error, String message) {
                    loadUnityInter();
                    Log.i("Unity Inter ", "onUnityAdsShowFailure");
                }

                @Override
                public void onUnityAdsShowStart(String placementId) {
                    Log.i("Unity Inter ", "onUnityAdsShowStart");
                }

                @Override
                public void onUnityAdsShowClick(String placementId) {
                    Log.i("Unity Inter ", "onUnityAdsShowClick");
                }

                @Override
                public void onUnityAdsShowComplete(String placementId, UnityAds.UnityAdsShowCompletionState state) {
                    loadUnityInter();
                    Log.i("Unity Inter ", "onUnityAdsShowComplete");
                }
            });
        }
        else {
            loadUnityInter();
        }
    }

    // Implement a function to display an ad if the Ad Unit is ready:
    public void showUnityReward () {
        UnityAds.load(ConfigGame.UNITY_REWARD, new IUnityAdsLoadListener() {
            @Override
            public void onUnityAdsAdLoaded(String placementId) {
                Log.i("Unity Reward ", "onUnityAdsAdLoaded");
                UnityAds.show(BaseActivity.this, ConfigGame.UNITY_REWARD, new UnityAdsShowOptions(), new IUnityAdsShowListener() {
                    @Override
                    public void onUnityAdsShowFailure(String placementId, UnityAds.UnityAdsShowError error, String message) {
                        nativeOnReward(0);
                        Log.i("Unity Reward ", "onUnityAdsShowFailure");
                    }

                    @Override
                    public void onUnityAdsShowStart(String placementId) {
                        Log.i("Unity Reward ", "onUnityAdsShowStart");
                    }

                    @Override
                    public void onUnityAdsShowClick(String placementId) {
                        Log.i("Unity Reward ", "onUnityAdsShowClick");
                    }

                    @Override
                    public void onUnityAdsShowComplete(String placementId, UnityAds.UnityAdsShowCompletionState state) {
                        if (state.equals(UnityAds.UnityAdsShowCompletionState.COMPLETED)) {
                            // Reward the user for watching the ad to completion
                            nativeOnReward(1);
                        } else {
                            // Do not reward the user for skipping the ad
                            CharSequence text = "Can hoan thanh viec xem Quang cao de co Phan Thuong!";
                            int duration = Toast.LENGTH_SHORT;
                            Toast toast = Toast.makeText(BaseActivity.this, text, duration);
                            toast.show();
                        }
                        Log.i("Unity Reward ", "onUnityAdsShowComplete");
                    }
                });
            }

            @Override
            public void onUnityAdsFailedToLoad(String placementId, UnityAds.UnityAdsLoadError error, String message) {
                nativeOnReward(1);
                Log.i("Unity Reward ", "onUnityAdsFailedToLoad");
            }
        });
    }
    /** endregion Unity */

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        System.out.println("request code " + requestCode);
    }

    @Override
    protected void onResume() {
        super.onResume();
        try {
            // signInSilently();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        try {
            if (adViewAdmob != null) {
                adViewAdmob.resume();
            }
        } catch (Exception e) {
            // TODO: handle exception
        }
    }

    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
        super.onPause();

        try {
            if (adViewAdmob != null) {
                adViewAdmob.pause();
            }
        } catch (Exception e) {
            // TODO: handle exception
        }
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        try {
            if (adViewAdmob != null) {
                adViewAdmob.removeAllViews();
                adViewAdmob.destroy();
            }


        } catch (Exception e) {
            // TODO: handle exception
        }
        super.onDestroy();
    }

    public void loginGoogleBase() {
        GamesSignInClient gamesSignInClient = PlayGames.getGamesSignInClient(this);

        gamesSignInClient.isAuthenticated().addOnCompleteListener(isAuthenticatedTask -> {
            boolean isAuthenticated =
                (isAuthenticatedTask.isSuccessful() &&
                    isAuthenticatedTask.getResult().isAuthenticated());
            System.out.println("is Authenticated " + isAuthenticated);
            if (isAuthenticated) {
                // Continue with Play Games Services
                if (this.waitShowLeaderBoard) {
                    this.submitScoreBase();
                    this.displayLeaderboardBase();
                }
            } else {
                // Disable your integration with Play Games Services or show a
                // login button to ask  players to sign-in. Clicking it should
                // call GamesSignInClient.signIn().
                gamesSignInClient.signIn();
                System.out.println("SignIn ====== ");
            }
        });
    }

    public void submitScoreBase() {
        if (this.waitType == 0) {
            PlayGames.getLeaderboardsClient(this)
                .submitScore(ConfigGame.LEADERBOARD_ID, this.waitScore);
        }
        else  if (this.waitType == 1) {
            PlayGames.getLeaderboardsClient(this)
                .submitScore(ConfigGame.LEADERBOARD_ID_ENDLESS, this.waitScore);
        }
        else  if (this.waitType == 2) {
            PlayGames.getLeaderboardsClient(this)
                .submitScore(ConfigGame.LEADERBOARD_ID_TIME, this.waitScore);
        }
        else  if (this.waitType == 3) {
            PlayGames.getLeaderboardsClient(this)
                .submitScore(ConfigGame.LEADERBOARD_ID_DROP, this.waitScore);
        }
        else  if (this.waitType == 4) {
            PlayGames.getLeaderboardsClient(this)
                .submitScore(ConfigGame.LEADERBOARD_ID_TWENTY, this.waitScore);
        }
    }

    public void displayLeaderboardBase() {
        if (this.waitType == 0) {
            PlayGames.getLeaderboardsClient(this)
                .getLeaderboardIntent(ConfigGame.LEADERBOARD_ID)
                .addOnSuccessListener(new OnSuccessListener<Intent>() {
                    @Override
                    public void onSuccess(Intent intent) {
                        startActivityForResult(intent, 9004);
                    }
                });
        }
        else  if (this.waitType == 1) {
            PlayGames.getLeaderboardsClient(this)
                .getLeaderboardIntent(ConfigGame.LEADERBOARD_ID_ENDLESS)
                .addOnSuccessListener(new OnSuccessListener<Intent>() {
                    @Override
                    public void onSuccess(Intent intent) {
                        startActivityForResult(intent, 9004);
                    }
                });
        }
        else  if (this.waitType == 2) {
            PlayGames.getLeaderboardsClient(this)
                .getLeaderboardIntent(ConfigGame.LEADERBOARD_ID_TIME)
                .addOnSuccessListener(new OnSuccessListener<Intent>() {
                    @Override
                    public void onSuccess(Intent intent) {
                        startActivityForResult(intent, 9004);
                    }
                });
        }
        else  if (this.waitType == 3) {
            PlayGames.getLeaderboardsClient(this)
                .getLeaderboardIntent(ConfigGame.LEADERBOARD_ID_DROP)
                .addOnSuccessListener(new OnSuccessListener<Intent>() {
                    @Override
                    public void onSuccess(Intent intent) {
                        startActivityForResult(intent, 9004);
                    }
                });
        }
        else  if (this.waitType == 4) {
            PlayGames.getLeaderboardsClient(this)
                .getLeaderboardIntent(ConfigGame.LEADERBOARD_ID_TWENTY)
                .addOnSuccessListener(new OnSuccessListener<Intent>() {
                    @Override
                    public void onSuccess(Intent intent) {
                        startActivityForResult(intent, 9004);
                    }
                });
        }
    }

    public static native void nativeOnReward(int num);
}
