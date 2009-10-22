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
    w2 = w - 3;
}

bool Track::onTrack(GLfloat _x, GLfloat _y)
{
    float track = (_x*_x) / (w*w) + (_y*_y) / (w*w*ratio*ratio);
    float inner_grass = (_x*_x) / (w2*w2) + (_y*_y) / (w2*w2*ratio*ratio);
    return (track <= 1.0 && inner_grass >= 1.0);
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
    glColor3f(0.0, 0.8, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(x-2*w, 0, y-w);
        glVertex3f(x+2*w, 0, y-w);
        glVertex3f(x+2*w, 0, y+w);
        glVertex3f(x-2*w, 0, y+w);
    glEnd();
    glColor3f(0.23, 0.23, 0.23);
    drawEllipse(x, 0.1, y, w, ratio*w);    // track
    glColor3f(0.0, 0.8, 0.0);
    drawEllipse(x, 0.2, y, w2, ratio*w2);  // inner field
    glPopMatrix();
}
