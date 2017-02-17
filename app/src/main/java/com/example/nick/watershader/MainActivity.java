package com.example.nick.watershader;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;
import android.opengl.GLSurfaceView;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.widget.Toast;

import java.nio.Buffer;
import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener {

    private GLSurfaceView glSurfaceView;
    private boolean rendererSet;

    private float touchX;
    private float touchY;

    protected void processBitmapAndPassToNative(Bitmap source, float flipX, float flipY) {

        Matrix imageFlipM = new Matrix();
        imageFlipM.postScale(flipX, flipY, source.getWidth()/2, source.getHeight()/2);
        Bitmap flippedBm = Bitmap.createBitmap(source, 0, 0, source.getWidth(), source.getHeight(), imageFlipM, true);
        ByteBuffer buffer = ByteBuffer.allocate(source.getByteCount());
        flippedBm.copyPixelsToBuffer(buffer);
        byte[] bytes = buffer.array();
        NativeWrapper.createImage(bytes, source.getWidth(), source.getHeight());
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

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


        //    processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.mipmap.heart), 1.0f, -1.0f);

            //process the 6 bitmap images in order to pass be used for cubemap
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_east), 1.0f, -1.0f);
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_west), 1.0f, -1.0f);
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_down), -1.0f, 1.0f);
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_up), -1.0f, 1.0f);
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_north), 1.0f, -1.0f);
            processBitmapAndPassToNative(BitmapFactory.decodeResource(getResources(), R.drawable.lostvalley_south), 1.0f, -1.0f);
 
            glSurfaceView.setOnTouchListener(this);

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

    @Override
    public boolean onTouch(View v, MotionEvent event) {

        if(event.getActionIndex() == 0) {
            if(event.getAction() == MotionEvent.ACTION_DOWN)
            {
                touchX = event.getX();
                touchY = event.getY();
            }
            else if(event.getAction() == MotionEvent.ACTION_MOVE) {
                float moveX = event.getX() - touchX;
                float moveY = event.getY() - touchY;

                NativeWrapper.touchMove(moveX * 0.01f, moveY * 0.01f);

                touchX = event.getX();
                touchY = event.getY();
            }
        }
        return true;
    }
}
