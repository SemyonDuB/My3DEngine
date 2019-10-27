#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QMatrix4x4>
#include <QVector>
#include <QVector3D>
#include <QDebug>
#include <QString>
#include <QMouseEvent>

#include "engine.h"

class Viewport : public QOpenGLWindow
{
   Q_OBJECT

public:
   Viewport();
   ~Viewport() override;

	void printContextInformation();

	Engine *eng;

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    QMatrix4x4 projection;
    QMatrix4x4 view;

    QPoint m_lastPos;
	int m_yRot;
	int m_xRot;

	float m_xView;
	float m_yView;
	float m_zView;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);

};
