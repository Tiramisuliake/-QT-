#include "controlwidget.h"
#include "ui_controlwidget.h"


ControlWidget::ControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("基于QT的智能家居控制系统");
    this->setWindowIcon(QIcon(":/image/module/SmartHome.ico"));
     setFixedSize(width(), height());         // 固定窗口大小

    //定时器     //查看状态
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));


    initForm();
    timerSlot();
    on_buttonControl_clicked();


     ui->labelName->setStyleSheet("background:transparent;");   //标题
    //返回键
    ui->buttonReturn->setStyleSheet(
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

    ui->buttonControl->setStyleSheet(
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

    isLedOn = false;  // 初始化灯的状态为关闭
    isFanOn = false;  // 初始化Fan的状态为关闭
    isBeepOn = false;  // 初始化Beep的状态为关闭
    controlflag = false;
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::startTimerSlot()
{
    timer->start(1000);
}

void ControlWidget::timerSlot() {
    TcpWidget::tcpData()->writeData("CMD_READ_STATUS_END");
    recData = TcpWidget::tcpData()->readData();

    //CMD_LED1_%d_ENDLED1_BEEP_%d_ENDBEEP_FAN_%d_ENDBEEP_END
    if (recData.section('_', 2, 2).toInt() == 1) {
        // 如果 LED 是打开的状态
        ui->buttonLED->setStyleSheet(m_stylebutOff);
    } else {
        // 如果 LED 是关闭的状态
        ui->buttonLED->setStyleSheet(m_stylebutOn);
    }

    if (recData.section('_', 5, 5).toInt() == 1) {
        // 如果 Beep 是打开的状态
        ui->buttonBeep->setStyleSheet(m_stylebutOn);
    } else {
        // 如果 Beep 是关闭的状态
        ui->buttonBeep->setStyleSheet(m_stylebutOff);
    }

    if (recData.section('_', 8, 8).toInt() == 1) {
        // 如果 Fan 是打开的状态
        ui->buttonFan->setStyleSheet(m_stylebutOff);
    } else {
        // 如果 Fan 是关闭的状态
        ui->buttonFan->setStyleSheet(m_stylebutOn);
    }
}


void ControlWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);  //构造画家
    p.drawPixmap(rect(),QPixmap(":/image/module/login.jpg"));
}

void ControlWidget::on_buttonReturn_clicked()
{
    if(timer->isActive())
    timer->stop();
    emit backWindow1();
}

void ControlWidget::initForm() {

    m_styleLedOn = "QLabel{border-image:url(:/image/module/light_on.png);border:0px;width:100px; height:100px;}";
    m_styleLedOff = "QLabel{border-image:url(:/image/module/light_off.png);border:0px;width:100px; height:100px;}";



    m_styleFanOn = "QLabel{border-image:url(:/image/module/fan_on.png);border:0px;width:100px; height:100px;}";
    m_styleFanOff = "QLabel{border-image:url(:/image/module/fan_off.png);border:0px;width:100px; height:100px;}";


    m_styleBeepOn = "QLabel{border-image:url(:/image/module/beep_on.svg);border:0px;width:100px; height:100px;}";
    m_styleBeepOff = "QLabel{border-image:url(:/image/module/beep_off.svg);border:0px;width:100px; height:100px;}";

     m_stylebutOn = "QPushButton{border-image:url(:/image/switch/btncheckon.png);width:100px; height:50px;}"
                    "QPushButton:checked{border-image:url(:/image/switch/btncheckon.png);width:100px; height:50px;}";
    m_stylebutOff = "QPushButton{border-image:url(:/image/switch/btncheckoff.png);width:100px; height:50px;}"
                    "QPushButton:checked{border-image:url(:/image/switch/btncheckoff.png);width:100px; height:50px;}";

    myMovie1 = new QMovie(":/image/module/shoudong.gif");
    //设置动画
    myMovie2 = new QMovie(":/image/module/zidongmoshi.gif");

    ui->label_light_main->setStyleSheet(m_styleLedOff);
    ui->label_fan_main->setStyleSheet(m_styleFanOff);
    ui->label_beep_main->setStyleSheet(m_styleBeepOff);
    ui->buttonLED->setStyleSheet(m_stylebutOff);

    qDebug() << "Style LED On (initForm): " << m_styleLedOn;
    qDebug() << "Style LED Off (initForm): " << m_styleLedOff;

}
void ControlWidget::init() {
}

void ControlWidget::initConnect() {
}



void ControlWidget::on_buttonLED_clicked() {
    qDebug() << "Button clicked"; // 输出调试信息

    // 获取TcpData实例
    auto tcpData = TcpWidget::tcpData();

    qDebug() << "Current Style LED On: " << m_styleLedOn;
       qDebug() << "Current Style LED Off: " << m_styleLedOff;

    if (!isLedOn) {
        // 如果灯是关闭状态
        ui->buttonLED->setStyleSheet(m_stylebutOn);
        ui->label_light_main->setStyleSheet(m_styleLedOn);
        tcpData->writeData("CMD_LED_1");   //开灯
    } else {
        // 如果灯是开启状态
        ui->buttonLED->setStyleSheet(m_stylebutOff);
        ui->label_light_main->setStyleSheet(m_styleLedOff);
        tcpData->writeData("CMD_LED_0");  //关灯
    }

    // 切换灯的状态
    isLedOn = !isLedOn;
    qDebug() << "Label style: " << ui->label_light_main->styleSheet(); // 输出标签样式
    // 输出样式表
      qDebug() << "Style LED On: " << m_styleLedOn;
      qDebug() << "Style LED Off: " << m_styleLedOff;
      qDebug() << "Button address: " << ui->buttonLED;
      qDebug() << "Label address: " << ui->label_light_main;

}



        void ControlWidget::on_buttonBeep_clicked(){
            qDebug() << "Button clicked"; // 输出调试信息

            // 获取TcpData实例
            auto tcpData = TcpWidget::tcpData();

            if (!isBeepOn) {

                // 如果Beep是关闭状态
                ui->buttonBeep->setStyleSheet(m_stylebutOn);
                ui->label_beep_main->setStyleSheet(m_styleBeepOn);
                tcpData->writeData("CMD_BEEP_1");   //开灯
            } else {

                // 如果Beep是开启状态
                ui->buttonBeep->setStyleSheet(m_stylebutOff);
                ui->label_beep_main->setStyleSheet(m_styleBeepOff);
                tcpData->writeData("CMD_BEEP_0");  //关灯
            }

            // 切换灯的状态
             isBeepOn = ! isBeepOn;
        }



        void ControlWidget::on_buttonFan_clicked(){
            qDebug() << "Button clicked"; // 输出调试信息

            // 获取TcpData实例
            auto tcpData = TcpWidget::tcpData();

            if (!isFanOn) {
                // 如果Fan是关闭状态
                ui->buttonFan->setStyleSheet(m_stylebutOn);
                ui->label_fan_main->setStyleSheet(m_styleFanOn);
                tcpData->writeData("CMD_FAN_1");   //开灯
            } else {
                // 如果Fan是开启状态
                ui->buttonFan->setStyleSheet(m_stylebutOff);
                ui->label_fan_main->setStyleSheet(m_styleFanOff);
                tcpData->writeData("CMD_FAN_0");  //关灯
            }

            // 切换灯的状态
             isFanOn = ! isFanOn;
        }

void ControlWidget::on_buttonControl_clicked()
{
    if(controlflag)
    {
        ui->label->setMovie(myMovie2);
        //设置动画大小
        ui->label->setScaledContents(true);
        //启动动画
        myMovie2->start();

        ui->buttonControl->setText("自动模式中");
        timer->start(1000);
        controlflag = false;
    }
    else
    {

        ui->label->setMovie(myMovie1);
        //设置动画大小
        ui->label->setScaledContents(true);
        //启动动画
        myMovie1->start();

        if(timer->isActive())
        timer->stop();
        //收不到暂时
        ui->buttonControl->setText("手动模式中");
        controlflag = true;
    }


}
