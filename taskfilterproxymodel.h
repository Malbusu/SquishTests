#ifndef TASKFILTERPROXYMODEL_H
#define TASKFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class TaskFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
public:
    TaskFilterProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent){};

    QString filter() const;
    void setFilter(const QString &filter);

    Q_INVOKABLE void addTask(const QString &name);
    Q_INVOKABLE void removeTask(int index);
    Q_INVOKABLE void editTaskName(QString name, int index);
    Q_INVOKABLE void editTaskCompleted(int index, bool completed);

    void persist();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

signals:
    void filterChanged();

private:
    QString m_filter;
};

#endif // TASKFILTERPROXYMODEL_H
