//      main.cpp
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

#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <vector>

#include "track.h"
#include "biker.h"

#include "../config.h"

GLfloat a;

class Game
{
    GLsizei screenWidth, screenHeight;
    std::vector<bool> keyPressed;
    bool fullScreen;
    GLfloat x, y, z, hAngle, vAngle;
    Track track;
    Biker biker;

    void update()
    {
        if (keyPressed[SDLK_LEFT])
            hAngle -= 0.01;

        if (keyPressed[SDLK_RIGHT])
            hAngle += 0.01;

        if (keyPressed[SDLK_PAGEUP])
            vAngle += 0.01;

        if (keyPressed[SDLK_PAGEDOWN])
            vAngle -= 0.01;

        if (keyPressed[SDLK_UP])
        {
            y += sin(vAngle);
            x += cos(vAngle)*sin(hAngle);
            z -= cos(vAngle)*cos(hAngle);
        }

        if (keyPressed[SDLK_DOWN])
        {
            y -= sin(vAngle);
            x -= cos(vAngle)*sin(hAngle);
            z += cos(vAngle )*cos(hAngle);
        }

        if (keyPressed[SDLK_RETURN])
            a += 0.1;

        track.update(keyPressed);
        biker.update(keyPressed);
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set perspectivic view
        glViewport(0, 0, screenWidth, screenHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, screenWidth / screenHeight, 1.0, 1000.0);

        // draw scene
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //gluLookAt(biker.getX() - 10.0, 40.0, biker.getY() - 10.0, biker.getX(), 0.0, biker.getY(), 0.0, 1.0, 0.0);
        glRotatef(-vAngle * (180.0 / M_PI), 1.0, 0.0, 0.0);
        glRotatef(hAngle * (180.0 / M_PI), 0.0, 1.0, 0.0);
        glTranslatef(-x, -y, -z);
        track.display();
        biker.display();

        // set orthographical view
        glViewport(screenWidth - 100, screenHeight - 100, 100, 100);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 0.0);

        // draw map
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(-biker.getX(), biker.getY(), 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        track.display();
        biker.display();

        glFlush();
    }

    SDL_Surface * setVideoMode()
    {
        SDL_Surface *surface;
        int flags = SDL_OPENGL | SDL_RESIZABLE | (fullScreen ? SDL_FULLSCREEN : 0);
        if ((surface = SDL_SetVideoMode(screenWidth, screenHeight, 0, flags)) == NULL)
        {
            std::cerr << "Unable to create OpenGL screen: " << SDL_GetError() << '\n';
            SDL_Quit();
            exit(-1);
        }

        return surface;
    }

    void initGL()
    {
        glClearColor(0.4, 0.4, 1.0, 0.0);

        // depth buffer
        glEnable(GL_DEPTH_TEST);

        // perspective correction
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        // culling
        glEnable(GL_CULL_FACE);

        // blending
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel (GL_FLAT);

    }

    public:

    Game(bool fullscreen = false) : screenWidth(640), screenHeight(480),
        keyPressed(SDLK_LAST, false), fullScreen(fullscreen), x(-5.0),
        y(20.0), hAngle(M_PI_2), vAngle(-M_PI_4), track(500, 0.5, 50), biker(track)
    {
        z = track.startY();
        srand(time(0));
    }

    int run()
    {
        SDL_Surface *surface = NULL;
        SDL_Event event;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Unable to initialize SDL: " << SDL_GetError() << '\n';
            return -1;
        }

        surface = setVideoMode();

        SDL_WM_SetCaption(PACKAGE_STRING, NULL);

        initGL();

        while (!keyPressed[SDLK_ESCAPE] && event.type != SDL_QUIT)
        {
            update();
            display();
            SDL_GL_SwapBuffers();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    keyPressed[event.key.keysym.sym] = static_cast<bool>(event.key.state);
                }

                if (event.type == SDL_VIDEORESIZE)
                {
                    screenWidth = event.resize.w;
                    screenHeight = event.resize.h;

                    if (surface)
                        SDL_FreeSurface(surface);

                    surface = setVideoMode();
                }
            }

            usleep(10000);
        }

        SDL_Quit();

        return 0;
    }
};

int main()
{
    Game game;
    return game.run();
}
