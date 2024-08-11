//münire kutlum 22100011917
//konumlar ve skorların yolunu verdim kodda

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int cutWatermelonCount = 0, missedWatermelonCount = 0;
QList<Watermelon*> watermelons; // Watermelon nesnelerini tutmak için bir liste

void MainWindow::setupGame()
{
    QTimer *watermelonTimer = new QTimer(this);
    connect(watermelonTimer, &QTimer::timeout, this, &MainWindow::createWatermelon);
    watermelonTimer->start(1500);

    QTimer *gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);
    gameTimer->start(1000);
    gameDuration = 30; // Oyun süresini başlat
    ui->sure->setText(" <font color='blue'>" + QString::number(gameDuration));
}

void MainWindow::createWatermelon()
{
    Watermelon *watermelon = new Watermelon(this);

    QFile konum("D:/görsel/odev/konumlar.txt");
    if (!konum.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Hata!", konum.errorString());
        return;
    }
    QTextStream stremKonum(&konum);

    QString line;
    while(!stremKonum.atEnd()){
        line = stremKonum.readLine();
    }

    QStringList list = line.split(",");
    int x, y;

    if(list.size() == 2){
        x = list.at(0).toInt();
        y = list.at(1).toInt();
    }

    konum.close();
    watermelon->setGeometry(rand()%(this->width()), 60, 42, 42); // Geometriyi burada ayarla
    watermelon->setStyleSheet("QPushButton {image: url(:/resim/images/1.png);background-color:rgba(0,0,0,0);}");    watermelon->show();
    watermelons.append(watermelon);
}


void MainWindow::updateGame()
{

    for(int i = 0; i < watermelons.size(); ++i) {
        Watermelon *watermelon = watermelons.at(i);

        if (watermelon->geometry().y() > this->height()) {
            missedWatermelonCount += 1;
            watermelons.removeAt(i);
            watermelon->hide();
            ui->kacirilan->setText("<font color='red'>" + QString::number(missedWatermelonCount));
        }

        if (watermelon->clickStatus()) {
            cutWatermelonCount += 1;
            watermelons.removeAt(i);
            watermelon->hide(); // Clicked watermelon is hidden
            ui->kesilen->setText("<font color='green'>" + QString::number(cutWatermelonCount));
        }
    }

    gameDuration -= 1; // Süreyi azalt

    ui->sure->setText(" <font color='blue'>" + QString::number(gameDuration));

    if (gameDuration <= 0) {
        endGame();
    }
}

void MainWindow::endGame()
{
    QString scoreFilePath = "D:/görsel/odev/skorlar.txt";
    QFile scoreFile(scoreFilePath);
    if (scoreFile.open(QIODevice::Append)) {
        QTextStream stream(&scoreFile);
        stream << QString::number(cutWatermelonCount) << "\n";
        scoreFile.close();
    } else {
        QMessageBox::critical(this, "Hata!", "Skorlar dosyası açılamadı: " + scoreFile.errorString());
    }

    int maxScore = INT_MIN;
    QFile scoreFileRead(scoreFilePath);
    if (scoreFileRead.open(QIODevice::ReadOnly)) {
        QTextStream stream(&scoreFileRead);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            maxScore = qMax(maxScore, line.toInt());
        }
        scoreFileRead.close();
    } else {
        QMessageBox::critical(this, "Hata!", "Skorlar dosyası açılamadı: " + scoreFileRead.errorString());
    }

    QString endGameMessage;
    if (cutWatermelonCount == maxScore) {
        endGameMessage = "Oyun Bitti! Maksimum Skor Sizde! \n";
    } else {
        endGameMessage = "Oyun Bitti! Maksimum Skoru Geçemediniz! \n";
    }
    endGameMessage += "Kesilen Karpuz Sayısı: " + QString::number(cutWatermelonCount) + "\n";
    endGameMessage += "Kaçırılan Karpuz Sayısı: " + QString::number(missedWatermelonCount) + "\n";
    endGameMessage += "Maximum Skor: " + QString::number(maxScore);
    QMessageBox::information(this, "Bilgi!", endGameMessage, QMessageBox::Ok);

    this->close();
}
