#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QtMath>
#include <QDebug>
#include <QFile>
#include <QImage>

class quad_tree : public QObject
{
    Q_OBJECT

public:
    explicit quad_tree(QObject *parent = nullptr);
    static void generate_quad_tree_line_points(QPoint left_top, QPoint right_down, const QImage image);

signals:

};

#endif // QUAD_TREE_H
