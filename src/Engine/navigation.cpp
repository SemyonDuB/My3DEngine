#include "Engine/navigation.h"

#include "Engine/scene.h"

#include <QGuiApplication>


SGE::Navigation::Navigation() 
	: proj(new QMatrix4x4),
	view(new QMatrix4x4),
	scene(nullptr),
	func(new QOpenGLFunctions)
{
}


SGE::Navigation::Navigation(QSharedPointer<QMatrix4x4> proj,
							QSharedPointer<QMatrix4x4> view,
							QSharedPointer<Scene> scene,
							const QRect &VP)
	: proj(proj), 
	view(view), 
	scene(scene), 
	VP(VP),
	func(new QOpenGLFunctions)
{}


void SGE::Navigation ::initNavigation()
{
	func->initializeOpenGLFunctions();
}


void SGE::Navigation::keyPress(QKeyEvent *ev)
{
	if(scene->selectionObjectExist())
	{
		if(ev->key() == Qt::Key_G)
		{
			diff = mouse;

			QVector3D origin(crntObjModel->column(3).toVector3D());
			origin = origin.project(*view, *proj, VP);

			diff.setX(diff.x() - static_cast<qint32>(origin.x()));  
			diff.setY(VP.height() - diff.y() - 
					  static_cast<qint32>(origin.y()));

			if( moveObjInView ) moveObjInView = false;
			else moveObjInView = true;
		}
		if(ev->key() == Qt::Key_X)
		{
			qint32 index = scene->getMainSelectionObj();
			scene->deleteObj(index);
			qDebug() << *crntObjModel;
		}
	}
}


void SGE::Navigation::mousePress(QMouseEvent *ev)
{
	mouse 		  = ev->pos();
	moveObjInView = false;

	if(ev->buttons() == Qt::LeftButton) selectObj();
}


void SGE::Navigation::mouseMove(QMouseEvent *ev)
{
	float dx = static_cast<float>(ev->x() - mouse.x());
	float dy = static_cast<float>(ev->y() - mouse.y());

	if( ev->buttons() == Qt::MiddleButton ) moveView(dx, dy);
	if( moveObjInView ) moveObj();

	mouse = ev->pos();
}


void SGE::Navigation::wheelEv(QWheelEvent *ev)
{
	if(ev->delta() > 0) ++zView;
	else --zView;
}


void SGE::Navigation::moveView(float dx, float dy)
{
	// aliases
	using QGA = QGuiApplication;
	using namespace Qt;

	if(QGA::keyboardModifiers().testFlag(ShiftModifier))
	{
		// move view around location
		xView += dx/50;
		yView -= dy/50;

	} 
	else if(QGA::keyboardModifiers().testFlag(ControlModifier)) {
		// soft view zoom
		zView += dy/25;
	} 
	else {
		// rotate view
		setXRotation(xRot + 8 * static_cast<int>(dy));
		setYRotation(yRot + 8 * static_cast<int>(dx));
	}
}


void SGE::Navigation::selectObj()
{
	GLuint index;
	func->glReadPixels(mouse.x(), VP.height() - mouse.y(), 
					   1, 1, GL_STENCIL_INDEX, 
					   GL_UNSIGNED_INT, &index);


	if( index > 0 )
	{ 
		const qint32 idObj = static_cast<qint32>(index) - 1;

		crntObjModel = scene->getObjModelMatrix(idObj);
		crntObjPos = crntObjModel->column(3).toVector3D();

		scene->selectCurrentObj(idObj);
	}
	else {
		scene->removeSelections();
	}
}


void SGE::Navigation::moveObj()
{
	crntObjPos = crntObjModel->column(3).toVector3D();

	// translate obj position in screen coordinate
	// without model, since we want move obj in view
	crntObjPos = crntObjPos.project(*view, *proj, VP);

	int difX = mouse.x() - diff.x();
	int	difY = VP.height() - mouse.y() - diff.y();

	// move obj in screen coordinate and save Z
	crntObjPos = QVector3D(difX, difY, crntObjPos.z());

	// translate screen coord in global
	// Note: we multiply VIEW * MODEL, but not vice versa!
	crntObjPos = crntObjPos.unproject((*view) * (*crntObjModel),
									  *proj, VP);

	scene->moveSelectObjects(crntObjPos);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void SGE::Navigation::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
    }
}

void SGE::Navigation::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
    }
}
