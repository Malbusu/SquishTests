#include "tasksmodel.h"
#include <QJsonDocument>
#include <QJsonObject>

int TasksModel::rowCount(const QModelIndex &) const{
    return m_tasks.size();
}

QVariant TasksModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= m_tasks.size())
        return QVariant();

    auto *task = m_tasks.at(index.row());
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

void TasksModel::addTask(const QString &name, bool completed){
    beginInsertRows(QModelIndex(), m_tasks.size(), m_tasks.size());
    m_tasks.append(new Task(name, completed, this));
    endInsertRows();
    QJsonObject task;
    task["name"] = name;
    task["completed"] = completed;
    m_tasksJson.append(task);
}

void TasksModel::removeTask(int index){
    if(index < 0 || index >= m_tasks.size())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_tasks.removeAt(index);
    m_tasksJson.removeAt(index);
    endRemoveRows();
}

void TasksModel::editTaskName(QString name, int index){
    if(index < 0 || index >= m_tasks.size())
        return;

    auto *task = m_tasks.at(index);
    task->setName(name);

    QJsonObject obj;
    obj["name"] = name;
    obj["completed"] = task->getCompleted();
    auto qv = QJsonValue(obj);
    m_tasksJson.replace(index, qv);

    auto modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { NameRole });
}

void TasksModel::editTaskCompleted(int index, bool completed){
    if(index < 0 || index >= m_tasks.size())
        return;

    auto *task = m_tasks.at(index);
    task->setCompleted(completed);

    QJsonObject obj;
    obj["name"] = task->getName();
    obj["completed"] = completed;
    auto qv = QJsonValue(obj);
    m_tasksJson.replace(index, qv);

    auto modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { CompletedRole });
}

void TasksModel::saveTasks(){
    auto file = QFile("./tasks.json");
    if(!file.open(QIODevice::WriteOnly)){
        //err
        return;
    }

    file.write(QJsonDocument(m_tasksJson).toJson());
    file.close();
}

void TasksModel::loadTasks(QString path){
    auto file = QFile(path);
    if(!file.open(QIODevice::ReadOnly)){
        //create
        return;
    }
    auto data = file.readAll();
    file.close();

    auto jsonDoc = QJsonDocument::fromJson(data);
    if(!jsonDoc.isArray()){
        //err
        return;
    }
    m_tasksJson = jsonDoc.array();

    beginResetModel();
    for (const QJsonValue &value: std::as_const(m_tasksJson)){
        auto task = value.toObject();
        m_tasks.append(new Task(task["name"].toString(), task["completed"].toBool(), this));
    }
    endResetModel();
}
