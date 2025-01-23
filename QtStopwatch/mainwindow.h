#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QMainWindow>
#include "Stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartStopButtonClicked();
    void onResetButtonClicked();
    void onLapButtonClicked();

    void updateTimeLabel(const QString &time);

private:
    Ui::MainWindow *ui;
    Stopwatch *stopwatch;
    int lapCount;
};

#endif // MAINWINDOW_H
