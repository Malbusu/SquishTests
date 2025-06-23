#pragma once

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "tasksmodel.h"
#include "tasksstatswindow.h"

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(TasksModel *model,  TasksStatsWindow *window,QObject* parent = nullptr);

public slots:
    Q_INVOKABLE void showStatistics();
    void resetRequested();

signals:
    void updateStats(double percentage, int completed, int remaining);

private:
    TasksModel *m_taskModel;
    TasksStatsWindow *m_window;
};

#endif // BACKEND_H
