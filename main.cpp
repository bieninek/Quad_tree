#include "widget.h"
#include "graham_algorithm.h"

#include <QApplication>

/*!
 * \brief qMain entry point of the project
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
