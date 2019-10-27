#include "Engine/scene.h"

Scene::Scene() :
	background_color(QVector4D(0,0,0,1))
{
}

Scene::Scene(QMatrix4x4 &projection, QMatrix4x4 &view) :
	projection(projection),
	view(view)
{
}

void Scene::setProjection(QMatrix4x4 &projection)
{
    this->projection = projection;
    for (int i = 0; i < objects.size(); ++i)
    {
        objects[i].projection = &projection;
    }
}

void Scene::setView(QMatrix4x4 &view)
{
    this->view = view;
    for (int i = 0; i < objects.size(); ++i)
    {
        objects[i].view = &view;
    }
}
