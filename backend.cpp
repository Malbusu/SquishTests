#include "Backend.h"
#include "tasksstatswindow.h"
#include "tasksmodel.h"

Backend::Backend(TasksModel *model, TasksStatsWindow *window,QObject* parent) : m_taskModel(model), m_window(window), QObject(parent) {
    m_window->setWindowTitle("Statistics");
    m_window->resize(300,100);
    m_window->connect(m_window->getResetButton(), &QPushButton::clicked, this, &Backend::resetRequested);
    connect(this, &Backend::updateStats, m_window, &TasksStatsWindow::updateStatisticsWindow);
}

void Backend::showStatistics() {
    m_window->show();
    emit updateStats(m_taskModel->calculateCompletedPercentage(), m_taskModel->countCompleted(), m_taskModel->countRemaining());
}

void Backend::resetRequested(){
    m_taskModel->clearAllTasks();
    emit updateStats(m_taskModel->calculateCompletedPercentage(), m_taskModel->countCompleted(), m_taskModel->countRemaining());
}
