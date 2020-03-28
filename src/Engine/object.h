#pragma once
#include <QMatrix4x4>
#include <QOpenGLFunctions_4_3_Core>
#include <QVector>
#include <memory>

#include "mesh.h"

class QOpenGLShaderProgram;

namespace SGE
{

    class Object
    {
    public:
        Object();

        void drawObject(QOpenGLShaderProgram &program);

        void setupObj(std::shared_ptr<QMatrix4x4> proj,
                      std::shared_ptr<QMatrix4x4> view);

        const QVector3D getCurrentPos() const;

        // inline functions
        void addMesh(const Mesh &mesh) { meshes.push_back(mesh); }

        void setObjVPMatrix(std::shared_ptr<QMatrix4x4> &view,
                            std::shared_ptr<QMatrix4x4> &proj)
        {
            m_projection = proj;
            m_view = view;
        }

        // overloaded functions
        void setObjLocation(const QVector3D location)
        {
            model->translate(location);
        }

        void setObjLocation(const QMatrix4x4 coord) { *model = coord; }

        void changeSelection() { objSelected = !objSelected; }

        bool isSelected() const { return objSelected; }

        std::shared_ptr<QMatrix4x4> getModelMatrix() { return model; }

    private:
        QOpenGLFunctions_4_3_Core *f;
        std::vector<Mesh> meshes;
        std::shared_ptr<QMatrix4x4> model;

        std::shared_ptr<QMatrix4x4> m_projection;
        std::shared_ptr<QMatrix4x4> m_view;
        QVector3D objColor;
        bool objSelected;
    };
} // namespace SGE
