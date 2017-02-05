package com.example.nick.watershader; /**
 * Created by nick on 04/02/17.
 */
import android.opengl.GLSurfaceView.Renderer;
import static android.opengl.GLES20.*;
import javax.microedition.khronos.opengles.*;
import javax.microedition.khronos.egl.*;

public class RendererWrapper implements Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeWrapper.on_surface_created();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        NativeWrapper.on_surface_changed(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        NativeWrapper.on_draw_frame();
    }
}
