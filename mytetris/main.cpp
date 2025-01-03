#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ui.h"
#include <QVector2D>
#include <QQmlContext>
#include <fstream>



int main(int argc, char *argv[])
{


    std::ifstream myfile("score.txt");
    if (!myfile.good()){
        myfile.close();
        std::ofstream outputFile("score.txt");
        outputFile << "0";
        outputFile.close();
        myfile.open("score.txt",std::ios::in);
    }


    std::string g;
    myfile >> g;
    myfile.close();
    // myfile >> line;
    // setHigh_score(QString::fromStdString(line));
    // qInfo()<<line;
    // qputenv("QML_XHR_ALLOW_FILE_READ", "1");
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    UI ui(20,10);
    ui.setHigh_score(g.c_str());
    engine.rootContext()->setContextProperty("uiscreen", &ui);



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}



