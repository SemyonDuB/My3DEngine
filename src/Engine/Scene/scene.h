#pragma once

#include <memory>

#include "shader.h"
#include "object.h"

namespace SGE
{

    class Scene
    {
    public:
        Scene();
        Scene(const QMatrix4x4 &projection, const QMatrix4x4 &view);

        void initScene();
        void drawAllObj(Shader &shaderProg);

        void selectCurrentObj(qint32 objId);
        void removeSelections();
        void moveSelectObjects(QVector3D offsetObj);
        bool selectionObjectExist();

        // inline functions
        void setProjection(const QMatrix4x4 &projection)
        {
            *m_projection = projection;
        }

        void setView(const QMatrix4x4 &view) { *m_view = view; }

        void setVPMatrix(const QMatrix4x4 &projection, const QMatrix4x4 &view)
        {
            *m_projection = projection;
            *m_view = view;
        }

        void addObject(const Object &obj) { objects.push_front(obj); }

        void deleteObj(qint32 index)
        {
            objects.erase(std::next(objects.begin(), index));
        }

        qint32 numObjects() const { return objects.size(); }

        void setBkgColor(const QVector4D &color) { background_color = color; }

        const std::shared_ptr<QMatrix4x4> getProj() const
        {
            return m_projection;
        }

        const std::shared_ptr<QMatrix4x4> getView() const { return m_view; }

        QVector3D getObjPos(std::size_t index)
        {
            return std::next(objects.begin(), index)->getCurrentPos();
        }

        std::shared_ptr<QMatrix4x4> getObjModelMatrix(qint32 index)
        {
            return std::next(objects.begin(), index)->getModelMatrix();
        }

        qint32 getMainSelectionObj() const { return selectionsObj.back(); }

    private:
        std::list<Object> objects;
        std::shared_ptr<QMatrix4x4> m_projection;
        std::shared_ptr<QMatrix4x4> m_view;

        QVector4D background_color;

        std::list<qint32> selectionsObj;
    };
} // namespace SGE
