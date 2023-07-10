#ifndef SIDEMENUBUTTON_H
#define SIDEMENUBUTTON_H

#include <QPushButton>

class RippleAnimation;

class SideMenuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SideMenuButton(const QString &text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    RippleAnimation *rippleAnimation_ = nullptr;
};

#endif // SIDEMENUBUTTON_H
