#include "Object.h"

SGE::Object::Object()
    : f(new QOpenGLFunctions_4_3_Core), model(new QMatrix4x4),
      m_projection(nullptr), m_view(nullptr), objColor(0.5, 0.5, 1.0),
      objSelected(false)
{
}


void SGE::Object::drawObject(QOpenGLShaderProgram &program)
{
    // Iteration for draw each meshes
    for (auto &mesh : meshes)
    {
        if (objSelected)
        {
            mesh.setColor(QVector3D(1.f, 0.7f, 0.f));
        }
        else
        {
            mesh.setColor(objColor);
        }
        mesh.draw(program, m_projection, m_view, model);
    }
}


void SGE::Object::setupObj(std::shared_ptr<QMatrix4x4> proj,
                           std::shared_ptr<QMatrix4x4> view)
{
    m_projection = proj;
    m_view = view;

    // Iteration for initialization each meshes
    for (auto &mesh : meshes)
    {
        mesh.setColor(objColor);
        mesh.setupMesh();
    }
}


const QVector3D SGE::Object::getCurrentPos() const
{
    QVector3D vec(model->column(3).toVector3D());
    return vec;
}
