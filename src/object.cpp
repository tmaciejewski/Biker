//      object.cpp
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


#include "object.h"


Object::Object(GLfloat _x, GLfloat _y) : x(_x), y(_y)
{

}


Object::~Object()
{

}

void Object::drawCuboid(GLfloat w, GLfloat l, GLfloat h) const
{
    glBegin(GL_QUADS);
        // down
        glVertex3f(w/2, 0.0, l/2);
        glVertex3f(-w/2, 0.0, l/2);
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(w/2, 0.0, -l/2);

        // up
        glVertex3f(w/2, h, -l/2);
        glVertex3f(-w/2, h, -l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(w/2, h, l/2);

        // back
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(-w/2, h, -l/2);
        glVertex3f(w/2, h, -l/2);
        glVertex3f(w/2, 0.0, -l/2);

        // front
        glVertex3f(w/2, 0.0, l/2);
        glVertex3f(w/2, h, l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(-w/2, 0.0, l/2);

        // left
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(-w/2, 0.0, l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(-w/2, h, -l/2);

        // right
        glVertex3f(w/2, h, -l/2);
        glVertex3f(w/2, h, l/2);
        glVertex3f(w/2, 0.0, l/2);
        glVertex3f(w/2, 0.0, -l/2);

    glEnd();
}
