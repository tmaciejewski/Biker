//      biker.h
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


#ifndef BIKER_H
#define BIKER_H

#include "object.h"
#include "track.h"

class Biker: public Object
{
    public:
        Biker(const Track &_track);

        void display() const;
        void update(const std::vector<bool> &keyPressed);
        void reset();

        GLfloat getX() { return x; }
        GLfloat getY() { return y; }

        void setFPPCamera();

    private:
        GLfloat w, l, h, angle, lean, speed;
        const Track &track;

        void limitSpeed(GLfloat &speed, const GLfloat limit[]);
};

#endif /* BIKER_H */
