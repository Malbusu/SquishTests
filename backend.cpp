#include "Backend.h"
#include "tasksstatswindow.h"
#include "tasksmodel.h"

Backend::Backend(TasksModel *model, QObject* parent) : m_taskModel(model), QObject(parent) {
}

void Backend::mostrarVentanaWidgets() {
    auto *window = new TasksStatsWindow();
    window->setWindowTitle("Statistics");
    window->resize(300,100);
    window->show();
    window->connect(window->getResetButton(), &QPushButton::clicked, this, &Backend::resetRequested);
    connect(this, &Backend::updateStats, window, &TasksStatsWindow::updateData);
    emit updateStats(m_taskModel->getCompletedPercentage(), m_taskModel->getCompleted(), m_taskModel->getRemaining());
}

void Backend::resetRequested(){
    m_taskModel->clearAllTasks();
    emit updateStats(m_taskModel->getCompletedPercentage(), m_taskModel->getCompleted(), m_taskModel->getRemaining());
}
