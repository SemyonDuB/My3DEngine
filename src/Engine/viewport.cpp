#include "Engine/viewport.h"
#include "Engine/import.h"
#include <QGuiApplication>
#include <QSurfaceFormat>

Viewport::Viewport() :
	eng(new Engine()),
	m_lastPos(),
	m_yRot(0),
	m_xRot(0),
	m_xView(0),
	m_yView(0),
	m_zView(-10)
{
}

Viewport::~Viewport()
{
    delete eng;
    eng = nullptr;
}

void Viewport::initializeGL()
{
	printContextInformation();

	eng->initEngine();

	Import monkey("/home/semyon/Projects/Qt/MyEngine/resources/mini_scene.obj",
                   *eng->scene);

    eng->setupObjects();
}

void Viewport::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
    
    float aspect = w / float(h);
    
    projection.setToIdentity();
    projection.perspective(45.0, aspect, 0.1f, 100);

    eng->scene->setProjection(projection);
}

void Viewport::paintGL()
{
    view.setToIdentity();
    view.translate(m_xView, m_yView, m_zView);
    view.rotate(m_xRot / 16.0f, 1, 0, 0);
    view.rotate(m_yRot / 16.0f, 0, 1, 0);

    eng->scene->setView(view);
    eng->drawObjects();
}

// I stole next func from Qt tutorial
void Viewport::printContextInformation()
{
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
        CASE(NoProfile);
        CASE(CoreProfile);
        CASE(CompatibilityProfile);
    }
    #undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion)
             << "(" << qPrintable(glProfile) << ")";
}

void Viewport::mousePressEvent(QMouseEvent *e)
{
    m_lastPos = e->pos();
}

void Viewport::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->x() - m_lastPos.x();
    int dy = e->y() - m_lastPos.y();

    bool shift = QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier);
    bool ctrl = QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier);

    if (e->buttons() & Qt::MiddleButton)
    {
        if(shift)
        {
            m_xView += static_cast<float>(dx)/50;
            m_yView -= static_cast<float>(dy)/50;
            update();
        } else if(ctrl) {
            m_zView += static_cast<float>(dy)/25;
            update();
        }
        else
        {
            setXRotation(m_xRot + 8 * dy);
            setYRotation(m_yRot + 8 * dx);
        }
    }

    m_lastPos = e->pos();
}

void Viewport::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
    {
        ++m_zView;
        update();
    }else{
        --m_zView;
        update();
    }
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void Viewport::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot)
    {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void Viewport::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot)
    {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}
