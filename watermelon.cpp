//münire kutlum 22100011917
#include "watermelon.h"

Watermelon::Watermelon(QWidget *parent) : QPushButton(parent)
{
    clickedFlag = false;

    connect(this, &QPushButton::clicked, this, &Watermelon::cutWhenClicked);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Watermelon::resizeWatermelon);
    timer->start(10);
}
bool Watermelon::clickStatus() const
{
    return clickedFlag;
}

void Watermelon::cutWhenClicked()
{
    clickedFlag = !clickedFlag;
    QTimer *cutTimer = new QTimer(this);

    connect(cutTimer, &QTimer::timeout, this, &Watermelon::cutWatermelon);

    this->setStyleSheet("QPushButton {image: url(:/resim/images/2.png);background-color:rgba(0,0,0,0);}");
    cutTimer->start(712);
}

void Watermelon::cutWatermelon()
{
    this->hide();
}

void Watermelon::resizeWatermelon()
{
    if(!clickedFlag){
        this->setGeometry(this->x(), this->y()+1, 71, 71);
    }
}
