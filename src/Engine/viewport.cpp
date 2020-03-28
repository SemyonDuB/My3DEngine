#include "viewport.h"
#include "navigation.h"
#include "scene.h"
#include "import.h"
#include "shader.h"

#include <QGuiApplication>
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QOpenGLDebugLogger>
#include <QSurfaceFormat>

#include <iostream>

Viewport::Viewport()
    : shaderProgram(new SGE::Shader), scene(new SGE::Scene),
      nvg(new SGE::Navigation)
{
}


void Viewport::initializeGL()
{
    // create debug logger
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    QOpenGLDebugLogger *logger = new QOpenGLDebugLogger(ctx);

    if (logger->initialize())
    {
        std::cout << "\n"
                  << "GL_DEBUG Logger" << logger << "\n";

        // connect logger and start logging
        connect(logger, &QOpenGLDebugLogger::messageLogged, this,
                &Viewport::loggedMessage);
        logger->startLogging();
    }

    printContextInformation();

    SGE::initEngine(*shaderProgram, *scene, *nvg);

    // Get absolute path to object file
    std::string filePath = SGE::getAssetsFileName("models/mini_scene.obj");

    SGE::Import monkey(filePath, *scene);

    nvg->setScene(scene);
    nvg->setVPMatrix(scene->getProj(), scene->getView());
}


void Viewport::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    VPsize.setWidth(w);
    VPsize.setHeight(h);

    nvg->setViewportSize(VPsize);

    float aspect = w / float(h);

    projection.setToIdentity();
    projection.perspective(45.0, aspect, 0.1f, 100.f);
}


void Viewport::paintGL()
{
    view.setToIdentity();
    view.translate(nvg->getViewPos());
    view.rotate(nvg->getXRot() / 16.0f, 1, 0, 0);
    view.rotate(nvg->getYRot() / 16.0f, 0, 1, 0);

    scene->setVPMatrix(projection, view);
    scene->drawAllObj(*shaderProgram);
}


// I stole next functions from Qt tutorial
void Viewport::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));

// Get Profile Information
#define CASE(c)                                                                \
    case QSurfaceFormat::c:                                                    \
        glProfile = #c;                                                        \
        break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
#undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    std::cout << "\n"
              << qPrintable(glType) << qPrintable(glVersion) << "("
              << qPrintable(glProfile) << ")"
              << "\n\n";
}


void Viewport::mousePressEvent(QMouseEvent *e)
{
    nvg->mousePress(e);
    update();
}


void Viewport::mouseMoveEvent(QMouseEvent *e)
{
    nvg->mouseMove(e);
    update();
}


void Viewport::wheelEvent(QWheelEvent *e)
{
    nvg->wheelEv(e);
    update();
}


void Viewport::keyPressEvent(QKeyEvent *ev)
{
    nvg->keyPress(ev);
    update();
}


void Viewport::loggedMessage(const QOpenGLDebugMessage &msg)
{
    QString error;

    switch (msg.severity())
    {
    case QOpenGLDebugMessage::NotificationSeverity:
        error += "--";
        break;
    case QOpenGLDebugMessage::HighSeverity:
        error += "!!";
        break;
    case QOpenGLDebugMessage::MediumSeverity:
        error += "!~";
        break;
    case QOpenGLDebugMessage::LowSeverity:
        error += "~~";
        break;
    case QOpenGLDebugMessage::AnySeverity:
        error += "**";
        break;
    case QOpenGLDebugMessage::InvalidSeverity:
        error += "!*";
        break;
    }

    error += " (";

    // Format based on source
#define CASE(c)                                                                \
    case QOpenGLDebugMessage::c:                                               \
        error += #c;                                                           \
        break
    switch (msg.source())
    {
        CASE(APISource);
        CASE(WindowSystemSource);
        CASE(ShaderCompilerSource);
        CASE(ThirdPartySource);
        CASE(ApplicationSource);
        CASE(OtherSource);
        CASE(InvalidSource);
        CASE(AnySource);
    }
#undef CASE

    error += " : ";
    //
    // Format based on type
#define CASE(c)                                                                \
    case QOpenGLDebugMessage::c:                                               \
        error += #c;                                                           \
        break
    switch (msg.type())
    {
        CASE(ErrorType);
        CASE(DeprecatedBehaviorType);
        CASE(UndefinedBehaviorType);
        CASE(PortabilityType);
        CASE(PerformanceType);
        CASE(OtherType);
        CASE(MarkerType);
        CASE(GroupPushType);
        CASE(GroupPopType);
        CASE(InvalidType);
        CASE(AnyType);
    }
#undef CASE

    error += ")";

    std::cout << qPrintable(error) << "\n";
    std::cout << msg.message().toStdString() << "\n\n";
}
