#include "monitorwidget.h"
#include "ui_monitorwidget.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

MonitorWidget::MonitorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("基于QT的智能家居控制系统");
    this->setWindowIcon(QIcon(":/image/module/SmartHome.ico"));
    myMovie = new QMovie(":/image/module/shuj.gif");
    //设置动画
    ui->label->setMovie(myMovie);
    //设置动画大小
    ui->label->setScaledContents(true);
    //启动动画
    myMovie->start();

    //返回键  字体颜色
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

    ui->labelName->setStyleSheet("color: rgb(0, 0, 0);");

    ui->labelBody->setStyleSheet("QLabel{"
                                "background-color:rgba(250,128,114,100);"//背景色（也可以设置图片）
                                "border-style:outset;"                  //边框样式（inset/outset）
                                "border-width:4px;"                     //边框宽度像素
                                "border-radius:20px;"                   //边框圆角半径像素
                                "border-color:rgba(255,255,255,30);"    //边框颜色
                                "font:bold 20px;"                       //字体，字体大小
                                "color:rgba(255,255,255,255);"                //字体颜色  (0,0,0,100)
                                "padding:6px;"                          //填衬
                                "}");
    ui->labelHum->setStyleSheet("QLabel{"
                                "background-color:rgba(250,128,114,100);"//背景色（也可以设置图片）
                                "border-style:outset;"                  //边框样式（inset/outset）
                                "border-width:4px;"                     //边框宽度像素
                                "border-radius:20px;"                   //边框圆角半径像素
                                "border-color:rgba(255,255,255,30);"    //边框颜色
                                "font:bold 20px;"                       //字体，字体大小
                                "color:rgba(255,255,255,255);"                //字体颜色  (0,0,0,100)
                                "padding:6px;"                          //填衬
                                "}");
    ui->labelSmoke->setStyleSheet("QLabel{"
                                "background-color:rgba(250,128,114,100);"//背景色（也可以设置图片）
                                "border-style:outset;"                  //边框样式（inset/outset）
                                "border-width:4px;"                     //边框宽度像素
                                "border-radius:20px;"                   //边框圆角半径像素
                                "border-color:rgba(255,255,255,30);"    //边框颜色
                                "font:bold 20px;"                       //字体，字体大小
                                "color:rgba(255,255,255,255);"                //字体颜色  (0,0,0,100)
                                "padding:6px;"                          //填衬
                                "}");
    ui->labelTem->setStyleSheet("QLabel{"
                                "background-color:rgba(250,128,114,100);"//背景色（也可以设置图片）
                                "border-style:outset;"                  //边框样式（inset/outset）
                                "border-width:4px;"                     //边框宽度像素
                                "border-radius:20px;"                   //边框圆角半径像素
                                "border-color:rgba(255,255,255,30);"    //边框颜色
                                "font:bold 20px;"                       //字体，字体大小
                                "color:rgba(255,255,255,255);"                //字体颜色  (0,0,0,100)
                                "padding:6px;"                          //填衬
                                "}");

    myTimer = new QTimer(this);
    connect(myTimer,&QTimer::timeout,
            [=]()
            {
                TcpWidget::tcpData()->writeData("CMD_READ_SENSOR_END");
                recData = TcpWidget::tcpData()->readData();
                displaydata();
            }
            );




}

MonitorWidget::~MonitorWidget()
{
    delete ui;
}

void MonitorWidget::startTimerSlot()
{
    myTimer->start(1000);
}

void MonitorWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);  //构造画家
    p.drawPixmap(rect(),QPixmap(":/image/module/login.jpg"));
}

void MonitorWidget::on_buttonReturn_clicked()
{
    if(myTimer->isActive())
    myTimer->stop();
    emit backWindow2();
}

void MonitorWidget::displaydata()
{
    //CMD_DHT11_%d.%d_%d.%d%%_ENDDHT11_SR501_%d_ENDSR501_MQ2_%.2f ppm_ENDMQ2_END
    //温度整数 温度小数  湿度整数 湿度小数 人体红外 烟雾

    if(recData.section('_',6,6).toInt() == 0)
    {
        ui->labelBodydata->setText("无人");
    }
    else
         ui->labelBodydata->setText("有人");

    ui->labelTemdata->setText(recData.mid(10,4));//把数据放进对应的槽第10段4个字符

    ui->labelHumdata->setText(recData.mid(15,5));

    ui->labelSmokedata->setText(recData.section('_',9,9));



}


