#include "mainwindow.h"
#include <QGuiApplication>
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setVersion(4, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow *win = new MainWindow();
  win->resize(800, 600);
  win->show();

  return a.exec();
}
