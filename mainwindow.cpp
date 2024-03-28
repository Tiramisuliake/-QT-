#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.名称和图标
    this->setWindowTitle("基于QT的智能家居控制系统");
    this->setWindowIcon(QIcon(":/image/module/SmartHome.ico"));

    //设置时间
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&MainWindow::timerSLot);
    timer->start(1000);

    //设置按钮、标签、字体
    ui->labelTime->setStyleSheet("background:transparent;");//背景透明
    //ui->labelControl->setStyleSheet("background:transparent;");
    ui->labelName->setStyleSheet("background:transparent;");
    //ui->labelMonitor->setStyleSheet("background:transparent;");
    ui->labelPicture->setStyleSheet("background:transparent;");

    QPixmap control(":/image/switch/kongzhi.png");
    ui->buttonControl->setIconSize(QSize(80,80));
    ui->buttonControl->setIcon(control);  //小图片

    QPixmap monitor(":/image/switch/jiance.png");
    ui->buttonMonitor->setIcon(monitor);
    ui->buttonMonitor->setIconSize(QSize(80,80));

    QPixmap we(":/image/key.png");
    ui->buttonWe->setIconSize(QSize(80,80));
    ui->buttonWe->setIcon(we);

    QPixmap weather(":/image/switch/tqyb.png");
    ui->buttonWeather->setIconSize(QSize(80,80));
    ui->buttonWeather->setIcon(weather);

    //设置字体
    ui->labelTime->setStyleSheet("color:rgb(0,0,0);");
    ui->labelName->setStyleSheet("color:rgb(0,0,0);");
/*
    ui->labelMonitor->setFont(QFont("楷体",13,75));
    ui->labelMonitor->setStyleSheet("color:black");
    ui->labelControl->setFont(QFont("楷体",13,75));
    ui->labelControl->setStyleSheet("color:black");
*/

    // 创建 QMovie 对象并设置给 label 控件
    myMovie = new QMovie(":/image/switch/long2.gif");
    ui->labelPicture->setMovie(myMovie);

    // 启动动画
    myMovie->start();

    // 获取动画的原始大小
    QSize originalSize = myMovie->scaledSize();

    // 设置新的大小
    int newWidth = 200; // 新的宽度
    int newHeight = 200; // 新的高度

    // 设置新的大小并调整动画大小
    myMovie->setScaledSize(QSize(newWidth, newHeight));

    // 更新标签控件的大小以适应新的动画大小
    ui->labelPicture->setFixedSize(newWidth, newHeight);

   this->setStyleSheet(
                //正常状态样式
                "QPushButton{"
                "background-color:rgba(50,128,250,200);"//背景色（也可以设置图片）
                "border-style:outset;"                  //边框样式（inset/outset）
                "border-width:4px;"                     //边框宽度像素
                "border-radius:10px;"                   //边框圆角半径像素
                "border-color:rgba(255,255,255,30);"    //边框颜色
                "font:bold 20px;"                       //字体，字体大小
                "color:rgba(0,0,0,200);"                //字体颜色  (0,0,0,100)
                "padding:6px;"                          //填衬
                "}"                   //鼠标按下样式
                "QPushButton:pressed{"
                "background-color:rgba(100,255,100,200);"
                "border-color:rgba(255,255,255,30);"
                "border-style:inset;"
                "color:rgba(0,0,0,100);"
                "}"                   //鼠标悬停样式
                "QPushButton:hover{"
                "background-color:rgba(255,255,153,200);"
                "border-color:rgba(255,255,255,200);"
                "color:rgba(0,0,0,200);"
                "}");

    this->setMinimumHeight(700);
    this->setMinimumWidth(1000);

    TcpWidget::tcpData()->connectWifi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerSLot()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->labelTime->setText(str);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);  //构造画家
    p.drawPixmap(rect(),QPixmap(":/image/module/login.jpg"));
}

void MainWindow::on_buttonControl_clicked()    //控制设备界面
{
    if(control == NULL)
    {
        control = new ControlWidget;
        connect(control,&ControlWidget::backWindow1,this,&MainWindow::backWindow1Slot);
        connect(this,&MainWindow::startControlTimer,control,&ControlWidget::startTimerSlot);
    }
    this->hide();
    emit startControlTimer();
    control->show();
}
void MainWindow::backWindow1Slot()
{
    this->show();
    control->hide();
}

void MainWindow::on_buttonMonitor_clicked()    //监测界面
{
    if(monitor == NULL)
    {

        monitor = new MonitorWidget;
        connect(monitor,&MonitorWidget::backWindow2,this,&MainWindow::backWindow2Slot);
        connect(this,&MainWindow::startMonitorTimer,monitor,&MonitorWidget::startTimerSlot);
    }
    emit startMonitorTimer();
    this->hide();
    monitor->show();
}
void MainWindow::backWindow2Slot()
{
    this->show();
    monitor->hide();
}

void MainWindow::on_buttonWeather_clicked()   //天气查询
{
    if(weather == NULL)
    {
        weather = new Weather;
        connect(weather,&Weather::backWindow3,this,&MainWindow::backWindow3Slot);
    }
    this->hide();
    weather->show();
}
void MainWindow::backWindow3Slot()
{
    this->show();
    weather->hide();
}

void MainWindow::on_buttonWe_clicked()    //系统教程
{
    if(we == NULL)
    {
        we = new WeWidget;
        connect(we,&WeWidget::backWindow4,this,&MainWindow::backWindow4Slot);
    }
    this->hide();
    we->show();
}
void MainWindow::backWindow4Slot()
{
    this->show();
    we->hide();
}
