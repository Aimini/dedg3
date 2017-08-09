/********************************************************************************
** Form generated from reading UI file 'dedg3.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEDG3_H
#define UI_DEDG3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dedg3Class
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dedg3Class)
    {
        if (dedg3Class->objectName().isEmpty())
            dedg3Class->setObjectName(QStringLiteral("dedg3Class"));
        dedg3Class->resize(600, 400);
        centralWidget = new QWidget(dedg3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dedg3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(dedg3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        dedg3Class->setStatusBar(statusBar);

        retranslateUi(dedg3Class);

        QMetaObject::connectSlotsByName(dedg3Class);
    } // setupUi

    void retranslateUi(QMainWindow *dedg3Class)
    {
        dedg3Class->setWindowTitle(QApplication::translate("dedg3Class", "dedg3", 0));
    } // retranslateUi

};

namespace Ui {
    class dedg3Class: public Ui_dedg3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEDG3_H
