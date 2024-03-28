#include "weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("智慧仓库门禁系统");

    this->setWindowIcon(QIcon(":/image/house.png"));
    //label
    line = new QLineEdit("常熟天气",this);
    line->setFocusPolicy(Qt::ClickFocus);  //点击后才能生成焦点   Policy 政策
    line->setFont(QFont("楷体",25,75));
    line->setStyleSheet("color:white;"
                        "background:transparent;"
                        "border: 0px;");
    backbtn = new QPushButton;
    backbtn->setText("返回");
    backbtn->setFixedSize(140,70);

    this->setMinimumWidth(1200);
    this->setMinimumHeight(800);

    qDebug()<<"JieMian2:布局";
    todayWeather =new weatherInfo(this);
    tomorrowWeather = new weatherInfo(this);
    houtianWeather = new weatherInfo(this);

    h1 = new QHBoxLayout;     //布局天气
    h1->addStretch();
    h1->addWidget(todayWeather);
    h1->addStretch();
    h1->addWidget(tomorrowWeather);
    h1->addStretch();
    h1->addWidget(houtianWeather);
    h1->addStretch();

    h2 = new QHBoxLayout;    //布局标题
    h2->addStretch();
    h2->addSpacing(200);
    h2->addWidget(line);
    h2->addStretch();


    h3 = new QHBoxLayout;    //布局返回键
    h3->addStretch();
    h3->addWidget(backbtn);
    h3->addStretch();

    v1 = new QVBoxLayout;    //垂直布局三者
    v1->addStretch();
    v1->addLayout(h2);
    v1->addSpacing(10);
    v1->addStretch();
    v1->addLayout(h1);
    v1->addStretch();
    v1->addSpacing(20);
    v1->addLayout(h3);
    v1->addStretch();

    this->setLayout(v1);  //整体布局

    //
    initNetwork();
    requestSlot();
    connect(line,SIGNAL(returnPressed()),this,SLOT(requestSlot()));

    connect(backbtn,SIGNAL(clicked(bool)),this,SLOT(backmain()));

    qDebug()<<"JieMian2:构造";

//    timer=new QTimer;
//    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
//    //timer->start(1000);

    //按钮
    this->setStyleSheet(
                 //正常状态样式
                 "QPushButton{"
                 "background-color:rgba(100,225,100,100);"//背景色（也可以设置图片）
                 "border-style:outset;"                  //边框样式（inset/outset）
                 "border-width:4px;"                     //边框宽度像素
                 "border-radius:10px;"                   //边框圆角半径像素
                 "border-color:rgba(255,255,255,30);"    //边框颜色
                 "font:bold 20px;"                       //字体，字体大小
                 "color:rgba(255,255,255,255);"                //字体颜色  (0,0,0,100)
                 "padding:6px;"                          //填衬
                 "}"                   //鼠标按下样式
                 "QPushButton:pressed{"
                 "background-color:rgba(100,255,100,200);"
                 "border-color:rgba(255,255,255,30);"
                 "border-style:inset;"
                 "color:rgba(0,0,0,100);"
                 "}"                   //鼠标悬停样式
                 "QPushButton:hover{"
                 "background-color:rgba(100,255,100,200);"
                 "border-color:rgba(255,255,255,200);"
                 "color:rgba(0,0,0,200);"
                 "}");
}

void WeatherWidget::initNetwork()
{
    manager =new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replySlot(QNetworkReply*)));
}

void WeatherWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);  //构造画家
    p.drawPixmap(rect(),QPixmap(":/image/background.jpg"));
}

void WeatherWidget::backmain()
{
    //timer->stop();
    emit backWindow3();
}

void WeatherWidget::requestSlot()
{
    QString url="http://wthrcdn.etouch.cn/weather_mini?city=";  //网址
    QString city=line->text();
    if(city.contains("天气"))
    {
        city=city.remove(city.indexOf("天气"),2);
    }
    QNetworkRequest request;  //通过QNetworkRequest类封装成一个request
    request.setUrl(QUrl(url+city));  //请求这个网址变成url  统一资源定位符（URL）是Internet上标准资源的地址
    request.setRawHeader("User-Agent","Weather 1.0");  //User-Agent设置为用户代理，
    manager->get(request);  //调用get方法，发送请求
}

void WeatherWidget::replySlot(QNetworkReply *reply)//reply信号关联的槽函数，当一次联网结束，finshed信号会发送。
{
    qDebug()<<"JieMian2:读取数据";
    //读取网络数据并存入字节数组
    QByteArray data=reply->readAll();
    if(data.isEmpty())
    {
//        QString date = "获取中...";
//        QString name = "晴";
//        QString direct = "获取中...";
//        QString power = "获取中...";
//        QString temp = "获取中...";
//        //调用接口
//        todayWeather->setInfo(date,name,temp,direct,power);
        return;
    }
    //将字节数组转化为json文档
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    //将json文档转换为json对象
    QJsonObject json =jsonDoc.object();
    //得到 json对象中的第一个键值对的值
    QJsonObject json1 = json.value("data").toObject();
    //得到json1中的第二个键值对
    QJsonArray array =json1.value("forecast").toArray();
    //array当中存储了未来5天的天气
    //今天的天气                                   //网页的内容是json文档的格式，传过来的是QByteArray
    QJsonObject today =array.at(0).toObject();   //使用json文档，用键值对解析格式
    QString date = today.value("date").toString();
    QString name = today.value("type").toString();
    QString high = today.value("high").toString();
    QString low = today.value("low").toString();
    QString direct = today.value("fengxiang").toString();
    QString power = today.value("fengli").toString();
    high =high.mid(3,high.size());
    low =low.mid(3,low.size());
    QString temp = low +"~"+ high;
    power =power.mid(9,power.indexOf("]")-9);
    //调用接口
    todayWeather->setInfo(date,name,temp,direct,power);

    today = array.at(1).toObject();
    date = today.value("date").toString();
    name = today.value("type").toString();
    high = today.value("high").toString();
    low = today.value("low").toString();
    direct =today.value("fengxiang").toString();
    power =today.value("fengli").toString();
    high = high.mid(3,6);
    low = low.mid(3,6);
    temp =low + "~" +high;
    power = power.mid(9,power.indexOf("]")-9);
    tomorrowWeather->setInfo(date,name,temp,direct,power);

    today = array.at(2).toObject();
    date = today.value("date").toString();
    name = today.value("type").toString();
    high = today.value("high").toString();
    low = today.value("low").toString();
    direct =today.value("fengxiang").toString();
    power =today.value("fengli").toString();
    high = high.mid(3,6);   //3,high.size
    low = low.mid(3,6);     //3,low.size
    temp =low + "~" +high;
    power = power.mid(9,power.indexOf("]")-9);

    houtianWeather->setInfo(date,name,temp,direct,power);
}



