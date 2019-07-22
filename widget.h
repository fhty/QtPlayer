#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include <QTimer>
#include <QTimerEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void openVideo(QString);
    void timerEvent(QTimerEvent *);
signals:

public slots:

private:
    Ui::Widget *ui;
    int farme;
    QString path;
    QMutex mutex;
};

#endif // WIDGET_H
