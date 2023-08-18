/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *label;
    QCheckBox *checkBox;
    QFrame *line;
    QCheckBox *checkBox_2;
    QFrame *line_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QFrame *line_3;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(723, 459);
        label = new QLabel(MainWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(550, 10, 161, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        font.setKerning(true);
        label->setFont(font);
        checkBox = new QCheckBox(MainWindow);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(560, 70, 131, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        checkBox->setFont(font1);
        line = new QFrame(MainWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(550, 50, 161, 16));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        line->setFont(font2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        checkBox_2 = new QCheckBox(MainWindow);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(560, 100, 131, 21));
        checkBox_2->setFont(font1);
        line_2 = new QFrame(MainWindow);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(550, 120, 161, 16));
        line_2->setFont(font2);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(MainWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(550, 170, 161, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        pushButton->setFont(font3);
        label_2 = new QLabel(MainWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(550, 140, 161, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Cascadia Mono"));
        font4.setPointSize(11);
        font4.setUnderline(false);
        label_2->setFont(font4);
        label_2->setFrameShape(QFrame::Box);
        label_2->setTextFormat(Qt::RichText);
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        line_3 = new QFrame(MainWindow);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(550, 240, 161, 16));
        line_3->setFont(font2);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(MainWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(550, 210, 41, 16));
        label_3->setFont(font3);
        doubleSpinBox = new QDoubleSpinBox(MainWindow);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(600, 210, 121, 22));
        doubleSpinBox->setFont(font3);
        doubleSpinBox->setDecimals(4);
        doubleSpinBox->setMinimum(0.001000000000000);
        doubleSpinBox->setMaximum(1.000000000000000);
        doubleSpinBox->setSingleStep(0.002500000000000);
        doubleSpinBox->setValue(0.001000000000000);
        pushButton_2 = new QPushButton(MainWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 430, 161, 23));
        pushButton_2->setFont(font3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Project Title", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "PolyLine Mode", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "Open Lighting", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Load New Model", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Empty Now", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Size:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Clear Loaded Model", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
