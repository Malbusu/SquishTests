#pragma once

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "tasksmodel.h"

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(TasksModel *model, QObject* parent = nullptr);

public slots:
    Q_INVOKABLE void mostrarVentanaWidgets();
    void resetRequested();

signals:
    void updateStats(double percentage, int completed, int remaining);

private:
    TasksModel *m_taskModel;
};

#endif // BACKEND_H
