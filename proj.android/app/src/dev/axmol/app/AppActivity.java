/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

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

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.Log;
import android.view.ViewGroup;
import android.view.WindowManager.LayoutParams;

import com.android.installreferrer.api.InstallReferrerClient;
import com.android.installreferrer.api.InstallReferrerStateListener;
import com.android.installreferrer.api.ReferrerDetails;
import com.google.android.gms.games.PlayGamesSdk;

import java.util.Locale;

import dev.axmol.lib.SharedLoader;

public class AppActivity extends BaseActivity implements InstallReferrerStateListener {
    public static AppActivity instance;
    private static final String TAG = "ReferrerTracker";
    private int isCampaign = 0; // mac dinh la organic
    int lastOrientation = Configuration.ORIENTATION_UNDEFINED;
    static {
        // DNT remove, some android simulator require explicit load shared libraries, otherwise will crash
        SharedLoader.load();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW
        instance = this;
        idAdsBanner = ConfigGame.ADMOB_ID;
        idAdsFull = ConfigGame.ADMOB_ID;
//        initMyAds();
//        initAds("", "ca-app-pub-3940256099942544/6300978111", "ca-app-pub-3940256099942544/1033173712", 1, 1);
        initFirebase();
        initAdjust();
        //PlayGamesSdk.initialize(this);
        // 1. Khởi tạo client

        // 2. Bắt đầu kết nối

    }
    // Giao diện InstallReferrerStateListener
    @Override
    public void onInstallReferrerSetupFinished(int responseCode) {

    }

    @Override
    public void onInstallReferrerServiceDisconnected() {
        // Play Store service bị ngắt kết nối. Bạn có thể thử kết nối lại
        // hoặc ghi nhận lỗi.
        Log.w(TAG, "Dịch vụ Referrer bị ngắt kết nối.");
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        // TODO Auto-generated method stub
        super.onDestroy();
    }

    public static void showAdsBanner(int show) {
        instance.showBannerBase(show);
    }

    public static void showAdsInterstitial() {
        instance.showAdsFullBase();
    }

    public static void showAdsReward() {
        instance.showRewardBase();
    }

    public static void initAds(String banner, String full, String reward, int idAdsBanner, int idAdsFull) {
        System.out.println("Id Ads Banner " + banner + " idAds " + idAdsBanner);
         ConfigGame.ADMOB_BANNER = banner;
         ConfigGame.ADMOB_INTER = full;
         ConfigGame.ADMOB_REWARD = reward;
        instance.idAdsBanner = idAdsBanner;
        instance.idAdsFull = idAdsFull;
//        instance.idAdsBanner = ConfigGame.UNITY_ID;
//        instance.idAdsFull = ConfigGame.UNITY_ID;
        instance.initMyAds();
    }

    public static void reloadAds(String banner, String full, String reward) {
        ConfigGame.ADMOB_BANNER = banner;
        ConfigGame.ADMOB_INTER = full;
        ConfigGame.ADMOB_REWARD = reward;
        instance.loadAdmobInter();
        instance.loadAdmobReward();
    }

    public static void initAdsFacebook(String app, String banner, String full, String reward) {
        System.out.println("initAdsFacebook " + app );
        ConfigGame.FACEBOOK_BANNER = banner;
        ConfigGame.FACEBOOK_INTER = full;
        ConfigGame.FACEBOOK_REWARD = reward;
        ConfigGame.FACEBOOK_APP = app;
    }

    public static void openApp(String app) {
        AppActivity.instance.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try {
                    AppActivity.instance.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + app)));
                } catch (android.content.ActivityNotFoundException anfe) {
                    AppActivity.instance.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://play.google.com/store/apps/details?id=" + app)));
                }
            }

        });
    }

    public static void openUrl(String URL) {
        System.out.println("URL *** " + URL);
        final Intent t = new Intent(Intent.ACTION_VIEW);
        t.setData(Uri.parse(URL));
        AppActivity.instance.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AppActivity.instance.startActivity(t);
            }

        });
    }

    public static void sendEvent(String name, String data) {
        System.out.println(name + " ==== " + data);
        instance.sendEventBase(name, data);
    }

    public static void loginGoogle() {
        instance.loginGoogleBase();
    }

    public static void submitScore(int type, int score) {
//        instance.submitScoreBase(score);
        System.out.println("Submit Score " + score);
        instance.waitShowLeaderBoard = true;
        instance.waitScore = score;
        instance.waitType = type;
        instance.loginGoogleBase();
    }

    public static void displayLeaderboard() {
        instance.displayLeaderboardBase();
    }

    public static void vibrate(int miliseconds) {
        try {
            Vibrator vibrator = (Vibrator) instance.getSystemService(VIBRATOR_SERVICE);
            if (vibrator != null && vibrator.hasVibrator()) {
                if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                    vibrator.vibrate(VibrationEffect.createOneShot(miliseconds, VibrationEffect.DEFAULT_AMPLITUDE));
                } else {
                    vibrator.vibrate(miliseconds); // Deprecated for Android 8.0+
                }
            }
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public static void changeToPortrait() {
        System.out.println("CHANGE TO ROTATE ");
        instance.runOnUiThread(
            new Runnable() {
                @Override
                public void run() {
                    instance.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
                }
            }
        );
    }

    public static void changeToLandscape() {
        instance.runOnUiThread(
            new Runnable() {
                @Override
                public void run() {
                    instance.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
                }
            }
        );
    }

    public static int getSourceApp() {
        return instance.isCampaign;
    }

    public static String getCountry() {
        String locale = Locale.getDefault().getLanguage() + "-" + Locale.getDefault().getCountry();
        return locale;
    }

    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        if (idAdsBanner != ConfigGame.ADMOB_ID)
            return;
        System.out.println("Orientation change ");
        if (newConfig.orientation != lastOrientation) {
            System.out.println("Orientation change 1");
            lastOrientation = newConfig.orientation;
            reloadBannerSafe();
        }
    }

    private void reloadBannerSafe() {
        try {
            if (adViewAdmob != null) {
                ViewGroup parent = (ViewGroup) adViewAdmob.getParent();
                if (parent != null) {
                    parent.removeView(adViewAdmob);
                }
                adViewAdmob.destroy();
                adViewAdmob = null;
            }
            System.out.println("reload Admob Banner ");
            loadAdmobBanner();
        }
        catch (Exception ex) {

        }
    }
}
