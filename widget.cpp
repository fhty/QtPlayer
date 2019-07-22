#include "widget.h"
#include "ui_widget.h"
#include "videowidget.h"
#include "readvidethr.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //qDebug()<<"set img id:"<<QThread::currentThreadId();
    setWindowTitle("player");
    setWindowFlag(Qt::WindowMinimizeButtonHint);
    setFixedSize(1300,800);

    connect(ReadVideThr::Get(),&ReadVideThr::video2Img,ui->VideoShow,&VideoWidget::SetImg);
    connect(this,&Widget::destroyed,ReadVideThr::Get(),[&](){
        ReadVideThr::Get()->closeThr();
    });
    connect(ui->OpenBtn, &QPushButton::clicked, this, [=]() {
        path = QFileDialog::getOpenFileName(this, "select", "../");
        if (path.isEmpty()) {
            QMessageBox::information(this, "info:", "no select!");
            return;
        }
        connect(ui->PauseBtn, &QPushButton::clicked, this, [&]() {
            ReadVideThr::Get()->setPause();
        });
        setWindowTitle(path);
        ReadVideThr::Get()->setPar(path,ui->VideoShow->width(),ui->VideoShow->height());
        ReadVideThr::Get()->start();
        ui->TimerSlider->setMaximum(1000);

        this->startTimer(500);
    });

}

void Widget::timerEvent(QTimerEvent *)
{
    ui->TimerSlider->setValue(1000*ReadVideThr::Get()->getNowFarme()/ReadVideThr::Get()->getVideoFrames());
}

Widget::~Widget()
{
    delete ui;
}

