#ifndef TCPWIDGET_H
#define TCPWIDGET_H

#include <QWidget>
#include <QTcpSocket>  //通信套接字


class TcpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TcpWidget(QWidget *parent = nullptr);
    static TcpWidget* tcpData();  //需要有一个文件对象

signals:
    void con();

public slots:
    void writeData(QString str);
    void connectWifi();
    QString readData();

private:
    QTcpSocket *tcpSocket;
};

#endif // TCPWIDGET_H
