#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

#include <QtQml>
#include "issobject.h"
#include "isservice.h"
#include "ouroborosservice.h"

#include "networkservice.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("ArpegiusWhooves");
    app.setApplicationName("ISS");


    qRegisterMetaType<NetworkServiceWork*>();
    qmlRegisterType<ISService>("ISS",1,0,"ISService");
    qmlRegisterType<ISSObject>("ISS",1,0,"ISSObject");
    qmlRegisterType<OuroborosService>("ISS",1,0,"OuroborosService");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/ISS/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
