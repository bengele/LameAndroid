package com.android.lame.helper;

/**
 * Created by ben on 2018/1/26.
 */

public class LameHelper {

    static {
        System.loadLibrary("lame");
    }

    public native static String getVersion();

    public native static boolean encodeToMp3File(String inputPath,String outputPath);

    public native static byte[] encode(byte[] buffer,int length);
}
