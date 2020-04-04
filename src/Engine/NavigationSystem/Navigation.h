#pragma once

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QPoint>
#include <QSharedPointer>
#include <QtCore>

namespace SGE
{

    class Scene;

    class Navigation
    {

    public:
        Navigation();
        Navigation(std::shared_ptr<QMatrix4x4> proj,
                   std::shared_ptr<QMatrix4x4> view,
                   std::shared_ptr<Scene> scene, const QRect &VP);

        void initNavigation();

        void keyPress(QKeyEvent *ev);
        void keyRelease(QKeyEvent *ev);
        void mousePress(QMouseEvent *ev);
        void mouseMove(QMouseEvent *ev);
        void wheelEv(QWheelEvent *ev);

        void moveView(float dx, float dy);

        void selectObj();
        void moveObj();

        // inline functions
        void setVPMatrix(std::shared_ptr<QMatrix4x4> proj,
                         std::shared_ptr<QMatrix4x4> view)
        {
            this->proj = proj;
            this->view = view;
        }

        void setVPMatrix(const QMatrix4x4 &proj, const QMatrix4x4 &view)
        {
            *this->proj = std::move(proj);
            *this->view = std::move(view);
        }

        void setScene(std::shared_ptr<Scene> scene) { this->scene = scene; }

        void setViewportSize(const QRect &VPsize) { VP = VPsize; }

        int getXRot() { return xRot; }

        int getYRot() { return yRot; }

        QVector3D getViewPos() { return QVector3D(xView, yView, zView); }

    private:
        void setXRotation(int angle);
        void setYRotation(int angle);

        std::shared_ptr<QMatrix4x4> proj;
        std::shared_ptr<QMatrix4x4> view;
        std::shared_ptr<Scene> scene;
        QRect VP;
        std::shared_ptr<QOpenGLFunctions> func;

        // 2 coord for calculate path to something
        // using mouse coord
        QPoint mouse;
        QPoint diff;

        bool moveObjInView = false;

        float zView = -10.f;
        float xView = 0;
        float yView = 0;

        int xRot = 0;
        int yRot = 0;

        std::shared_ptr<QMatrix4x4> crntObjModel;
        QVector3D crntObjPos;
    };

} // namespace SGE
