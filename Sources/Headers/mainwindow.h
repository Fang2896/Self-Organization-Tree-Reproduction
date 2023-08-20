//
// Created by fangl on 2023/7/28.
//

#ifndef MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QFileDialog>

#include "ogladapter.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    OGLAdapter *oglAdapter;

    QLabel *titleLabel;
    QFrame *titleSplitLine;

    QCheckBox *lineModeCheck;
    QCheckBox *lightingCheck;
    QFrame *renderSplitLine;

    QLabel *fileNameLabel;
    QPushButton *openFileButton;
    QLabel *modelSizeLabel;
    QDoubleSpinBox *modelScaleDoubleSpinBox;
    QFrame *loadModelSplitLine;
    QPushButton *clearLoadedModelButton;

    QLabel *treeGrowthControlLabel;
    QPushButton *performGrowthButton;
    QPushButton *resetGrowthButton;
    QLabel *iterationLabel;
    QLabel *iterationTimesLabel;
    QFrame *treeGrowthControlSplitLine;

    QLabel *treeGrowthParamsLabel;

    void ConfigLayout();

private slots:
    void updateOGLAdapter(){
        oglAdapter->update();
    }

    void lineModeChangeCheck(int state);
    void lightingOpenCheck(int state);
    void loadNewModelButtonPush();
    void adjustModelScaling(double value);
    void clearLoadedModelPush();
    void performGrowthButtonPush();
    void resetTreeGrowthPush();

};


#endif //MY_MAINWINDOW_H
