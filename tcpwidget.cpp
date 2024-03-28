#include "tcpwidget.h"
#include <QDebug>
#include <QHostAddress>
#include <QMutex>

TcpWidget::TcpWidget(QWidget *parent) : QWidget(parent)
{
    tcpSocket = NULL;
    //分配空间，指定父对象
    tcpSocket = new QTcpSocket(this);

    //如果成功和对方建立好连接，通信套接字会自动触发connected()信号
    connect(tcpSocket,&QTcpSocket::connected,
            [=]()
            {
                qDebug() << "成功和服务器建立好连接";
                emit con();
            }
            );
    //读数据
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                qDebug()<<"准备好读数据";
                //获取对方发送的内容
            }
            );

}

TcpWidget *TcpWidget::tcpData()   //单例模式
{
//    static TcpWidget tcp;
//    return &tcp;
    static QMutex mutex;     //需要时才动态初始化，保证了线程安全，又防止了内存泄漏。
    static QScopedPointer<TcpWidget> inst;
    if(Q_UNLIKELY(!inst))
    {
        mutex.lock();
        if(!inst)
        {
            inst.reset(new TcpWidget);
        }
        mutex.unlock();
    }
    return inst.data();
}

void TcpWidget::writeData(QString str)
{
    tcpSocket->write(str.toUtf8().data());
    //qDebug() <<"写成功";
}

void TcpWidget::connectWifi()
{
    QString ip = "192.168.66.166";  //我要连的WIFI IP地址
    qint16 port = 8080;  //我要连的端口号
    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);  //将ip转为QHostAddress这个默认类型
}

QString TcpWidget::readData()
{
    QByteArray array = tcpSocket->readAll();   //读全部
    qDebug() << array;
    QString str = array;
    return str;
}





