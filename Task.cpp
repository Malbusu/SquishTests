#include "Task.h"

QString Task::getName() const{
    return m_name;
}

void Task::setName(QString &newName){
    m_name = newName;
}

bool Task::getCompleted() const{
    return m_completed;
}

void Task::setCompleted(bool completed){
    m_completed = completed;
}
