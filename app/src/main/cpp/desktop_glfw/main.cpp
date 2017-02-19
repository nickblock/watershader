#include <gl_include.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "app.h"
#include "bitmap.h"

void imageDataFromFile(const char* filename)
{
  BITMAPINFO* info = new BITMAPINFO;
  GLubyte * bytes = LoadDIBitmap(filename, &info);

  int numBytes = info->bmiHeader.biWidth * info->bmiHeader.biHeight * (info->bmiHeader.biBitCount/8);
  App::get()->loadImage((const signed char*)bytes, numBytes, info->bmiHeader.biWidth, info->bmiHeader.biHeight);

  delete info;
  delete bytes;
}

static void error_callback(int error, const char* description)
{
  LOG("Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
      App::get()->nextEffect();
    }
}
static void window_size_callback(GLFWwindow* window, int width, int height)
{
  App::get()->setScreen(width, height);
}
int main(void)
{

  GLFWwindow* window;

  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
      exit(EXIT_FAILURE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(640, 480, "Hatchbaby", NULL, NULL);

  if (!window)
  {
    
    glfwTerminate();
    exit(EXIT_FAILURE);

  }

  glfwSetWindowSizeCallback(window, window_size_callback);
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
#ifdef WIN32
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
#endif
  glfwSwapInterval(1);

  imageDataFromFile("data/lostvalley_east.bmp");
  imageDataFromFile("data/lostvalley_west.bmp");
  imageDataFromFile("data/lostvalley_down.bmp");
  imageDataFromFile("data/lostvalley_up.bmp");
  imageDataFromFile("data/lostvalley_north.bmp");
  imageDataFromFile("data/lostvalley_south.bmp");

  bool init = false;

  while (!glfwWindowShouldClose(window))
  {
    if(!init) {
      App::get()->init();
      App::get()->setScreen(640, 480);
      init = true;
    }

    App::get()->drawFrame();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
