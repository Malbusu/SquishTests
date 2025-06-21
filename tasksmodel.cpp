#include "tasksmodel.h"

int TasksModel::rowCount(const QModelIndex &) const{
    return m_tasks.size();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= m_tasks.size())
        return QVariant();

    Task *task = m_tasks.at(index.row());
    if(role == NameRole)
        return task->getName();
    if(role == CompletedRole)
        return task->getCompleted();

    return QVariant();
}

QHash<int, QByteArray> TasksModel::roleNames() const{
    return {
        { NameRole, "name"},
        { CompletedRole, "completed"}
    };
}

void TasksModel::addTask(const QString &name){
    beginInsertRows(QModelIndex(), m_tasks.size(), m_tasks.size());
    m_tasks.append(new Task(name, false, this));
    endInsertRows();
}

void TasksModel::removeTask(int index){
    if(index < 0 || index >= m_tasks.size())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_tasks.removeAt(index);
    endRemoveRows();
}

void TasksModel::editTaskName(QString name, int index){
    if(index < 0 || index >= m_tasks.size())
        return;

    Task *task = m_tasks.at(index);
    task->setName(name);

    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { NameRole });
}

void TasksModel::editTaskCompleted(int index, bool completed){
    if(index < 0 || index >= m_tasks.size())
        return;

    Task *task = m_tasks.at(index);
    task->setCompleted(completed);

    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { CompletedRole });
}
