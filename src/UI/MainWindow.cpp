#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Viewport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Viewport *viewport = new Viewport;
    QWidget *container = QWidget::createWindowContainer(viewport);

    ui->scenes->addTab(container, "Scene");
}

MainWindow::~MainWindow()
{
    delete ui;
}
