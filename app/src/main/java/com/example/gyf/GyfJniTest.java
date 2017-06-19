package com.example.gyf;

import java.util.Random;
import java.util.UUID;

/**
 * Created by 龚勇峰 on 2017/6/18.
 */

public class GyfJniTest {
    static {
        System.loadLibrary("gyf");
    }

    public GyfJniTest() {

    }

    public String name = "gongfengyong";
    public static int NUM = 2;

    public int getAdminName(int num) {

        return new Random().nextInt(num);
    }

    public static String getUUID() {
        System.out.println("getUUID 执行了...");
        return UUID.randomUUID().toString();
    }

    public native String getNameFromC();

    public native void getStaticNameFormC();

    public native int getMethodFromC();

    public native String getStaticMethodFromC();

    public native long accessConstructor();
}