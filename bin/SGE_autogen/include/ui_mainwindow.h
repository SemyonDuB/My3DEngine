/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTabWidget *scenes;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTreeWidget *outliner;
    QMenuBar *menubar;
    QMenu *menufile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(805, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setMinimumSize(QSize(0, 0));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(1);
        splitter->setChildrenCollapsible(true);
        scenes = new QTabWidget(splitter);
        scenes->setObjectName(QString::fromUtf8("scenes"));
        scenes->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scenes->sizePolicy().hasHeightForWidth());
        scenes->setSizePolicy(sizePolicy2);
        scenes->setMinimumSize(QSize(0, 0));
        scenes->setBaseSize(QSize(0, 0));
        scenes->setContextMenuPolicy(Qt::DefaultContextMenu);
        scenes->setAcceptDrops(false);
        scenes->setTabPosition(QTabWidget::North);
        scenes->setElideMode(Qt::ElideRight);
        scenes->setDocumentMode(false);
        scenes->setTabsClosable(true);
        scenes->setMovable(false);
        scenes->setTabBarAutoHide(false);
        splitter->addWidget(scenes);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        outliner = new QTreeWidget(tab);
        outliner->setObjectName(QString::fromUtf8("outliner"));

        verticalLayout->addWidget(outliner);

        tabWidget->addTab(tab, QString());
        splitter->addWidget(tabWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 805, 22));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menufile->menuAction());

        retranslateUi(MainWindow);

        scenes->setCurrentIndex(-1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = outliner->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
