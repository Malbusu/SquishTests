#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include <qobject.h>
#include <QAbstractListModel>
#include "Task.h"

class TasksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles{
        NameRole = Qt::UserRole + 1,
        CompletedRole
    };

    explicit TasksModel(QObject *parent = nullptr) : QAbstractListModel(parent){};

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTask(const QString &name);
    Q_INVOKABLE void removeTask(int index);
    Q_INVOKABLE void editTaskName(QString name, int index);
    Q_INVOKABLE void editTaskCompleted(int index, bool completed);

private:
    QVector<Task*> m_tasks;
};

#endif // TASKSMODEL_H
