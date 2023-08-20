//
// Created by fangl on 2023/7/28.
//

#include "mainwindow.h"
#include "Forms/ui_MainWindow.h"

const int OGL_DEFAULT_WIDTH = 800;
const int OGL_DEFAULT_HEIGHT = 600;


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    oglAdapter = new OGLAdapter(this, OGL_DEFAULT_WIDTH, OGL_DEFAULT_HEIGHT);

    // Layout
    ConfigLayout();

    // something to be initialized or connected
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateOGLAdapter);
    timer->start(10);

    connect(lineModeCheck, &QCheckBox::stateChanged,
            this, &MainWindow::lineModeChangeCheck);
    connect(lightingCheck, &QCheckBox::stateChanged,
            this, &MainWindow::lightingOpenCheck);
    connect(openFileButton, &QPushButton::clicked,
            this, &MainWindow::loadNewModelButtonPush);
    connect(modelScaleDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::adjustModelScaling);
    connect(clearLoadedModelButton, &QPushButton::clicked,
            this, &MainWindow::clearLoadedModelPush);

    // set background color
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(99, 103, 106));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

MainWindow::~MainWindow() {
    delete ui;
}

// protected functions
void MainWindow::keyPressEvent(QKeyEvent *event) {
    oglAdapter->handleKeyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    oglAdapter->handleKeyReleaseEvent(event);
}


// slot functions
void MainWindow::lineModeChangeCheck(int state) {
    if(state == Qt::Checked)
        oglAdapter->isLineMode = true;
    else
        oglAdapter->isLineMode = false;
}

void MainWindow::lightingOpenCheck(int state) {
    if(state == Qt::Checked)
        oglAdapter->isOpenLighting = true;
    else
        oglAdapter->isOpenLighting = false;
}

void MainWindow::loadNewModelButtonPush() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select .obj file"), "../Resources/Models");
    if(filePath.isEmpty()) {
        qDebug() << "No obj file selected. ";
        return;
    }

    qDebug() << "Loading New Model. Path: " + filePath;
    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    fileNameLabel->setText(fileName);

    OGLAdapter::changeObjModel(filePath);
}

void MainWindow::adjustModelScaling(double value) {
    oglAdapter->modelScaling = (float)value;
    oglAdapter->setFocus();
}

void MainWindow::clearLoadedModelPush() {
    OGLAdapter::clearLoadedModel();
    fileNameLabel->setText("Empty Now");
}


// utils functions
void MainWindow::ConfigLayout() {
    titleLabel = ui->label;
    titleSplitLine = ui->line;

    lineModeCheck = ui->checkBox;
    lightingCheck = ui->checkBox_2;
    renderSplitLine = ui->line_2;

    fileNameLabel = ui->label_2;
    modelSizeLabel = ui->label_3;
    modelScaleDoubleSpinBox = ui->doubleSpinBox;
    openFileButton = ui->pushButton;
    clearLoadedModelButton = ui->pushButton_2;
    loadModelSplitLine = ui->line_3;

    treeGrowthControlLabel = ui->label_4;
    performGrowthButton = ui->pushButton_3;
    resetGrowthButton = ui->pushButton_4;
    iterationLabel = ui->label_5;
    iterationTimesLabel = ui->label_6;
    treeGrowthControlSplitLine = ui->line_4;

    treeGrowthParamsLabel = ui->label_7;

    auto *hScalingModelLayout = new QHBoxLayout;
    hScalingModelLayout->addWidget(modelSizeLabel);
    hScalingModelLayout->addWidget(modelScaleDoubleSpinBox);

    auto *hIterationTimesLayout = new QHBoxLayout;
    hIterationTimesLayout->addWidget(iterationLabel);
    hIterationTimesLayout->addWidget(iterationTimesLabel);

    auto *vToolLayout = new QVBoxLayout;
    vToolLayout->addWidget(titleLabel);
    vToolLayout->addWidget(titleSplitLine);

    vToolLayout->addWidget(lineModeCheck);
    vToolLayout->addWidget(lightingCheck);
    vToolLayout->addWidget(renderSplitLine);

    vToolLayout->addWidget(fileNameLabel);
    vToolLayout->addLayout(hScalingModelLayout);
    vToolLayout->addWidget(openFileButton);
    vToolLayout->addWidget(clearLoadedModelButton);
    vToolLayout->addWidget(loadModelSplitLine);

    vToolLayout->addWidget(treeGrowthControlLabel);
    vToolLayout->addWidget(performGrowthButton);
    vToolLayout->addWidget(resetGrowthButton);
    vToolLayout->addLayout(hIterationTimesLayout);
    vToolLayout->addWidget(treeGrowthControlSplitLine);

    // TODO: add more parameters settings
    vToolLayout->addWidget(treeGrowthParamsLabel);
    // .....

    vToolLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    auto *vGLLayout = new QVBoxLayout;
    vGLLayout->addWidget(oglAdapter);
    // TODO: add more information display in GL.

    auto *hOverallLayout = new QHBoxLayout;
    hOverallLayout->addLayout(vGLLayout, 5);
    hOverallLayout->addLayout(vToolLayout);

    this->setLayout(hOverallLayout);
}



