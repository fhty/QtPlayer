#include "videowidget.h"

#include <QPainter>
#include <QDebug>

VideoWidget::VideoWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void VideoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    //mutex.lock();
    painter.begin(this);
    painter.drawImage(QPoint(0, 0), m_Img);
    painter.end();
    //mutex.unlock();
}

void VideoWidget::SetImg(QImage img)
{
    if(img.bits()!=0){
        m_Img=img;
        update();
    }
}

//void VideoWidget::setImg(cv::Mat &mat)
//{
//    //qDebug() <<__TIME__<< __FILE__ << __LINE__ ;
//    //qDebug()<<"set img id:"<<QThread::currentThreadId();
//    QImage::Format f = QImage::Format_RGB888;
//    int pixSize = 3;//像素大小。
//    if (m_Img.isNull() || m_Img.format() != f) {
//        delete m_Img.bits();
//        uchar *buf = new uchar[width()*height() * pixSize];
//        m_Img = QImage(buf, width(), height(), f);//BGR->RGB
//    }
//    cv::Mat des;
//    if (mat.empty()) return;
//    cv::resize(mat, des, cv::Size(m_Img.size().width(), m_Img.size().height()));
//    if (pixSize > 1)//当不是灰度图时才需要转换。
//        cv::cvtColor(des, des, 4);//色彩转换COLOR_RGB2BGR
//    memcpy(m_Img.bits(), des.data, des.cols*des.rows*des.elemSize());//行*列*单位元素大小
//    //qDebug() <<__TIME__<< __FILE__ << __LINE__ ;
//    update();
//}
