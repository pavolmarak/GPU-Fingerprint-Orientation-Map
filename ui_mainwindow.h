/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *omapBlockSizeLabel;
    QSpinBox *omapBlockSize;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QSpinBox *currentWidth;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_2;
    QSpinBox *currentHeight;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QSpinBox *increment;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QSpinBox *howManyIncrements;
    QHBoxLayout *horizontalLayout_10;
    QLabel *omapBlockSizeLabel_2;
    QSpinBox *numTests;
    QPushButton *runTestBTN;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *plot;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *log;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(855, 537);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        horizontalLayout_11 = new QHBoxLayout(groupBox);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        omapBlockSizeLabel = new QLabel(groupBox);
        omapBlockSizeLabel->setObjectName(QStringLiteral("omapBlockSizeLabel"));

        horizontalLayout_4->addWidget(omapBlockSizeLabel, 0, Qt::AlignRight);

        omapBlockSize = new QSpinBox(groupBox);
        omapBlockSize->setObjectName(QStringLiteral("omapBlockSize"));
        omapBlockSize->setMinimum(1);
        omapBlockSize->setMaximum(999999);
        omapBlockSize->setValue(13);

        horizontalLayout_4->addWidget(omapBlockSize);


        horizontalLayout_11->addLayout(horizontalLayout_4);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_6->addWidget(label);

        currentWidth = new QSpinBox(groupBox_2);
        currentWidth->setObjectName(QStringLiteral("currentWidth"));
        currentWidth->setMinimum(3);
        currentWidth->setMaximum(999999);
        currentWidth->setSingleStep(50);
        currentWidth->setValue(50);

        horizontalLayout_6->addWidget(currentWidth);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_7->addWidget(label_2);

        currentHeight = new QSpinBox(groupBox_2);
        currentHeight->setObjectName(QStringLiteral("currentHeight"));
        currentHeight->setMinimum(3);
        currentHeight->setMaximum(999999);
        currentHeight->setSingleStep(50);
        currentHeight->setValue(50);

        horizontalLayout_7->addWidget(currentHeight);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_8->addWidget(label_3);

        increment = new QSpinBox(groupBox_3);
        increment->setObjectName(QStringLiteral("increment"));
        increment->setMinimum(1);
        increment->setMaximum(999999);
        increment->setSingleStep(1);
        increment->setValue(50);

        horizontalLayout_8->addWidget(increment);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);

        howManyIncrements = new QSpinBox(groupBox_3);
        howManyIncrements->setObjectName(QStringLiteral("howManyIncrements"));
        howManyIncrements->setMinimum(0);
        howManyIncrements->setMaximum(999999);
        howManyIncrements->setSingleStep(1);
        howManyIncrements->setValue(10);

        horizontalLayout_9->addWidget(howManyIncrements);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_5->addWidget(groupBox_3);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        omapBlockSizeLabel_2 = new QLabel(groupBox_4);
        omapBlockSizeLabel_2->setObjectName(QStringLiteral("omapBlockSizeLabel_2"));

        horizontalLayout_10->addWidget(omapBlockSizeLabel_2, 0, Qt::AlignRight);

        numTests = new QSpinBox(groupBox_4);
        numTests->setObjectName(QStringLiteral("numTests"));
        numTests->setMaximum(999999);
        numTests->setValue(50);

        horizontalLayout_10->addWidget(numTests, 0, Qt::AlignLeft);


        verticalLayout_4->addLayout(horizontalLayout_10);


        horizontalLayout_11->addWidget(groupBox_4);


        horizontalLayout_3->addWidget(groupBox);

        runTestBTN = new QPushButton(centralWidget);
        runTestBTN->setObjectName(QStringLiteral("runTestBTN"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(runTestBTN->sizePolicy().hasHeightForWidth());
        runTestBTN->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(runTestBTN);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(plot);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        log = new QTextEdit(groupBox_5);
        log->setObjectName(QStringLiteral("log"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy4);
        log->setMinimumSize(QSize(300, 0));

        verticalLayout_5->addWidget(log);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_5->addWidget(label_5, 0, Qt::AlignHCenter);


        horizontalLayout_2->addWidget(groupBox_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 855, 17));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GPU Orientation Map", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Performance test adjustment", nullptr));
        omapBlockSizeLabel->setText(QApplication::translate("MainWindow", "O-Map blocksize", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Image size", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Starting image size", nullptr));
        label->setText(QApplication::translate("MainWindow", "Width", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Height", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Test length configuration", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Size increment", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "How many increments?", nullptr));
        omapBlockSizeLabel_2->setText(QApplication::translate("MainWindow", "Number of tests per size", nullptr));
        runTestBTN->setText(QApplication::translate("MainWindow", "Run test", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Log", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Green color indicates shorter processing time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
