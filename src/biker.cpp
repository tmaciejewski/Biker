//      biker.cpp
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


#include "biker.h"
#include <cmath>
#include <GL/glu.h>

Biker::Biker(const Track &_track) : Object(), w(1), l(10), h(5),
    leanLimit(0.01), track(_track)
{
    speedLimit[0] = 2.0;
    speedLimit[1] = 0.2;
    reset();
}

void Biker::reset()
{
    x = 0.0;
    y = track.startY();
    speed = 0.0;
    angle = M_PI_2;
    lean = 0.0;
    leanAngle = 0.0;
}

void Biker::display() const
{
    glPushMatrix();
    glColor3f(1.0, 0.8, 0.2);
    glTranslatef(x, 0.0, y);
    glRotatef(angle * (180.0 / M_PI), 0.0, 1.0, 0.0);
    glRotatef(leanAngle * (180.0 / M_PI), 0.0, 0.0, 1.0);
    drawCuboid(w, l, h);
    glPopMatrix();
}

void Biker::update(const std::vector<bool> &keyPressed)
{
    const GLfloat accel = 0.004, turnSpeed = 0.0001;
    GLfloat friction = 0.001;
    const bool onTrack = track.onTrack(x, y);

    if (!onTrack)
        friction *= 10;

    if (keyPressed['r'])
        reset();

    if (keyPressed['t'])
        speed += 0.1; // turbo

    if (keyPressed['a'] && lean < leanLimit)
        lean += turnSpeed;
    else if (keyPressed['d'] && lean > -leanLimit)
        lean -= turnSpeed;
    else if (lean > turnSpeed)
        lean -= turnSpeed;
    else if (lean < -turnSpeed)
        lean += turnSpeed;
    else
        lean = 0.0;

    leanAngle = (speed/speedLimit[0]) *
        (-lean/leanLimit * M_PI_4/2);

    if (keyPressed['w'] && speed < speedLimit[(onTrack ? 0 : 1)])
    {
        // we're accelerating
        speed += accel;
    }
    else if (keyPressed['s'] && speed > -speedLimit[1])
    {
        // we're braking or going reverse
        speed -= accel;
    }
    // free ride
    else if (speed > friction)
        speed -= friction;
    else if (speed < -friction)
        speed += friction;
    else
        speed = 0.0; // the speed is so near 0.0, that it is in fact 0.0


    angle += lean;
    y += speed*cos(angle);
    x += speed*sin(angle);
}

void Biker::setFPPCamera()
{
    GLfloat p = sin(-leanAngle) * h / 2;
    GLfloat xprim = p * cos(angle), yprim = - p * sin(angle);

    gluLookAt(x + xprim, h/2, y + yprim, x + xprim + sin(angle), h/2, y + yprim + cos(angle), xprim, h/2, yprim);
}
