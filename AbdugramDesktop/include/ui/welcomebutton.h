#ifndef WELCOMEBUTTON_H
#define WELCOMEBUTTON_H

#include <QPushButton>

class RippleAnimation;

class WelcomeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit WelcomeButton(QWidget *parent = nullptr);
    explicit WelcomeButton(const QString &text, QWidget *parent = nullptr);
    WelcomeButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    RippleAnimation *rippleAnimation_ = nullptr;

};

#endif // WELCOMEBUTTON_H
