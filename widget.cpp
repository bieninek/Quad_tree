#include "widget.h"
#include "ui_widget.h"
#include "graham_algorithm.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    m_flag = false;
    hull_flag = false;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

/*!
 * \brief Widget::on_pushButtonImage_clicked works to generate convex hulls
 */
void Widget::on_pushButtonImage_clicked()
{
    // saves number of polygons
    int amount = ui->lineEditNumPoint->text().toInt();
    qDebug() << "points number: " << amount;

    grahamAlgorithm::clearTextFile("points.txt");
    grahamAlgorithm::clearTextFile("quad_tree_points.txt");

    m_flag = true;
    this->num_amount = amount;
    amount = ui->lineEditNumCloud->text().toInt();
    this->num_cloud = amount;
    this->num_amount *= this->num_cloud;
}

/*!
 * \brief Widget::paintEvent usual paint event
 */
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    // convex hull part
    if (m_flag)
    {
        grahamAlgorithm obj;
        int temp_x, temp_y;

        // creates cloud of points
        while (num_amount > 0)
        {
            temp_x = rand() % 540 + 50;
            temp_y = rand() % 540 + 50;
            obj.addPoint("points.txt", temp_x, temp_y);
            --num_amount;
        }

        // new pix map - set to have white background
        QPixmap *pix = new QPixmap(600,600);
        QPainter *paint_image = new QPainter(pix);
        pix->fill();

        // creates some conex hulls
        for (int i = 0; i < num_cloud; i++)
        {
            grahamAlgorithm::clearTextFile("hull_pt.txt");
            obj.createHull(i, num_cloud);

            QVector<QPoint> pts;
            QFile file("hull_pt.txt");
            if(!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(0, "error", file.errorString());
            }

            QTextStream in(&file);
            while(!in.atEnd()) {
                int pt_x = in.readLine().toInt();
                int pt_y = in.readLine().toInt();
                pts.push_back(QPoint(pt_x, pt_y));
            }
            file.close();

            // convert to array...
            QPoint pts_arr[pts.size()];
            for (int i=0; i < pts.size(); i++)
                pts_arr[i] = pts[i];

            // fills polygons to be black
            paint_image->setBrush(Qt::black);
            paint_image->setPen(Qt::black);

            paint_image->drawConvexPolygon(pts_arr, pts.size());
        }

        QFile image_file("convex_hull.png");
        image_file.open(QIODevice::WriteOnly);

        pix->save(&image_file, "PNG");
        image_file.close();
        m_flag = false;
    }

    // quad tree part
    if (hull_flag)
    {
        // new pix map filled to be white
        QPixmap *pix = new QPixmap(600,600);
        QPainter *paint_image = new QPainter(pix);
        pix->fill();

        QFile image_file("quadTree.png");
        image_file.open(QIODevice::WriteOnly);

        // draws image get as input
        QImage convex_hull_image("convex_hull.png");
        paint_image->drawImage(0,0,convex_hull_image);

        // creates .txt file with quad tree points
        quad_tree::generate_quad_tree_line_points(QPoint(0, 0), QPoint(589, 589), convex_hull_image);


        // open from file
        QVector<QPoint> line_pts;
        QFile file3("quad_tree_points.txt");
        if(!file3.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file3.errorString());
        }

        // copy QPoints to QVector based on .txt file
        QTextStream in3(&file3);
        while(!in3.atEnd()) {
            int pt_x = in3.readLine().toInt();
            int pt_y = in3.readLine().toInt();
            line_pts.push_back(QPoint(pt_x, pt_y));
        }
        file3.close();

        // set pen to proper display format
        paint_image->setPen(Qt::red);

        // draw lines
        for(QVector<QPoint>::Iterator it = line_pts.begin(); it != line_pts.end(); ++it)
        {
            QPoint *p1= new QPoint(it->x(), it->y());
            ++it;
            QPoint *p2= new QPoint(it->x(), it->y());
            painter.drawLine(*p1, *p2);
            paint_image->drawLine(*p1, *p2);
        }

        // saves file
        pix->save(&image_file, "PNG");
        image_file.close();

        // prevents from executing again
        hull_flag = false;
    }

}

/*!
 * \brief Widget::on_pushButtonQuad_clicked creates quad tree lines on image
 */
void Widget::on_pushButtonQuad_clicked()
{
    qDebug() << "clicked button quad";
    hull_flag = true;
}

