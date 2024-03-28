#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QPainter>  //画家类
#include <QPaintEvent>   //
#include <QIcon>
#include <QTimer>
#include <QString>
#include "tcpwidget.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtMath>
#include <QMovie>


namespace Ui {
class MonitorWidget;
}

class MonitorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorWidget(QWidget *parent = 0);
    ~MonitorWidget();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_buttonReturn_clicked();
    void displaydata();
public slots:
    void startTimerSlot();

signals:
    void backWindow2();
private:
    Ui::MonitorWidget *ui;
    QTimer *myTimer;  //定时器对象
    QString recData;
    QString temp_int;
    QString temp_deci;
    QString humi_int;
    QString humi_deci;
    QString temp;
    QString humi;
    QString body;
    QString smoke;
 QMovie *myMovie;

    QtCharts::QChart *chart;
       QtCharts::QLineSeries *temperatureSeries;
       QtCharts::QChartView *chartView;


};


#endif // MONITORWIDGET_H
