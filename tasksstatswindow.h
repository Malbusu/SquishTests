#ifndef TASKSSTATSWINDOW_H
#define TASKSSTATSWINDOW_H

#include <QObject>
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>

class TasksStatsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TasksStatsWindow(QWidget *parent = nullptr);
    QPushButton* getResetButton();

public slots:
    void updateStatisticsWindow(double percentage, int completed, int remaining);

private:
    QLabel *labelPercentage;
    QLabel *labelCompleted;
    QLabel *labelRemaining;
    QPushButton *btnReset;
};

#endif // TASKSSTATSWINDOW_H
