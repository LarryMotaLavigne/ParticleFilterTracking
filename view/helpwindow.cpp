#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    ui->particlesColumnIDInfo->setText(QString::number(Tools::idParticleTableview));
    ui->particleColumnWeightInfo->setText(QString::number(Tools::weightParticleTableView));

    double blue = Tools::objectColor.val[0];
    double green = Tools::objectColor.val[1];
    double red = Tools::objectColor.val[2];
    ui->Object_Red->setText(QString::number(red));
    ui->Object_Green->setText(QString::number(green));
    ui->Object_Blue->setText(QString::number(blue));

    blue = Tools::labelColor.val[0];
    green = Tools::labelColor.val[1];
    red = Tools::labelColor.val[2];
    ui->Label_Red->setText(QString::number(red));
    ui->Label_Green->setText(QString::number(green));
    ui->Label_Blue->setText(QString::number(blue));


    red = Tools::particleColor.val[0];
    green = Tools::particleColor.val[1];
    blue = Tools::particleColor.val[2];
    ui->Particle_Red->setText(QString::number(red));
    ui->Particle_Green->setText(QString::number(green));
    ui->Particle_Blue->setText(QString::number(blue));

    ui->maxParticleDisplayInfo->setText(QString::number(Tools::maxParticleDisplay));

    ui->EdgeThicknessInfo->setText(QString::number(Tools::edgeThickness));

    ui->rectangleThicknessInfo->setText(QString::number(Tools::rectangleThickness));

    setParticleColor(ui->particleColor1,Tools::colorList.at(0));
    Tools::debugMessage("######");
    setParticleColor(ui->particleColor2,Tools::colorList.at(1));
    setParticleColor(ui->particleColor3,Tools::colorList.at(2));
    setParticleColor(ui->particleColor4,Tools::colorList.at(3));
    setParticleColor(ui->particleColor5,Tools::colorList.at(4));
    setParticleColor(ui->particleColor6,Tools::colorList.at(5));
    setParticleColor(ui->particleColor7,Tools::colorList.at(6));
    setParticleColor(ui->particleColor8,Tools::colorList.at(7));
    setParticleColor(ui->particleColor9,Tools::colorList.at(8));
    setParticleColor(ui->particleColor10,Tools::colorList.at(9));
    setParticleColor(ui->particleColor11,Tools::colorList.at(10));
    setParticleColor(ui->particleColor12,Tools::colorList.at(11));
}

HelpWindow::~HelpWindow()
{
    delete ui;
}



void HelpWindow::setParticleColor(QLabel* label, cv::Scalar scalar)
{
    QPalette* palette = new QPalette();
    int blue = scalar.val[0];
    int green = scalar.val[1];
    int red = scalar.val[2];
    //Tools::debugMessage("R:"+QString::number(red)+", G:"+QString::number(green)+", B:"+QString::number(blue));
    palette->setColor(label->backgroundRole(),QColor(red,green,blue));
    label->setAutoFillBackground(true);
    label->setPalette(*palette);
}
