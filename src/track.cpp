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
#include <cstdlib>

Track::Track(GLfloat size, GLfloat _ratio, GLfloat _w) : Object(), w(size), ratio(_ratio)
{
    w2 = size - _w;
    for(unsigned i = 0; i < w*w/1000; ++i)
    {
        GLfloat x, y;
        do {
            x = rand() / (float)RAND_MAX * 2*w - w;
            y = rand() / (float)RAND_MAX * 2*w - w;
        } while (onTrack(x, y));
        tree.push_back(TreeCoord(x, y));
    }
}

bool Track::onTrack(GLfloat _x, GLfloat _y) const
{
    GLfloat track = (_x*_x) / (w*w) + (_y*_y) / (w*w*ratio*ratio);
    GLfloat inner_grass = (_x*_x) / (w2*w2) + (_y*_y) / (w2*w2*ratio*ratio);
    return (track <= 1.0 && inner_grass >= 1.0);
}

GLfloat Track::startY() const
{
    return ratio * w2 + ratio * (w - w2) / 2;
}

void Track::drawEllipse(GLfloat xcenter, GLfloat ycenter, GLfloat zcenter,
    GLfloat r1, GLfloat r2, int pieces) const
{
    glPushMatrix();
    glTranslatef(xcenter, ycenter, zcenter);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.0, 0.0);
        for(int i = -pieces/2; i <= pieces/2; ++i)
        {
            GLfloat angle = M_PI * i / GLfloat(pieces/2);
            glVertex3f(r1*sin(angle), 0.0, r2*cos(angle));
        }
    glEnd();
    glPopMatrix();
}

void Track::drawField() const
{
    glPushMatrix();
    glTranslatef(x, 0.0, y);
    glBegin(GL_QUADS);
        glVertex3f(-2*w, 0.0, -2*w);
        glVertex3f(2*w, 0.0, -2*w);
        glVertex3f(2*w, 0.0, 2*w);
        glVertex3f(-2*w, 0.0, 2*w);
    glEnd();
    glPopMatrix();
}

void Track::drawPost(GLfloat x, GLfloat y) const
{
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9);
    glTranslatef(x, 0.0, y);
    drawCuboid(1.0, 1.0, 20.0);
    glPopMatrix();
}

void Track::drawTree(GLfloat x, GLfloat y) const
{
    glPushMatrix();
    glTranslatef(x, 0.0, y);
    glColor3f(0.2, 0.1, 0.1);
    drawCuboid(1.0, 1.0, 10.0);
    glTranslatef(0.0, 10.0, 0.0);
    glColor3f(0.1, 0.7, 0.2);
    drawCuboid(5.0, 5.0, 10.0);
    glPopMatrix();
}

void Track::display() const
{
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    drawField();
    glColor3f(0.8, 0.23, 0.23);
    drawEllipse(x, 0.0, y, w, ratio*w);    // track
    glColor3f(0.1, 0.1, 0.1);
    drawEllipse(x, 0.0, y, w2, ratio*w2);  // inner field
    drawPost(0.0, w2*ratio - 2.0);
    drawPost(0.0, w*ratio + 2.0);
    for (vector<TreeCoord>::const_iterator it = tree.begin(); it != tree.end(); ++it)
        drawTree(it->first, it->second);
    glPopMatrix();
}
