//      track.cpp
//
//      Copyright 2009 Tomasz Maciejewski <ponton@jabster.pl>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include "track.h"
#include <cmath>
#include <iostream>

Track::Track(float _w, float _ratio) : Object(), w(_w), ratio(_ratio)
{

}

void Track::drawEllipse(GLfloat xcenter, GLfloat ycenter, GLfloat zcenter, float r1, float r2, int pieces)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(xcenter, ycenter, zcenter);
        for(int i = -pieces/2; i <= pieces/2; ++i)
        {
            float angle = M_PI * i / float(pieces/2);
            GLfloat x = xcenter + r1*sin(angle);
            GLfloat y = ycenter;
            GLfloat z = zcenter + r2*cos(angle);
            glVertex3f(x, y, z);
        }
    glEnd();
}

void Track::display()
{
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    drawEllipse(x, 0.0, y, 10*w, 10*w);         // outer field
    glColor3f(0.23, 0.23, 0.23);
    drawEllipse(x, 0.0, y, w, ratio*w);         // track
    glColor3f(0.0, 1.0, 0.0);
    drawEllipse(x, 0.0, y, (w-3), ratio*(w-3)); // inner field
    glPopMatrix();
}
