#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"
#include "tasksmodel.h"
#include "taskfilterproxymodel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QQmlApplicationEngine engine; 

    TasksModel tasksModel;
    tasksModel.loadTasks();
    Backend backend(&tasksModel);
    TaskFilterProxyModel taskFilterModel;
    taskFilterModel.setSourceModel(&tasksModel);

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("tasksModel", &tasksModel);
    engine.rootContext()->setContextProperty("taskFilterModel", &taskFilterModel);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/squishtests/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
