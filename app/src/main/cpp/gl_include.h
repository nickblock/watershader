#ifndef GL_INCLUDE
#define GL_INCLUDE

#ifdef DESKTOP_BUILD
#if WIN32 
#define NOMINMAX
#include <windows.h>
#include "glad/glad.h"
#define LOG(x,y) ;
#else
#define GL_GLEXT_PROTOTYPES 
#include "GL/gl.h"
#define LOG(args...) printf(args); printf("\n");
#endif
#else
#include <GLES2/gl2.h>
#include <android/log.h>
#define LOG(args...) __android_log_print(ANDROID_LOG_INFO, args);
#endif

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265359
#endif
#endif