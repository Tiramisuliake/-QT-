#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
//#include <QTimer>
#include <QPainter>  //画家类
#include <QPaintEvent>   //
#include <QIcon>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "weatherinfo.h"

class WeatherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    void initNetwork();

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void requestSlot();
    void replySlot(QNetworkReply *reply);
    //void startWidget2TimerSlot();


private slots:
    void backmain();
signals:
    void backWindow3();

private:
    QLineEdit  *line;
    weatherInfo *todayWeather;
    weatherInfo *tomorrowWeather;
    weatherInfo *houtianWeather;
    QHBoxLayout *h1;
    QHBoxLayout *h2;
    QHBoxLayout *h3;
    QVBoxLayout *v1;
    QVBoxLayout *v2;
    QNetworkAccessManager *manager;
    QPushButton *backbtn;
};

#endif // WEATHERWIDGET_H
