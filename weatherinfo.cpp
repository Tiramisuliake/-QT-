#include "weatherinfo.h"

weatherInfo::weatherInfo(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(270);
    widget=new QWidget(this);
    dateLable=new QLabel("获取中...",widget);
    iconLable=new QLabel(widget);
    nameLable=new QLabel("获取中...",widget);
    temperatureLable=new QLabel("获取中...",widget);
    directioLabel=new QLabel("获取中...",widget);
    windyPowerLabel=new QLabel("获取中...",widget);
    //居中
    dateLable->setAlignment(Qt::AlignCenter);
    nameLable->setAlignment(Qt::AlignCenter);
    temperatureLable->setAlignment(Qt::AlignCenter);
    directioLabel->setAlignment(Qt::AlignCenter);
    windyPowerLabel->setAlignment(Qt::AlignCenter);
    iconLable->setFixedSize(250,250);
    QPixmap map(":/icons/sun.png");
    iconLable->setPixmap(map.scaled(iconLable->size()));
    //布局
    v=new QVBoxLayout;
    v->addWidget(dateLable);
    v->addWidget(iconLable);
    v->addWidget(nameLable);
    v->addWidget(temperatureLable);
    v->addWidget(directioLabel);
    v->addWidget(windyPowerLabel);
    this->setLayout(v);
    //样式表
    widget->setStyleSheet("background:rgba(255,255,255,100);border-radius:15px");
    this->setStyleSheet("QLabel{color: white;font:25px '楷体';}");
}

weatherInfo::~weatherInfo()
{
    delete widget;delete dateLable;
    delete iconLable;delete nameLable;
    delete temperatureLable;
    delete directioLabel;
    delete windyPowerLabel;
    delete v;
}

//显示 天气信息
void weatherInfo::setInfo(QString date, QString name, QString temp, QString direct, QString power)
{
    dateLable->setText(date);
    QString icon=getIcon(name);
    QPixmap map(icon);
    iconLable->setPixmap(map.scaled(iconLable->size()));
    nameLable->setText(name);
    temperatureLable->setText(temp);
    directioLabel->setText(direct);
    windyPowerLabel->setText(power);
}
//获取name对应的图片
QString weatherInfo::getIcon(QString name)
{
    if(name=="晴")
    {
        return ":/icons/sun.png";
    }else if(name =="多云")
    {
        return ":/icons/sun&cloudy.png";
    }else if(name=="阴")
    {
        return ":/icons/cloudy.png";
    }else if(name.contains("阵雨"))
    {
        return ":/icons/sun&rain.png";
    }else if(name=="小雨"||name=="中雨")
    {
        return ":/icons/smallrain.png";
    }else if(name=="大雨"||name.contains("暴雨"))
    {
        return ":/icons/largerain.png";
    }else if(name.contains("雪"))
    {
        return ":/icons/snow.png";
    }else{
        return ":/icons/sun&cloudy.png";
    }

}

void weatherInfo::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    widget->resize(this->size());
}
