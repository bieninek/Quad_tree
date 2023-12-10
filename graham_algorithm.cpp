#include "graham_algorithm.h"

grahamAlgorithm::grahamAlgorithm(QObject *parent) : QObject(parent)
{

}

/*!
 * \brief grahamAlgorithm::clearTextFile deletes a file with the 'filename' filename
 * \param filename name od the file to delete
 */
void grahamAlgorithm::clearTextFile(QString filename)
{
    QFile file (filename);
        file.remove();
}

/*!
 * \brief grahamAlgorithm::addPoint method opens the file with a 'filename' name
 * and adds information with QPoint type
 * \param filename name of the file
 * \param a 'x' of the point
 * \param b 'y' of the point
 */
void grahamAlgorithm::addPoint(QString filename, int a, int b)
{
    QFile file(filename);
    if (file.open(QIODevice::Append)) {
        QTextStream stream(&file);
        stream << a << endl;
        stream << b << endl;
    }
}

/*!
 * \brief grahamAlgorithm::createHull method uses many mentioned methods - writes
 * QPoints to the text file which are the part of the hull.
 * All the parameters are used because of creating many hulls in one file.
 * \param iteration counts how many times the method was invoked
 * \param num_part number of all invokes of the function
 */
void grahamAlgorithm::createHull(int iteration, int num_part)
{
    // read from file
    QFile file("points.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    // choose only appropriate points
    points.clear();
    QTextStream in(&file);
    while(!in.atEnd()) {
        int pt_x = in.readLine().toInt();
        int pt_y = in.readLine().toInt();
        if (pt_x > iteration*(600/num_part)+0 && pt_x < iteration*(600/num_part) + 600/num_part -0 )
            points.push_back(QPoint(pt_x, pt_y));
    }
    file.close();

    qDebug() << points;


   // the bottom point
   int ymin = points.at(0).y(), min = 0;
   for (int i{1}; i < points.size(); i++)
   {
     int y = points.at(i).y();

     // bottomest or the most left
     if ((y < ymin) || (ymin == y && points.at(i).x() < points.at(min).x()))
        ymin = points.at(i).y(), min = i;
   }
   swap(const_cast<QPoint&>(points.at(0)), const_cast<QPoint&>(points.at(min)));


   // my bubble sort
   this->p0 = points.at(0);
   for (int i{0}; i < points.size() - 1; i++)
       for (int j{0}; j < points.size() - i - 1; j++)
           if (sortRule(points.at(j), points.at(j + 1)))
               swap(const_cast<QPoint&>(points.at(j)), const_cast<QPoint&>(points.at(j + 1)));

   int m{1};
   for (int i{1}; i < points.size(); i++)
   {
       while (i < points.size()-1 && orientation(this->p0, points.at(i), points.at(i + 1)) == 0)
          i++;

       const_cast<QPoint&>(points.at(m)) = points.at(i);
       m++;
   }

   // exception?
   if (m < 3) return;

   QStack<QPoint> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i{3}; i < m; i++)
   {
      while (S.size()>1 && orientation(nextToTop(S), S.top(), points.at(i)) != 2)
        S.pop();
      S.push(points.at(i));
   }

   // take all the points from stack
   while (!S.empty())
   {
       QPoint p = S.top();
       qDebug() << p;
        addPoint("hull_pt.txt", p.x(), p.y());
       S.pop();
   }
}

/*!
 * \brief grahamAlgorithm::nextToTop finds next to top on stack
 * \param S stack
 * \return QPoint next to top on stack
 */
QPoint grahamAlgorithm::nextToTop(QStack<QPoint> &S)
{
    QPoint p = S.top();
    S.pop();
    QPoint res = S.top();
    S.push(p);
    return res;
}

/*!
 * \brief grahamAlgorithm::dist calculates distance between two QPoints
 * \param p1 QPoint to compare
 * \param p2 QPoint to compare
 * \return integer distance between QPoints
 */
int grahamAlgorithm::dist(QPoint p1, QPoint p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
            (p1.y() - p2.y())*(p1.y() - p2.y());
}

/*!
 * \brief grahamAlgorithm::orientation checks position of the 3 QPoints
 * \param p QPoint to compare
 * \param q QPoint to compare
 * \param r QPoint to compare
 * \return int value depending on the position
 */
int grahamAlgorithm::orientation(QPoint p, QPoint q, QPoint r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
                  (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

/*!
 * \brief grahamAlgorithm::sortRule sorting rule based which replaced lambda expression in sorting
 * \param p1 QPoint to compare
 * \param p2 QPoint to compare
 * \return boolean value used in bubble sort in createHull
 */
bool grahamAlgorithm::sortRule(QPoint p1, QPoint p2)
{
   // Find orientation
   int o = orientation(p0, p1, p2);
   if (o == 0)
     return (dist(p0, p2) >= dist(p0, p1))? false : true;

   return (o == 2)? false : true;
}

/*!
 * \brief grahamAlgorithm::swap simple swap method
 * \param p1 QPoint to swap
 * \param p2 QPoint to swap
 */
void grahamAlgorithm::swap(QPoint &p1, QPoint &p2)
{
    QPoint temp = p1;
    p1 = p2;
    p2 = temp;
}


