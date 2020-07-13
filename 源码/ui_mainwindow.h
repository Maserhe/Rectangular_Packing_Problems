/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_3;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_4;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_5;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(385, 20, 366, 511));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(widget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_4->addWidget(widget_2);

        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_4->addWidget(tableWidget);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_4->addWidget(widget_3);

        widget_12 = new QWidget(centralwidget);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        widget_12->setGeometry(QRect(20, 10, 259, 522));
        verticalLayout_3 = new QVBoxLayout(widget_12);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(widget_12);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(groupBox);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(61, 31));

        horizontalLayout_3->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(widget_4);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMinimumSize(QSize(61, 31));
        doubleSpinBox->setMaximumSize(QSize(61, 31));

        horizontalLayout_3->addWidget(doubleSpinBox);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(groupBox);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(61, 31));

        horizontalLayout_4->addWidget(label_2);

        doubleSpinBox_2 = new QDoubleSpinBox(widget_5);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setMinimumSize(QSize(61, 31));
        doubleSpinBox_2->setMaximumSize(QSize(61, 31));

        horizontalLayout_4->addWidget(doubleSpinBox_2);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(groupBox);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(widget_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(61, 31));

        horizontalLayout_5->addWidget(label_3);

        doubleSpinBox_3 = new QDoubleSpinBox(widget_6);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
        doubleSpinBox_3->setMinimumSize(QSize(61, 31));
        doubleSpinBox_3->setMaximumSize(QSize(31, 31));
        doubleSpinBox_3->setSingleStep(0.100000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_3);


        verticalLayout_2->addWidget(widget_6);

        widget_7 = new QWidget(groupBox);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(widget_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(61, 31));

        horizontalLayout_6->addWidget(label_4);

        doubleSpinBox_4 = new QDoubleSpinBox(widget_7);
        doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));
        doubleSpinBox_4->setMinimumSize(QSize(61, 31));
        doubleSpinBox_4->setMaximumSize(QSize(61, 31));
        doubleSpinBox_4->setSingleStep(1.000000000000000);

        horizontalLayout_6->addWidget(doubleSpinBox_4);


        verticalLayout_2->addWidget(widget_7);

        widget_8 = new QWidget(groupBox);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_5 = new QLabel(widget_8);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(61, 31));

        horizontalLayout_7->addWidget(label_5);

        doubleSpinBox_5 = new QDoubleSpinBox(widget_8);
        doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));
        doubleSpinBox_5->setMinimumSize(QSize(61, 31));
        doubleSpinBox_5->setMaximumSize(QSize(61, 31));
        doubleSpinBox_5->setSingleStep(0.001000000000000);

        horizontalLayout_7->addWidget(doubleSpinBox_5);


        verticalLayout_2->addWidget(widget_8);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_12);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_9 = new QWidget(groupBox_2);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        horizontalLayout_8 = new QHBoxLayout(widget_9);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_6 = new QLabel(widget_9);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(61, 31));
        label_6->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_8->addWidget(label_6);

        lineEdit_2 = new QLineEdit(widget_9);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(61, 31));
        lineEdit_2->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_8->addWidget(lineEdit_2);


        verticalLayout->addWidget(widget_9);

        widget_10 = new QWidget(groupBox_2);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        horizontalLayout_9 = new QHBoxLayout(widget_10);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_7 = new QLabel(widget_10);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(61, 31));
        label_7->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_9->addWidget(label_7);

        lineEdit_3 = new QLineEdit(widget_10);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(61, 31));
        lineEdit_3->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_9->addWidget(lineEdit_3);


        verticalLayout->addWidget(widget_10);

        widget_11 = new QWidget(groupBox_2);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        horizontalLayout_10 = new QHBoxLayout(widget_11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(widget_11);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(61, 31));
        label_8->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_10->addWidget(label_8);

        lineEdit_4 = new QLineEdit(widget_11);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(61, 31));
        lineEdit_4->setMaximumSize(QSize(61, 16777215));

        horizontalLayout_10->addWidget(lineEdit_4);


        verticalLayout->addWidget(widget_11);


        verticalLayout_3->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\267\257\345\276\204", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\277\241\346\201\257\345\220\257\345\217\221\345\233\240\345\255\220", nullptr));
        doubleSpinBox->setSpecialValueText(QCoreApplication::translate("MainWindow", "2", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\237\346\234\233\345\220\257\345\217\221\345\233\240\345\255\220", nullptr));
        doubleSpinBox_2->setSpecialValueText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\205\250\345\261\200\344\277\241\346\201\257\347\264\240\346\214\245\345\217\221\345\217\202\346\225\260", nullptr));
        doubleSpinBox_3->setSpecialValueText(QCoreApplication::translate("MainWindow", "0.6", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\261\200\351\203\250\344\277\241\346\201\257\347\264\240\346\214\245\345\217\221\345\217\202\346\225\260", nullptr));
        doubleSpinBox_4->setSpecialValueText(QCoreApplication::translate("MainWindow", "0.1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\350\275\254\347\247\273\345\205\254\345\274\217\344\270\255\347\232\204q0", nullptr));
        doubleSpinBox_5->setSpecialValueText(QCoreApplication::translate("MainWindow", "0.01", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\346\235\220\346\226\231\350\247\204\346\240\274", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\345\256\275\345\272\246", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\351\253\230\345\272\246", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\346\211\277\351\207\215", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "2000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
