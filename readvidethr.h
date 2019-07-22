#ifndef READVIDETHR_H
#define READVIDETHR_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QImage>
#include <QMutex>

class ReadVideThr : public QThread
{
    Q_OBJECT
public:
    static ReadVideThr* Get();
    void run();
    void setPar(QString p,int w,int h);
    void closeThr();
    void setPause();
    void mat2Img(cv::Mat &mat);
    int getVideoFrames();
    int getNowFarme();
signals:
    void video2Mat(cv::Mat&);
    void video2Img(QImage img);
public slots:

private:
    explicit ReadVideThr(QObject *parent = nullptr);

    int _WidghtHeight;
    int _WidghtWidth;
    int frames;
    int fps;
    int now_fram;
    QString m_Path;
    QImage _DesImg;

    bool m_IsPause=false;
    QMutex mutex;
};

#endif // READVIDETHR_H
