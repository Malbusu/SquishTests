#ifndef TASK_H
#define TASK_H

#include <qobject.h>

class Task : public QObject
{
    Q_OBJECT

public:

    Task(const QString &name, bool completed, QObject *parent = nullptr)
        : QObject(parent), m_name(name), m_completed(completed){};
    QString getName() const;
    void setName(QString &newName);
    bool getCompleted() const;
    void setCompleted(bool completed);

private:
    QString m_name;
    bool m_completed;
};

#endif // TASK_H
