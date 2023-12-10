#include "quad_tree.h"

quad_tree::quad_tree(QObject *parent) : QObject(parent)
{

}

/*!
 * \brief quad_tree::generate_quad_tree_line_points recursive method which creates quad tree
 * \param left_top upper left position of the image part
 * \param right_down bottom right position of the image part
 * \param image the whole image to write quad tree lines
 */
void quad_tree::generate_quad_tree_line_points(QPoint left_top, QPoint right_down, const QImage image)
{
    // bottom of recursion - method ends when the size of the rectangle is less than 2
    if (qFabs(left_top.x() - right_down.x()) < 2 || qFabs(left_top.y() - right_down.y()) < 2)
        return;

    // counts black and white points
    int white = 0, black = 0;
    for (int row = left_top.x(); row < right_down.x(); row++)
    {
        for (int col = left_top.y(); col < right_down.y(); col++)
        {
            QRgb pix_color = image.pixel(row, col);
            if (qRed(pix_color) == 0 && qGreen(pix_color) == 0 && qBlue(pix_color) == 0)
            {
                black++;
                continue;
            }
            if (qRed(pix_color) == 255 && qGreen(pix_color) == 255 && qBlue(pix_color) == 255)
            {
                white++;
                continue;
            }
        }
    }

    // if there are only white or black points quits
    if (white < 1 || black < 1) return;
    qDebug() << "White points: " << white;
    qDebug() << "Black points: " << black;
    qDebug() << white+black;

    // stores QPoint positions of the line to write
    QVector<QPoint> quad_tree_line_points;

    quad_tree_line_points.push_back(left_top);
    quad_tree_line_points.push_back(QPoint(left_top.x(), right_down.y()));
    quad_tree_line_points.push_back(left_top);
    quad_tree_line_points.push_back(QPoint(right_down.x(), left_top.y()));
    quad_tree_line_points.push_back(right_down);
    quad_tree_line_points.push_back(QPoint(right_down.x(), left_top.y()));
    quad_tree_line_points.push_back(right_down);
    quad_tree_line_points.push_back(QPoint(left_top.x(), right_down.y()));

    // finds the medium on the image
    QPoint medium;
    if (right_down.x() >= left_top.x())
    {
        medium.setX((right_down.x()-left_top.x())/2+left_top.x());
        medium.setY((right_down.y()-left_top.y())/2+left_top.y());
    }
    else
    {
        qDebug() << "ERROR";
    }

    // write QPoints of the line
    QFile file("quad_tree_points.txt");
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        for (auto elem : quad_tree_line_points)
        {
            stream << elem.x() << endl;
            stream << elem.y() << endl;
        }
    }

    // invoke 4 recursive methods to get quad tree
    generate_quad_tree_line_points(left_top, medium, image);
    generate_quad_tree_line_points(QPoint(medium.x(), left_top.y()), QPoint(right_down.x(), medium.y()), image);
    generate_quad_tree_line_points(QPoint(left_top.x(), medium.y()), QPoint(medium.x(), right_down.y()), image);
    generate_quad_tree_line_points(medium, right_down, image);
}
