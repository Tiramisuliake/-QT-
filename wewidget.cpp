#include "wewidget.h"
#include "ui_wewidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
WeWidget::WeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("基于QT的智能家居控制系统");
    this->setWindowIcon(QIcon(":/image/house.png"));




    ui->label->setStyleSheet("color:black");

    ui->brj->setStyleSheet(
                 //正常状态样式
                 "QPushButton{"
                 "background-color:rgba(255,255,51,100);"//背景色（也可以设置图片）
                 "border-style:outset;"                  //边框样式（inset/outset）
                 "border-width:4px;"                     //边框宽度像素
                 "border-radius:10px;"                   //边框圆角半径像素
                 "border-color:rgba(255,255,255,30);"    //边框颜色
                 "font:bold 20px;"                       //字体，字体大小
                 "color:rgba(0,0,0,100);"                //字体颜色  (0,0,0,100)
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
                 "border-color:rgba(255,255,51,200);"
                 "color:rgba(0,0,0,200);"
                 "}");

ui->byj->setStyleSheet(
        //正常状态样式
        "QPushButton{"
        "background-color:rgba(255,153,51,100);"//背景色（也可以设置图片）
        "border-style:outset;"                  //边框样式（inset/outset）
        "border-width:4px;"                     //边框宽度像素
        "border-radius:10px;"                   //边框圆角半径像素
        "border-color:rgba(255,255,255,30);"    //边框颜色
        "font:bold 20px;"                       //字体，字体大小
        "color:rgba(0,0,0,100);"                //字体颜色  (0,0,0,100)
        "padding:6px;"                          //填衬
        "}"                   //鼠标按下样式
        "QPushButton:pressed{"
        "background-color:rgba(100,255,100,200);"
        "border-color:rgba(255,255,255,30);"
        "border-style:inset;"
        "color:rgba(0,0,0,100);"
        "}"                   //鼠标悬停样式
        "QPushButton:hover{"
        "background-color:rgba(255,153,51,200);"
        "border-color:rgba(255,255,255,200);"
        "color:rgba(0,0,0,200);"
        "}");

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

    connect(ui->brj, SIGNAL(clicked()), this, SLOT(on_brj_clicked()));
    connect(ui->byj, SIGNAL(clicked()), this, SLOT(on_byj_clicked()));



}




WeWidget::~WeWidget()
{
    delete ui;
}

void WeWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);  //构造画家
    p.drawPixmap(rect(),QPixmap(":/image/module/login.jpg"));
}

void WeWidget::on_buttonReturn_clicked()
{
    emit backWindow4();
}


void WeWidget::currentChanged(int index)
{
    qDebug() << "页面发生变化: " << index;
}


void WeWidget::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->brj)
        ui->stackedWidget->setCurrentIndex(1);
    else if(button==ui->byj)
        ui->stackedWidget->setCurrentIndex(0);
    else if(button==ui->pushButton)
        ui->stackedWidget->setCurrentIndex(2);
    // 调用 currentChanged(int) 函数
       currentChanged(ui->stackedWidget->currentIndex());

       // 打印当前页面索引
       qDebug() << "当前页面索引: " << ui->stackedWidget->currentIndex();

}


void WeWidget::on_brj_clicked() {
    qDebug() << "brj 按钮被点击";
    switchPage();
}

void WeWidget::on_byj_clicked() {
    qDebug() << "byj 按钮被点击";
    switchPage();
}
void WeWidget:: on_pushButton_clicked() {
    qDebug() << "byj 按钮被点击";
    switchPage();
}
