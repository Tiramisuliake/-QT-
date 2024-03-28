#ifndef WEWIDGET_H
#define WEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>  //画家类
#include <QPaintEvent>   //
#include <QScrollArea>
namespace Ui {
class WeWidget;
}

class WeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeWidget(QWidget *parent = 0);
    ~WeWidget();

protected:
    void paintEvent(QPaintEvent *);


private slots:
    void on_buttonReturn_clicked();

    void on_brj_clicked();

    void on_byj_clicked();

void on_pushButton_clicked();

    void currentChanged(int index); // 确保这行是存在的
    void switchPage();

signals:
    void backWindow4();

private:
    Ui::WeWidget *ui;
    QTimer *timer;
    QString mytext;
    int curindex;

};

#endif // WEWIDGET_H
