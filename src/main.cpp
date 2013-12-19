#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QtQml>

#include "isservice.h"
#include "ouroborosservice.h"



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ISService>("ISS",1,0,"ISService");
    qmlRegisterType<OuroborosService>("ISS",1,0,"OuroborosService");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/ISS/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
