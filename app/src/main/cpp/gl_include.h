#ifndef GL_INCLUDE
#define GL_INCLUDE

#ifdef DESKTOP_BUILD
#define GL_GLEXT_PROTOTYPES 
#include "GL/gl.h"
#define LOG(args...) printf(args); printf("\n");
#else
#include <GLES2/gl2.h>
#include <android/log.h>
#define LOG(args...) __android_log_print(ANDROID_LOG_INFO, args);
#endif

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#endif