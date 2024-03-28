#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>         //定时器
#include <QDateTime>      //日期时间
#include <QLabel>         //标签
#include <QPainter>  //画家类
#include <QPaintEvent>   //
//#include <QImage>
#include <QIcon>
#include "controlwidget.h"
#include "monitorwidget.h"
#include "wewidget.h"

#include "weather.h"
#include "tcpwidget.h"
#include <QMovie>   //动画GIF
#include <QSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void timerSLot();

    void on_buttonControl_clicked();
    void backWindow1Slot();

    void on_buttonMonitor_clicked();
    void backWindow2Slot();

    void on_buttonWeather_clicked();
    void backWindow3Slot();

    void on_buttonWe_clicked();
    void backWindow4Slot();

signals:
    void startMonitorTimer();
    void startControlTimer();

private:
    QTimer  *timer;            //定时器*/
    QMovie *myMovie;

private:
    Ui::MainWindow *ui;
    ControlWidget *control = NULL;
    MonitorWidget *monitor = NULL;
    WeWidget *we = NULL;
    Weather *weather = NULL;
    //TcpWidget *tcp = NULL;

};

#endif // MAINWINDOW_H
