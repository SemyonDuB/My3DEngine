#include "Engine/object.h"

Object::Object() :
	projection(nullptr),
	view(nullptr),
	model()
{
}

Object::~Object()
{
    projection = nullptr;
    view = nullptr;
}

void Object::drawObject(QOpenGLShaderProgram &program)
{
    // Iteration for draw each meshes
    for(int i = 0; i < meshes.size(); ++i)
    {
        meshes[i].Draw(program, projection, view, model);
    }
}

void Object::setupObj()
{
    // Iteration for initialization each meshes
    for(int i = 0; i < meshes.size(); ++i)
    {
        meshes[i].setupMesh();
    }
}
