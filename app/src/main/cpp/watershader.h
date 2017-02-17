//
// Created by nick on 05/02/17.
//

#ifndef WATERSHADER_WATERSHADER_H
#define WATERSHADER_WATERSHADER_H

#include "shader.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class WaterShader : public Shader {

public:
    WaterShader();

    GLuint getPosAttr();

    void setUniforms(glm::mat4& mvp, glm::vec3& eyePos, float time, float amplitude, glm::mat4& rotateM);

protected:

    GLuint _posAttribute;

    GLuint _MVPId;
    GLuint _eyePosId;
    GLuint _timeId;
    GLuint _ampId;
    GLuint _rotateViewId;
};


#endif //WATERSHADER_WATERSHADER_H
