/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableWidget *table;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineBirthday;
    QPushButton *buttonBirthday;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineNewDate;
    QPushButton *buttonChangeDate;
    QPushButton *buttonAddDate;
    QPushButton *buttonOpenFile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1065, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        table = new QTableWidget(centralwidget);
        table->setObjectName("table");

        gridLayout->addWidget(table, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        lineBirthday = new QLineEdit(centralwidget);
        lineBirthday->setObjectName("lineBirthday");

        horizontalLayout_3->addWidget(lineBirthday);

        buttonBirthday = new QPushButton(centralwidget);
        buttonBirthday->setObjectName("buttonBirthday");

        horizontalLayout_3->addWidget(buttonBirthday);


        horizontalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        lineNewDate = new QLineEdit(centralwidget);
        lineNewDate->setObjectName("lineNewDate");

        horizontalLayout_2->addWidget(lineNewDate);

        buttonChangeDate = new QPushButton(centralwidget);
        buttonChangeDate->setObjectName("buttonChangeDate");

        horizontalLayout_2->addWidget(buttonChangeDate);

        buttonAddDate = new QPushButton(centralwidget);
        buttonAddDate->setObjectName("buttonAddDate");

        horizontalLayout_2->addWidget(buttonAddDate);


        horizontalLayout->addLayout(horizontalLayout_2);

        buttonOpenFile = new QPushButton(centralwidget);
        buttonOpenFile->setObjectName("buttonOpenFile");

        horizontalLayout->addWidget(buttonOpenFile);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1065, 23));
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
        label->setText(QCoreApplication::translate("MainWindow", "Your Birthday: ", nullptr));
        buttonBirthday->setText(QCoreApplication::translate("MainWindow", "Day To Your Birtday", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "New Date:", nullptr));
        buttonChangeDate->setText(QCoreApplication::translate("MainWindow", "ChangeDate", nullptr));
        buttonAddDate->setText(QCoreApplication::translate("MainWindow", "Add Date", nullptr));
        buttonOpenFile->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
