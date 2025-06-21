#pragma once

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "Task.h"

class Backend : public QObject {
    Q_OBJECT
public:
    explicit Backend(QObject* parent = nullptr);

public slots:
    void mostrarVentanaWidgets();

private:
    std::vector<Task> tasks;
};

#endif // BACKEND_H
