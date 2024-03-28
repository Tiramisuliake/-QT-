#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <weatherdata.h>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMap>
#include <QMouseEvent>
#include <QNetworkAccessManager>
namespace Ui {
class Weather;
}

class Weather : public QWidget
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
 bool eventFilter(QObject* watched, QEvent* event);
private slots:
    void backmain();

    void backToMainWindow();
signals:
    void backWindow3();
protected:
    // 重写父类的方法
    void contextMenuEvent(QContextMenuEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    // 获取天气数据、解析JSON、更新UI
    void getWeatherInfo(QString cityCode);
    void parseJson(QByteArray& byteArray);
    void updateUI();

    // 绘制高低温曲线
    void paintHighCurve();
    void paintLowCurve();

private slots:
    void onReplied(QNetworkReply* reply);

    void on_btnSearch_clicked();

private:
    Ui::Weather* ui;

    // 右键退出和窗口移动
    QMenu* mExitMenu;   // 右键退出的菜单
    QAction* mExitAct;  // 退出的行为
    QPoint mOffset;     // 窗口移动时, 鼠标与窗口左上角的偏移

    // Http 请求
    QNetworkAccessManager* mNetAccessManager;

    // 今天和6天的天气
    Today mToday;
    Day mDay[6];

    // 星期和日期
    QList<QLabel*> mWeekList;
    QList<QLabel*> mDateList;

    // 天气和天气图标
    QList<QLabel*> mTypeList;
    QList<QLabel*> mTypeIconList;

    // 天气指数
    QList<QLabel*> mAqiList;

    // 风向和风力
    QList<QLabel*> mFxList;
    QList<QLabel*> mFlList;

    QMap<QString, QString> mTypeMap;
};


#endif // WEATHER_H
