#include <jni.h>
#include <string>
#include <main.h>
#include <vector>

JNIEXPORT void JNICALL
Java_com_example_nick_watershader_NativeWrapper_createImage(JNIEnv *env, jobject instance,
                                                            jbyteArray data_, jint width,
                                                            jint height) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    int len = env->GetArrayLength (data_);

    App::get()->loadImage(data, len, width, height);

    env->ReleaseByteArrayElements(data_, data, 0);
}

JNIEXPORT void JNICALL
Java_com_example_nick_watershader_NativeWrapper_init(JNIEnv *env, jclass type) {

    App::get()->init();

}

extern "C"
{
jstring
Java_com_example_nick_watershader_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void Java_com_example_nick_watershader_NativeWrapper_on_1surface_1created
        (JNIEnv *, jobject) {
    on_surface_created();
}
void Java_com_example_nick_watershader_NativeWrapper_on_1surface_1changed
        (JNIEnv *env, jobject, jint width, jint height) {
    on_surface_changed(width, height);
}
void Java_com_example_nick_watershader_NativeWrapper_on_1draw_1frame
        (JNIEnv *, jobject) {
    on_draw_frame();
}

}