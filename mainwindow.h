//münire kutlum 22100011917
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QList>
#include "watermelon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<Watermelon *> watermelons;
    int gameDuration = 30;

    void setupGame();
    void createWatermelon();
    void updateGame();
    void endGame();
};

#endif // MAINWINDOW_H
