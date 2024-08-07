/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *openButton;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QTextEdit *resultsTextEdit;
    QLabel *statsLabel;
    QPushButton *saveButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1191, 616);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName("openButton");
        openButton->setGeometry(QRect(120, 70, 81, 31));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setGeometry(QRect(210, 70, 771, 31));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(990, 70, 81, 31));
        resultsTextEdit = new QTextEdit(centralwidget);
        resultsTextEdit->setObjectName("resultsTextEdit");
        resultsTextEdit->setGeometry(QRect(120, 110, 951, 241));
        statsLabel = new QLabel(centralwidget);
        statsLabel->setObjectName("statsLabel");
        statsLabel->setGeometry(QRect(210, 360, 771, 51));
        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(990, 360, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1191, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openButton->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        statsLabel->setText(QString());
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save Results", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
