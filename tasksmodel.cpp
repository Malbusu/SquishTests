#include "tasksmodel.h"
#include <QJsonDocument>
#include <QJsonObject>

static constexpr const char* TASKS_FILE = "./tasks.json";

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

    auto *task = m_tasks.at(index);
    task->setName(name);

    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { NameRole });
}

void TasksModel::editTaskCompleted(int index, bool completed){
    if(index < 0 || index >= m_tasks.size())
        return;

    auto *task = m_tasks.at(index);
    task->setCompleted(completed);

    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { CompletedRole });
}

void TasksModel::saveTasks(){
    auto file = QFile(TASKS_FILE);
    if(!file.open(QIODevice::WriteOnly)){
        qWarning() << "Could not save tasks";
        return;
    }

    QJsonArray jsonArray;
    for(Task* task: std::as_const(m_tasks)){
        QJsonObject obj;
        obj["name"] = task->getName();
        obj["completed"] = task->getCompleted();
        auto qv = QJsonValue(obj);
        jsonArray.append(qv);
    }
    file.write(QJsonDocument(jsonArray).toJson());
    file.close();
}

void TasksModel::loadTasks(){
    auto file = QFile(TASKS_FILE);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    auto data = file.readAll();
    file.close();

    auto jsonDoc = QJsonDocument::fromJson(data);
    if(!jsonDoc.isArray()){
        qWarning() << "Error loading tasks - Invalid JSON";
        return;
    }
    const auto jsonArray = jsonDoc.array();

    beginResetModel();
    qDeleteAll(m_tasks);
    m_tasks.clear();
    for (const QJsonValue &value: jsonArray){
        auto task = value.toObject();
        m_tasks.append(new Task(task["name"].toString(), task["completed"].toBool(), this));
    }
    endResetModel();
}

int TasksModel::countCompleted(){
    int completed = 0;
    for(const Task *t : std::as_const(m_tasks)){
        if(t->getCompleted())
            completed++;
    }
    return completed;
}

double TasksModel::calculateCompletedPercentage(){
    int total = m_tasks.size();
    if(total == 0)
        return 0;

    int completed = countCompleted();
    return static_cast<double>(completed) * 100 / total;
}

int TasksModel::countRemaining(){
    return m_tasks.size() - countCompleted();
}

void TasksModel::clearAllTasks() {
    beginResetModel();
    qDeleteAll(m_tasks);
    m_tasks.clear();
    endResetModel();
}
