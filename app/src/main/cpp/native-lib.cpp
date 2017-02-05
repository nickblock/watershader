#include <jni.h>
#include <string>
#include <main.h>

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
    on_surface_changed();
}
void Java_com_example_nick_watershader_NativeWrapper_on_1draw_1frame
        (JNIEnv *, jobject) {
    on_draw_frame();
}

}