#include <QApplication>
#include <QOpenGLContext>
#include <QSurfaceFormat>

#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    auto *context = new QOpenGLContext;
    context->setFormat(format);
    context->create();

    auto *win = new MainWindow;
    win->resize(800, 600);
    win->show();

    return QApplication::exec();
}
