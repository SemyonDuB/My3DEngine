#pragma once
#include <QOpenGLShaderProgram>

#include "mesh.h"

class Object
{
public:
    Object();
    ~Object();

    QVector<Mesh> meshes;

	void drawObject(QOpenGLShaderProgram &program);
    void setupObj();
    void transformObject(QMatrix4x4);

    QMatrix4x4 *projection;
    QMatrix4x4 *view;
    QMatrix4x4 model;
};

