#pragma once

#include <QSharedPointer>
#include <QPoint>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QtCore>
#include <QOpenGLFunctions>

namespace SGE
{
	class Scene;

	class Navigation
	{

	public:
		Navigation();
		Navigation(QSharedPointer<QMatrix4x4> proj,
				   QSharedPointer<QMatrix4x4> view,
				   QSharedPointer<Scene> scene,
				   const QRect &VP);
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
		void setVPMatrix(QSharedPointer<QMatrix4x4> proj,
						 QSharedPointer<QMatrix4x4> view)
		{
			this->proj = proj;
			this->view = view;
		}
		void setVPMatrix(const QMatrix4x4 &proj,
						 const QMatrix4x4 &view)
		{
			*this->proj = proj;
			*this->view = view;
		}

		void setScene(QSharedPointer<Scene> scene)
		{ this->scene = scene; }

		void setViewportSize(const QRect &VPsize)
		{ VP = VPsize; }

		int getXRot()
		{ return xRot; }

		int getYRot()
		{ return yRot; }

		QVector3D getViewPos()
		{ return QVector3D(xView, yView, zView); }
						
	private:
		void setXRotation(int angle);
		void setYRotation(int angle);

		QSharedPointer<QMatrix4x4> proj;
		QSharedPointer<QMatrix4x4> view;
		QSharedPointer<Scene> scene;
		QRect VP;
		QSharedPointer<QOpenGLFunctions> func;

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

		QSharedPointer<QMatrix4x4> crntObjModel;
		QVector3D crntObjPos;
	};
}
