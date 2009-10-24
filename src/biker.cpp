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

Biker::Biker(const Track &_track) : Object(), w(1), l(10), h(5),
    track(_track)
{
    reset();
}

void Biker::reset()
{
    x = 0.0;
    y = track.startY();
    speed = 0.0;
    angle = M_PI_2;
}

void Biker::display() const
{
    glPushMatrix();

    if (track.onTrack(x, y))
        glColor3f(1.0, 0.0, 0.0);
    else
        glColor3f(0.0, 0.0, 0.0);

    glTranslatef(x, 0.0, y);
    glRotatef(angle * (180.0 / M_PI), 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
        // down
        glVertex3f(w/2, 0.0, l/2);
        glVertex3f(-w/2, 0.0, l/2);
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(w/2, 0.0, -l/2);

        // up
        glVertex3f(w/2, h, l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(-w/2, h, -l/2);
        glVertex3f(w/2, h, -l/2);

        // back
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(-w/2, h, -l/2);
        glVertex3f(w/2, h, -l/2);
        glVertex3f(w/2, 0.0, -l/2);

        // front
        glVertex3f(-w/2, 0.0, l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(w/2, h, l/2);
        glVertex3f(w/2, 0.0, l/2);

        // left
        glVertex3f(-w/2, 0.0, -l/2);
        glVertex3f(-w/2, 0.0, l/2);
        glVertex3f(-w/2, h, l/2);
        glVertex3f(-w/2, h, -l/2);

        // right
        glVertex3f(w/2, 0.0, -l/2);
        glVertex3f(w/2, 0.0, l/2);
        glVertex3f(w/2, h, l/2);
        glVertex3f(w/2, h, -l/2);

    glEnd();
    glPopMatrix();
}

void Biker::limitSpeed(GLfloat &speed, const GLfloat limit[])
{
    if (speed < -limit[1])
        speed = -limit[1];

    if (speed > limit[0])
        speed = limit[0];

    if (speed > limit[1] && !track.onTrack(x, y))
        speed = limit[1];
}

void Biker::update(const std::vector<bool> &keyPressed)
{
    const GLfloat speedLimit[] = {2.0, 0.1}, turnSpeed = 0.008;
    const GLfloat accel = 0.001, friction = 0.0005;

    if (keyPressed['r'])
        reset();

    if (keyPressed['a'])
        angle += turnSpeed;

    if (keyPressed['d'])
        angle -= turnSpeed;

    if (keyPressed['w'])
        speed += accel;

    if (keyPressed['s'])
        speed -= accel;

    // speed limitations
    limitSpeed(speed, speedLimit);

    y += speed*cos(angle);
    x += speed*sin(angle);

    if (speed > friction)
        speed -= friction;
    else if (speed < -friction)
        speed += friction;
    else
        speed = 0.0;
}
