#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QRgb>
#include <QDebug>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <quad_tree.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    bool m_flag;
    bool hull_flag;
    int num_amount;
    int num_cloud;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setHull(bool);
    void paintEvent(QPaintEvent *event);

private slots:

    void on_pushButtonImage_clicked();

    void on_pushButtonQuad_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
