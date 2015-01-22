#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "display.h"
#include "shader.h"


float vertices1[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left         0
     0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-right        1
     0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // Bottom-right     2
    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f  // Bottom-left      3
};

float vertices2[] = {
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-left         0
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right        1
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom-right     2
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f  // Bottom-left      3
};

GLuint elements1[] = {
    3, 2, 0
};

GLuint elements2[] = {
    3, 2, 1
};

int main(int argc, char *argv[])
{
    Display display("OpenGL", 800, 600);
    display.init();
    display.createWindow();
    display.createContext();

    Shader shader;
    shader.add(GL_VERTEX_SHADER, "res/shaders/vertexShader.glsl");
    shader.add(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.glsl");
    shader.createAndCompile();
    shader.linkAndUse();

    GLuint vao[2];
    glGenVertexArrays(2, vao);

    GLuint vbo[2];
    glGenBuffers(2, vbo);

    GLuint ebo[2];
    glGenBuffers(2, ebo);

    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements1), elements1, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shader.getProgram(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shader.getProgram(), "vs_in_color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements2), elements2, GL_STATIC_DRAW);

    posAttrib = glGetAttribLocation(shader.getProgram(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    colAttrib = glGetAttribLocation(shader.getProgram(), "vs_in_color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));


    SDL_Event windowEvent;
//    Uint32 lastTime = SDL_GetTicks();
    int vao_index = 0;
//    Uint32 frameNumber = 0;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE))
                break;
           if (windowEvent.type == SDL_MOUSEBUTTONUP && windowEvent.button.button == SDL_BUTTON_LEFT)
                vao_index ^= 1;
        }
        glBindVertexArray(vao[vao_index]);
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        display.SwapBuffers();
//        if (frameNumber > 1000)
//        {
//            std::cout << 1000 * frameNumber / (SDL_GetTicks() - lastTime)<< std::endl;
//            lastTime = SDL_GetTicks();
//            frameNumber = 0;
//        }
//        frameNumber++;
    }

    glDeleteBuffers(2, ebo);
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(2, vao);
    SDL_Quit();
    return 0;
}
