//
// Created by nick on 04/02/17.
//
#include <GLES2/gl2.h>


void on_surface_created()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}
void on_surface_changed()
{

}

void on_draw_frame()
{
    glClear(GL_COLOR_BUFFER_BIT);

}