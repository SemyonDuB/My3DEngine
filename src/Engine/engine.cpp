#include "Engine/engine.h"

Engine::Engine()
	: scene(new Scene),
	 shaderProgram()
{
}

Engine::~Engine()
{
    delete scene;
    scene = nullptr;
}

void Engine::initEngine()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    glClearColor(
            scene->background_color[0],
            scene->background_color[1],
            scene->background_color[2],
            scene->background_color[3]);

    shaderProgram.loadShader();
}

void Engine::setScene(Scene &scene)
{
    this->scene = &scene;
}

void Engine::setupObjects() const
{
    for(int i = 0; i < scene->objects.size(); ++i)
    {
        scene->objects[i].setupObj();
    }
}

void Engine::drawObjects()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(
            scene->background_color[0],
            scene->background_color[1],
            scene->background_color[2],
            scene->background_color[3]);

    for (int i = 0; i < scene->objects.size(); ++i)
    {
        scene->objects[i].drawObject(shaderProgram.phongShader);
    }
}

