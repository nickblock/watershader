//
// Created by nick on 05/02/17.
//

#include "watershader.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <cmath>
#include <string.h>
#include <android/log.h>

void CHECKGL_ERROR()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR) {
    __android_log_print(ANDROID_LOG_INFO, "glError %d %s:%d ", __FILE__, __LINE__);
    std::exit(1);
  }
}

const char* fragSource = {
        "varying vec3 position;\n"
        "varying vec3 worldNormal;\n"
        "varying vec3 eyeNormal;\n"
        "uniform vec3 eyePos;\n"
        "uniform samplerCube envMap;\n"
        "\n"
        "void main() {\n"
        "vec3 eye = normalize(eyePos - position);\n"
        "vec3 r = reflect(eye, worldNormal);\n"
        "vec4 color = textureCube(envMap, r);\n"
        "color.a = 0.5;\n"
        "gl_FragColor = color;\n"
        "}\n"

};

const char* vertexSource = { 
                "const float pi = 3.14159;\n"
                " attribute vec3 in_position;\n"
                " uniform mat4 MVPMatrix;\n"
                " uniform mat4 normalMatrix;\n"
                " uniform float waterHeight;\n"
                " uniform float time;\n"
                " uniform int numWaves;\n"
                " uniform float amplitude[8];\n"
                " uniform float wavelength[8];\n"
                " uniform float speed[8];\n"
                " uniform vec2 direction[8];\n"
                " varying vec3 position;\n"
                " varying vec3 worldNormal;\n"
                " varying vec3 eyeNormal;\n"
                "\n"
                "float wave(int i, float x, float y) {\n"
                "float frequency = 2.0*pi/wavelength[i];\n"
                "float phase = speed[i] * frequency;\n"
                "float theta = dot(direction[i], vec2(x, y));\n"
                "return amplitude[i] * sin(theta * frequency + time * phase);\n"
                "}\n"
                "\n"
                "float waveHeight(float x, float y) {\n"
                "float height = 0.0;\n"
                "for (int i = 0; i < numWaves; ++i)\n"
                "height += wave(i, x, y);\n"
                "return height;\n"
                "}\n"
                "\n"
                "float dWavedx(int i, float x, float y) {\n"
                "float frequency = 2.0*pi/wavelength[i];\n"
                "float phase = speed[i] * frequency;\n"
                "float theta = dot(direction[i], vec2(x, y));\n"
                "float A = amplitude[i] * direction[i].x * frequency;\n"
                "return A * cos(theta * frequency + time * phase);\n"
                "}\n"
                "\n"
                "float dWavedy(int i, float x, float y) {\n"
                "float frequency = 2.0*pi/wavelength[i];\n"
                "float phase = speed[i] * frequency;\n"
                "float theta = dot(direction[i], vec2(x, y));\n"
                "float A = amplitude[i] * direction[i].y * frequency;\n"
                "return A * cos(theta * frequency + time * phase);\n"
                "}\n"
                "\n"
                "vec3 waveNormal(float x, float y) {\n"
                "float dx = 0.0;\n"
                "float dy = 0.0;\n"
                "for (int i = 0; i < numWaves; ++i) {\n"
                "dx += dWavedx(i, x, y);\n"
                "dy += dWavedy(i, x, y);\n"
                "}\n"
                "vec3 n = vec3(-dx, -dy, 1.0);\n"
                "return normalize(n);\n"
                "}\n"
                "\n"
                "void main() {\n"
                "vec4 pos = vec4(in_position, 1.0);\n"
                "pos.z = waterHeight + waveHeight(pos.x, pos.y);\n"
                "position = pos.xyz / pos.w;\n"
                "worldNormal = waveNormal(pos.x, pos.y);\n"
                "eyeNormal = vec3(normalMatrix * vec4(worldNormal, 1.0));\n"
                "gl_Position = MVPMatrix * pos;\n"
                "}\n"
};


void compileStatus(GLuint id)
{
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *buffer = new GLchar[logLength];
        glGetShaderInfoLog(id, logLength, &logLength, buffer);
        __android_log_print(ANDROID_LOG_INFO, "%s", buffer);
        delete [] buffer;
        std::exit(1);
    }
}
WaterShader::WaterShader() {

    _programId = glCreateProgram();

    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    CHECKGL_ERROR();

    int len = strlen(vertexSource);
    //const char* vSource = vertexSource.c_str();
    glShaderSource(vertexId, 1, &vertexSource, &len);
    CHECKGL_ERROR();

    glCompileShader(vertexId);
    compileStatus(vertexId);
    CHECKGL_ERROR();
    glAttachShader(_programId, vertexId);

    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
    CHECKGL_ERROR();

    len = strlen(fragSource);
    //const char* fSource = fragSource.c_str();
    glShaderSource(fragId, 1, &fragSource, &len);
    CHECKGL_ERROR();

    glCompileShader(fragId);
    compileStatus(fragId);
    CHECKGL_ERROR();
    glAttachShader(_programId, fragId);

    glLinkProgram(_programId);
    CHECKGL_ERROR();


    printf("Created WaterShader");

    glUseProgram(_programId);
    CHECKGL_ERROR();

    GLuint waterHeightId = glGetUniformLocation(_programId, "waterHeight");
    glUniform1f(waterHeightId, 1.f);
    CHECKGL_ERROR();
    GLuint numWavesId = glGetUniformLocation(_programId, "numWaves");
    glUniform1i(numWavesId, 4);
    CHECKGL_ERROR();
    GLuint envMapId = glGetUniformLocation(_programId, "envMap");    
    glUniform1i(envMapId, 0);
    CHECKGL_ERROR();
    
    for (int i = 0; i < 4; ++i) {
        float amplitude = 0.5f / (i + 1);
        {
            std::stringstream ss;
            ss << "amplitude[" << i << "]";
            GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
            if(locId >= 0) {
                glUniform1f(locId, amplitude);
            }

            CHECKGL_ERROR();
        }

        float wavelength = 8 * M_PI / (i + 1);
        {
            std::stringstream ss;
            ss << "wavelength[" << i << "]";
            GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
            if(locId >= 0) {
                glUniform1f(locId, wavelength);
            }

            CHECKGL_ERROR();
        }

        float speed = 1.0f + 2*i;
        {
            std::stringstream ss;
            ss << "speed[" << i << "]";
            GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
            if(locId >= 0) {
                glUniform1f(locId, speed);
            }

            CHECKGL_ERROR();
        }

        float angle = -M_PI/3 + i * (M_PI/12);
        {
            std::stringstream ss;
            ss << "direction[" << i << "]";
            GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
            if(locId >= 0) {
                glUniform2f(locId, cos(angle), sin(angle));
            }

            CHECKGL_ERROR();
        }
    }
}
