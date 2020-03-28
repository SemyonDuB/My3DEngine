#pragma once

#include <QOpenGLWindow>

#include "engine.h"
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QString>
#include <memory>


class QOpenGLDebugMessage;
class QKeyEvent;


namespace SGE
{
    class Scene;
    class Shader;
    class Navigation;
} // namespace SGE


class Viewport : public QOpenGLWindow
{
    Q_OBJECT

public:
    Viewport();

    void printContextInformation();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *ev) override;

    QRect VPsize;

    QMatrix4x4 projection;
    QMatrix4x4 view;

    std::shared_ptr<SGE::Shader> shaderProgram;
    std::shared_ptr<SGE::Scene> scene;
    std::shared_ptr<SGE::Navigation> nvg;

public slots:
    // OpenGL debuging
    void loggedMessage(const QOpenGLDebugMessage &msg);
};
