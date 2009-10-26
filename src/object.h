//      object.h
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


#ifndef OBJECT_H
#define OBJECT_H

#include <GL/gl.h>
#include <vector>

class Object
{
    public:
        Object(GLfloat _x = 0.0, GLfloat _y = 0.0);
        virtual ~Object();

        virtual void update(const std::vector<bool> &keyPressed) { };
        virtual void display() const { };
        virtual void reset() { };

    protected:

        GLfloat x, y;

        void drawCuboid(GLfloat w, GLfloat l, GLfloat h) const;
};

#endif /* OBJECT_H */
