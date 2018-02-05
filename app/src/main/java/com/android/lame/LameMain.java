package com.android.lame;

import com.android.lame.helper.LameHelper;

/**
 * Created by ben on 2018/1/26.
 */

public class LameMain {

    public static String getVersion() {
        return LameHelper.getVersion();
    }

    public static boolean encodeToMp3File(String inputPath, String outputPath) {
        return LameHelper.encodeToMp3File(inputPath, outputPath);
    }

    public static byte[] encode(byte[] buffer, int length) {
        return LameHelper.encode(buffer, length);
    }
}
