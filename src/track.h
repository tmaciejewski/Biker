//      track.h
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


#ifndef TRACK_H
#define TRACK_H

#include "object.h"

class Track : public Object
{
    public:
        Track(GLfloat size = 30, GLfloat _ratio = 1.0, GLfloat _w = 5);

        void display() const;
        bool onTrack(GLfloat _x, GLfloat _y) const;
        GLfloat startY() const;

    private:

        GLfloat w, w2, ratio;

        void drawEllipse(GLfloat xcenter, GLfloat ycenter, GLfloat zcenter,
            GLfloat r1, GLfloat r2, int pieces = 64) const;

        void drawField() const;
        void drawPost(GLfloat x, GLfloat y) const;

};

#endif /* TRACK_H */
