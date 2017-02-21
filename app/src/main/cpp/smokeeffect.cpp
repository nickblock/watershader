#include "smokeeffect.h"
#include "app.h"

const char* smokeVertex = {
  "attribute vec3 in_position;\n"
  "varying vec3 pos;\n"

  "void main() {\n"
  "pos = in_position;\n"
  "gl_Position = vec4(in_position, 1.0);\n"
  "}\n"
};
const char* smokeFrag = {
"  uniform vec2 res;\n"
"  uniform sampler2D bufferTexture;//Our input texture\n"
"  uniform vec3 smokeSource;//The x,y are the posiiton. The z is the power/density\n"
"  uniform float time;\n"
"  varying vec3 pos;\n"
"  void main() {\n"
"         vec2 uvTrue = 0.5*pos.xy + vec2(0.5, 0.5);\n"
"         vec2 uv = -1.0 + 2.0 * uvTrue;\n"
"        vec2 pixel = uvTrue * res;\n"
"\n"
"        float dist = distance(smokeSource.xy,pixel.xy);\n"
"\n"
"        gl_FragColor = texture2D( bufferTexture, uvTrue );\n"
"\n"
"        //Generate smoke when mouse is pressed\n"
"    gl_FragColor.rgb += smokeSource.z * max(15.0-dist,0.0);\n"
"     return;\n"
"    //Generate fixed smoke (this is the little point moving around in the center)\n"
"    vec2 smokePoint = vec2(res.x/2.0+100.0*sin(time),res.y/2.0+cos(time*3.5)*20.0);\n"
"    dist = distance(smokePoint,gl_FragCoord.xy);\n"
"    gl_FragColor.rgb += 0.01 * max(15.0-dist,0.0);\n"
"\n"
"        //Smoke diffuse\n"
"        float xPixel = 1.0/res.x;//The size of a single pixel\n"
"        float yPixel = 1.0/res.y;\n"
"        vec4 rightColor = texture2D(bufferTexture,vec2(pixel.x+xPixel,pixel.y));\n"
"        vec4 leftColor = texture2D(bufferTexture,vec2(pixel.x-xPixel,pixel.y));\n"
"        vec4 upColor = texture2D(bufferTexture,vec2(pixel.x,pixel.y+yPixel));\n"
"        vec4 downColor = texture2D(bufferTexture,vec2(pixel.x,pixel.y-yPixel));\n"
"        //Handle the bottom boundary\n"
"    if(pixel.y <= yPixel){\n"
"      downColor.rgb = vec3(0.0);\n"
"    }\n"
"    //Diffuse equation\n"
"    float factor = 8.0 * 0.016 * (leftColor.r + rightColor.r + downColor.r * 3.0 + upColor.r - 6.0 * gl_FragColor.r);\n"
"\n"
"  //Account for low precision of texels\n"
"    float minimum = 0.003;\n"
"    if(factor >= -minimum && factor < 0.0) factor = -minimum;\n"
"\n"
"    gl_FragColor.rgb += factor; \n"

"  }\n"
};

const char* finalFrag = {

" varying vec3 pos;\n"
" uniform sampler2D tex;\n"
" void main() \n"
" {\n"
"   vec2 uv = pos.xy;\n"
"   gl_FragColor = vec4(texture2D(tex, uv).xyz, 1.0);\n"
" }\n"
};


SmokeEffect::SmokeEffect(int width, int height)
{
  _flipFlop = true;

  _width = width;
  _height = height;

  _mousePos = glm::vec2(0.5);

  _heightMap = std::make_shared<HeightMap>(1);

  _smokeShader = std::make_shared<Shader>();
  _smokeShader->compileProgram(smokeVertex, smokeFrag);

  _resId = glGetUniformLocation(_smokeShader->id(), "res");
  _smokeSourceId = glGetUniformLocation(_smokeShader->id(), "smokeSource");
  _timeId = glGetUniformLocation(_smokeShader->id(), "time");

  _finalShader = std::make_shared<Shader>();
  _finalShader->compileProgram(smokeVertex, finalFrag);
}

void SmokeEffect::setScreen(int width, int height)
{
  Effect::setScreen(width, height);

  _texture[0] = std::make_shared<FrameBuffer>(width, height);
  _texture[1] = std::make_shared<FrameBuffer>(width, height);
}

void SmokeEffect::drawFrame()
{
  _texture[_flipFlop?0:1]->bindFBO();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _smokeShader->use();

  glUniform1f(_timeId, App::getTime());
  glUniform3f(_smokeSourceId, _width*_mousePos.x, _height*_mousePos.y, 0.0f);
  glUniform2f(_resId, _width, _height);

  glActiveTexture(0);
  _texture[_flipFlop?1:0]->bindTex();

  _heightMap->draw(_smokeShader->getPosAttr());

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  _finalShader->use();
  glActiveTexture(0);
  _texture[_flipFlop?0:1]->bindTex();

  _heightMap->draw(_finalShader->getPosAttr());

  _flipFlop = !_flipFlop;
}

void SmokeEffect::touchMove(float x, float y)
{
  _mousePos += glm::vec2(x/10.f, -y/10.f);
  
  if(_mousePos.x > 1.0f)
    _mousePos.x -= 1.0f;
  else if(_mousePos.x < 0.0)
    _mousePos.x += 1.0;

  _mousePos.y = std::max(0.f, std::min(1.f, _mousePos.y));
}