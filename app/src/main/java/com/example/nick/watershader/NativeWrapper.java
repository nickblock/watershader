package com.example.nick.watershader;

/**
 * Created by nick on 04/02/17.
 */

public class NativeWrapper {
    static {
        System.loadLibrary("native-lib");
    }
    public static native void on_surface_created();

    public static native void on_surface_changed(int width, int height);

    public static native void on_draw_frame();

    public static native void createImage(byte[] data, int width, int height);

}
