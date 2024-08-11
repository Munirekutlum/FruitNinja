//münire kutlum 22100011917
#ifndef WATERMELON_H
#define WATERMELON_H

#include <QPushButton>
#include <QTimer>

class Watermelon : public QPushButton
{
    Q_OBJECT

public:
    explicit Watermelon(QWidget *parent = nullptr);

    bool clickStatus() const; // clickStatus fonksiyonunu tanımladık

private slots:
    void cutWhenClicked();
    void cutWatermelon();
    void resizeWatermelon();

private:
    bool clickedFlag;
    QTimer *timer;
};

#endif // WATERMELON_H
