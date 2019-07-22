#include "readvidethr.h"
#include <QDebug>
#include <QImage>

static cv::VideoCapture g_Cap;
static bool g_IsRun=true;

ReadVideThr::ReadVideThr(QObject *parent) : QThread(parent)
{
}

ReadVideThr* ReadVideThr::Get()
{
    static ReadVideThr rv;
    return &rv;
}

void ReadVideThr::setPar(QString p,int w,int h)
{
    if(!p.isEmpty()) {m_Path=p;}
    if(w!=0&&h!=0) {
        _WidghtHeight=h;
        _WidghtWidth=w;
    }
}

void ReadVideThr::closeThr()
{
    g_IsRun=false;
    //quit();
    wait();
}

void ReadVideThr::setPause()
{
    if(m_IsPause) {m_IsPause=false;}
    else {m_IsPause=true;}
}

int ReadVideThr::getVideoFrames()
{
    if(frames!=0){
        return frames;
    }
}

int ReadVideThr::getNowFarme()
{
    if(now_fram!=0){
        return now_fram;
    }else {
        return 1;
    }
}

void ReadVideThr::run()
{
    //qDebug() <<__TIME__<< __FILE__ << __LINE__ ;
    qDebug()<<"set img id:"<<QThread::currentThreadId();

    if(m_Path.isEmpty()) {return;}
    g_Cap.open(m_Path.toStdString());
    if(!g_Cap.isOpened()) {return;}

    frames = g_Cap.get(CV_CAP_PROP_FRAME_COUNT);
    fps = g_Cap.get(CV_CAP_PROP_FPS);
    now_fram = 0;
    unsigned int wait = 1000/fps-100/fps;
    qDebug()<<"fps:"<<fps;
    qDebug()<<"time:"<<wait;
    cv::Mat VideoMat;
    while (1) {
        if (m_IsPause) {
            QThread::msleep(100);
            continue;
        }
        if(!g_IsRun) {break;}

        g_Cap.read(VideoMat);
        //cv::imshow("video", m_VideoMat);
        mat2Img(VideoMat);
        emit video2Img(_DesImg);
        mutex.lock();
        now_fram++;
        mutex.unlock();
        if (now_fram == frames) {break;}
        //cv::waitKey(wait);
        QThread::msleep(wait);
    }
}

void ReadVideThr::mat2Img(cv::Mat &mat)
{
    //qDebug() <<__TIME__<< __FILE__ << __LINE__ ;
    //qDebug()<<"set img id:"<<QThread::currentThreadId();
    QImage::Format f = QImage::Format_RGB888;
    int pixSize = 3;//像素大小。
    if (_DesImg.isNull() || _DesImg.format() != f) {
        delete _DesImg.bits();
        uchar *buf = new uchar[_WidghtHeight*_WidghtWidth * pixSize];
        _DesImg = QImage(buf, _WidghtWidth, _WidghtHeight, f);//BGR->RGB
    }
    cv::Mat des;
    if (mat.empty()) return;
    cv::resize(mat, des, cv::Size(_DesImg.size().width(), _DesImg.size().height()));
    if (pixSize > 1)//当不是灰度图时才需要转换。
        cv::cvtColor(des, des, 4);//色彩转换COLOR_RGB2BGR
    memcpy(_DesImg.bits(), des.data, des.cols*des.rows*des.elemSize());//行*列*单位元素大小
}
