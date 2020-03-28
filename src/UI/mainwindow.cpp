#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewport.h"

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
