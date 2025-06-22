#include "taskfilterproxymodel.h"
#include "tasksmodel.h"

bool TaskFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    auto index = sourceModel()->index(sourceRow, 0, sourceParent);
    bool completed = index.data(TasksModel::CompletedRole).toBool();

    if (m_filter == "active") return !completed;
    if (m_filter == "completed") return completed;
    return true; // "all"
}

QString TaskFilterProxyModel::filter() const {
    return m_filter;
}

void TaskFilterProxyModel::setFilter(const QString &filter) {
    if (m_filter == filter)
        return;

    m_filter = filter;
    invalidateFilter();
    emit filterChanged();
}

void TaskFilterProxyModel::addTask(const QString &name){
    auto model = qobject_cast<TasksModel*>(sourceModel());
    model->addTask(name, false);
    model->saveTasks();
};

void TaskFilterProxyModel::removeTask(int idx){
    auto proxyIndex = index(idx, 0);
    auto sourceIndex = mapToSource(proxyIndex);
    auto model = qobject_cast<TasksModel*>(sourceModel());
    model->removeTask(sourceIndex.row());
    model->saveTasks();
};

void TaskFilterProxyModel::editTaskName(QString name, int idx){
    auto proxyIndex = index(idx, 0);
    auto sourceIndex = mapToSource(proxyIndex);
    auto model = qobject_cast<TasksModel*>(sourceModel());
    model->editTaskName(name, sourceIndex.row());
    model->saveTasks();
};

void TaskFilterProxyModel::editTaskCompleted(int idx, bool completed){
    auto proxyIndex = index(idx, 0);
    auto sourceIndex = mapToSource(proxyIndex);
    auto model = qobject_cast<TasksModel*>(sourceModel());
    model->editTaskCompleted(sourceIndex.row(), completed);
    model->saveTasks();
};
