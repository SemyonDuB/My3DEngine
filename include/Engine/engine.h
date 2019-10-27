#pragma once

#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "scene.h"
#include "shader.h"

class Engine : protected QOpenGLFunctions_4_3_Core
{
public:
    Engine();
    ~Engine();

	void initEngine();
    void setScene(Scene &scene);
	void setupObjects() const;

    void drawObjects();

    Scene *scene;
    Shader shaderProgram;
private:
};

