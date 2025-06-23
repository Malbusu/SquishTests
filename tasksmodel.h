#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <qobject.h>
#include <QAbstractListModel>
#include "Task.h"
#include <QFile>
#include <QJsonArray>

class TasksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        NameRole = Qt::UserRole + 1,
        CompletedRole
    };

    explicit TasksModel(QObject *parent = nullptr) :  QAbstractListModel(parent){};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addTask(const QString &name, bool completed);
    void removeTask(int index);
    void editTaskName(QString name, int index);
    void editTaskCompleted(int index, bool completed);

    double getCompletedPercentage();
    int getCompleted();
    int getRemaining();

    void saveTasks();
    void loadTasks();
    void clearAllTasks();

private:
    QVector<Task*> m_tasks;
    QJsonArray m_tasksJson;
};

#endif // TASKSMODEL_H
