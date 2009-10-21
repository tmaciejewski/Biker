//      kolarz.cpp
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

#define PI 3.141592

class Game
{
    GLfloat screenWidth, screenHeight;
    bool keyPressed[SDLK_LAST];

    void update()
    {
    }

    void reshape()
    {
        glViewport(0, 0, (GLsizei) screenWidth, (GLsizei)  screenHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.0, screenWidth / screenHeight, 0.0, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void display()
    {
        reshape();
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();


        glFlush();
    }

    SDL_Surface * setVideoMode()
    {
        SDL_Surface *surface;
        if ((surface = SDL_SetVideoMode(screenWidth, screenHeight, 0, SDL_OPENGL | SDL_RESIZABLE)) == NULL)
        {
            std::cerr << "Unable to create OpenGL screen: " << SDL_GetError() << '\n';
            SDL_Quit();
            exit(-1);
        }

        return surface;
    }

    public:

    Game() : screenWidth(640.0), screenHeight(480.0)
    { }

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

        SDL_WM_SetCaption("Kolarz", NULL);

        while (!keyPressed[SDLK_ESCAPE] && event.type != SDL_QUIT)
        {
            update();
            display();
            SDL_GL_SwapBuffers();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    keyPressed[event.key.keysym.sym] =static_cast<bool>(event.key.state);
                }

                if (event.type == SDL_VIDEORESIZE)
                {
                    screenWidth = event.resize.w;
                    screenHeight = event.resize.h;

                    if (surface)
                        SDL_FreeSurface(surface);

                    surface = setVideoMode();
                    reshape();
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
