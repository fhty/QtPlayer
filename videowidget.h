#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <QImage>

class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
signals:

public slots:
    //void setImg(cv::Mat&);
    void SetImg(QImage img);

private:
    QImage m_Img;
    //QMutex mutex;
};

#endif // VIDEOWIDGET_H
