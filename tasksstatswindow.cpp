#include <qboxlayout.h>
#include "tasksstatswindow.h"

TasksStatsWindow::TasksStatsWindow(QWidget *parent) :
    QWidget(parent)
{
    labelPercentage = new QLabel("Completed tasks percentage:", this);
    labelCompleted= new QLabel("Completed tasks:", this);
    labelRemaining= new QLabel("Remaining tasks:", this);

    btnReset = new QPushButton("Reset", this);

    auto layout = new QVBoxLayout;
    layout->addWidget(labelPercentage);
    layout->addWidget(labelCompleted);
    layout->addWidget(labelRemaining);
    layout->addWidget(btnReset);
    setLayout(layout);
}

QPushButton *TasksStatsWindow::getResetButton(){
    return btnReset;
}

void TasksStatsWindow::updateData(double percentage, int completed, int remaining){
    qDebug() << "percentage" << percentage;
    labelPercentage->setText(QString("Completed tasks percentage: %1%").arg(percentage,0,'f',2));
    labelCompleted->setText(QString("Completed tasks:: %1").arg(completed));
    labelRemaining->setText(QString("Remaining tasks: %1").arg(remaining));
}
