#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class RippleAnimation;

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    explicit Button(const QString &text, QWidget *parent = nullptr);
    Button(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    RippleAnimation *rippleAnimation_ = nullptr;

};

#endif // BUTTON_H
