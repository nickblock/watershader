//
// Created by nick on 05/02/17.
//

#include "watershader.h"

#include <string>
#include <iostream>
#include <cstdlib>

#define CHECKGL_ERROR() \
{\
  GLenum err = glGetError();\
  if(err != 0) {\
    std::cout << "glError " << err << " " <<  __FILE__ << ":" <<__LINE__ << std::endl;\
    std::exit(0); \
  }\
}

const std::string fragSource = {
        "varying vec3 position;"
                "varying vec3 worldNormal;"
                "varying vec3 eyeNormal;"
                "uniform vec3 eyePos;"
                "uniform samplerCube envMap;"
                ""
                "void main() {"
                "vec3 eye = normalize(eyePos - position);"
                "vec3 r = reflect(eye, worldNormal);"
                "vec4 color = textureCube(envMap, r);"
                "color.a = 0.5;"
                "gl_FragColor = color;"
                "}"

};

const std::string vertexSource = {
        "const float pi = 3.14159;"
                " uniform float waterHeight;"
                " uniform float time;"
                " uniform int numWaves;"
                " uniform float amplitude[8];"
                " uniform float wavelength[8];"
                " uniform float speed[8];"
                " uniform vec2 direction[8];"
                " varying vec3 position;"
                " varying vec3 worldNormal;"
                " varying vec3 eyeNormal;"
                ""
                "float wave(int i, float x, float y) {"
                "float frequency = 2*pi/wavelength[i];"
                "float phase = speed[i] * frequency;"
                "float theta = dot(direction[i], vec2(x, y));"
                "return amplitude[i] * sin(theta * frequency + time * phase);"
                "}"
                ""
                "float waveHeight(float x, float y) {"
                "float height = 0.0;"
                "for (int i = 0; i < numWaves; ++i)"
                "height += wave(i, x, y);"
                "return height;"
                "}"
                ""
                "float dWavedx(int i, float x, float y) {"
                "float frequency = 2*pi/wavelength[i];"
                "float phase = speed[i] * frequency;"
                "float theta = dot(direction[i], vec2(x, y));"
                "float A = amplitude[i] * direction[i].x * frequency;"
                "return A * cos(theta * frequency + time * phase);"
                "}"
                ""
                "float dWavedy(int i, float x, float y) {"
                "float frequency = 2*pi/wavelength[i];"
                "float phase = speed[i] * frequency;"
                "float theta = dot(direction[i], vec2(x, y));"
                "float A = amplitude[i] * direction[i].y * frequency;"
                "return A * cos(theta * frequency + time * phase);"
                "}"
                ""
                "vec3 waveNormal(float x, float y) {"
                "float dx = 0.0;"
                "float dy = 0.0;"
                "for (int i = 0; i < numWaves; ++i) {"
                "dx += dWavedx(i, x, y);"
                "dy += dWavedy(i, x, y);"
                "}"
                "vec3 n = vec3(-dx, -dy, 1.0);"
                "return normalize(n);"
                "}"
                ""
                "void main() {"
                "vec4 pos = gl_Vertex;"
                "pos.z = waterHeight + waveHeight(pos.x, pos.y);"
                "position = pos.xyz / pos.w;"
                "worldNormal = waveNormal(pos.x, pos.y);"
                "eyeNormal = gl_NormalMatrix * worldNormal;"
                "gl_Position = gl_ModelViewProjectionMatrix * pos;"
                "}"

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
        printf("%s", buffer);
        delete [] buffer;
    }
}
WaterShader::WaterShader() {

    _programId = glCreateProgram();

    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    CHECKGL_ERROR()

    int len = vertexSource.size();
    const char* vSource = vertexSource.c_str();
    glShaderSource(vertexId, 1, &vSource, &len);
    CHECKGL_ERROR()

    glCompileShader(vertexId);
    compileStatus(vertexId);
    CHECKGL_ERROR()
    glAttachShader(_programId, vertexId);

    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
    CHECKGL_ERROR()

    len = fragSource.size();
    const char* fSource = fragSource.c_str();
    glShaderSource(fragId, 1, &fSource, &len);
    CHECKGL_ERROR()

    glCompileShader(fragId);
    compileStatus(fragId);
    CHECKGL_ERROR()
    glAttachShader(_programId, fragId);

    glLinkProgram(_programId);
    CHECKGL_ERROR()


    printf("Created WaterShader");
}
