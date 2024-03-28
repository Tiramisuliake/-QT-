#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QPainter>  //画家类
#include <QPaintEvent>
#include <QTimer>
#include <QString>
#include "tcpwidget.h"
#include <QMovie>


namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = 0);
    ~ControlWidget();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void timerSlot();

    void on_buttonReturn_clicked();

    void on_buttonLED_clicked();

    void on_buttonBeep_clicked();

    void on_buttonFan_clicked();

    void on_buttonControl_clicked();

public slots:
    void startTimerSlot();

signals:
    void backWindow1();
    void startLed();
    void closeLed();
private:
    void initForm();
    void init();
    void initConnect();

    //设置灯的样式
    void setLightStyle(const QString &styleName);

private:
    Ui::ControlWidget *ui;
    QTimer *timer;
     QMovie *myMovie1;
     QMovie *myMovie2;
    QString recData;
    bool controlflag;

    QString m_styleLedOn;                  //灯打开
    QString m_styleLedOff;                 //灯关闭

    QString m_styleFanOn;                  //Fan打开
    QString m_styleFanOff;                 //Fan关闭

    QString m_styleBeepOn;                  //Beep打开
    QString m_styleBeepOff;                 //Beep关闭

    QString m_stylebutOn;                  //but打开
    QString m_stylebutOff;                 //but关闭

    // 追踪灯的状态
        bool isLedOn;
        bool isBeepOn;
        bool isFanOn;

};

#endif // CONTROLWIDGET_H
