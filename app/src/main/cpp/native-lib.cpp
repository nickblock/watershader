#include <jni.h>
#include <string>
#include <app.h>
#include <vector>

extern "C"
{

JNIEXPORT void JNICALL
Java_com_example_nick_watershader_NativeWrapper_createImage(JNIEnv *env, jobject instance,
                                                            jbyteArray data_, jint width,
                                                            jint height) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    int len = env->GetArrayLength (data_);

    App::get()->loadImage(data, len, width, height);

    env->ReleaseByteArrayElements(data_, data, 0);
}

jstring
Java_com_example_nick_watershader_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void Java_com_example_nick_watershader_NativeWrapper_on_1surface_1created
        (JNIEnv *, jobject) {

    App::get()->init();
}
void Java_com_example_nick_watershader_NativeWrapper_on_1surface_1changed
        (JNIEnv *env, jobject, jint width, jint height) {
    
  App::get()->setScreen(width, height);
}
void Java_com_example_nick_watershader_NativeWrapper_on_1draw_1frame
        (JNIEnv *, jobject) {
    
  App::get()->drawFrame();
}

}