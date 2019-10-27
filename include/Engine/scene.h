#pragma once
#include "object.h"
#include "QSize"

class Scene
{
public:
    Scene();
    Scene(QMatrix4x4 &projection, QMatrix4x4 &view);

    void setProjection(QMatrix4x4 &projection);
    void setView(QMatrix4x4 &view);

    QVector<Object> objects;
    QVector4D background_color;

private:
    QMatrix4x4 projection;
    QMatrix4x4 view;
};
