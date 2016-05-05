#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "colorpicture.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorPicture>("Pictures", 1, 0, "ColorPicture");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

