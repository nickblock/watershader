package com.example.nick.watershader;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.opengl.GLSurfaceView;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.widget.Toast;

import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        /*
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        */


        ActivityManager activityManager
                = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 =
                configurationInfo.reqGlEsVersion >= 0x20000;

        if (supportsEs2) {
            glSurfaceView = new GLSurfaceView(this);

            glSurfaceView.setEGLContextClientVersion(2);
            glSurfaceView.setRenderer(new RendererWrapper());
            rendererSet = true;
            setContentView(glSurfaceView);

            Bitmap bm_lostvalley_east = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_east);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_east.getByteCount());
                bm_lostvalley_east.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_east.getWidth(), bm_lostvalley_east.getHeight());
            }
            Bitmap bm_lostvalley_west = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_west);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_west.getByteCount());
                bm_lostvalley_west.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_west.getWidth(), bm_lostvalley_west.getHeight());
            }
            Bitmap bm_lostvalley_up = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_up);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_up.getByteCount());
                bm_lostvalley_up.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_up.getWidth(), bm_lostvalley_up.getHeight());
            }
            Bitmap bm_lostvalley_down = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_down);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_down.getByteCount());
                bm_lostvalley_down.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_down.getWidth(), bm_lostvalley_down.getHeight());
            }
            Bitmap bm_lostvalley_north = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_north);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_north.getByteCount());
                bm_lostvalley_north.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_north.getWidth(), bm_lostvalley_north.getHeight());
            }
            Bitmap bm_lostvalley_south = BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_south);
            {
                ByteBuffer buffer = ByteBuffer.allocate(bm_lostvalley_south.getByteCount());
                bm_lostvalley_south.copyPixelsToBuffer(buffer);
                byte[] bytes = new byte[buffer.remaining()];
                NativeWrapper.createImage(bytes, bm_lostvalley_south.getWidth(), bm_lostvalley_south.getHeight());
            }

        } else {
            // Should never be seen in production, since the manifest filters
            // unsupported devices.
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
                    Toast.LENGTH_LONG).show();
            return;
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    @Override
    protected void onPause() {
        super.onPause();

        if (rendererSet) {
            glSurfaceView.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        if (rendererSet) {
            glSurfaceView.onResume();
        }
    }
}
