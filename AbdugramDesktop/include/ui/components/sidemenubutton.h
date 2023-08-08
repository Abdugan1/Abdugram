#ifndef SIDEMENUBUTTON_H
#define SIDEMENUBUTTON_H

#include <QPushButton>

class RippleAnimation;

class SideMenuButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SideMenuButton(const QString &text, const QIcon &icon, QWidget *parent = nullptr);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

    void drawBackground(QPainter *painter);
    void drawIcon(QPainter *painter);
    void drawText(QPainter *painter);

private:
    enum {
        LeftMargin = 20,
        IconTextSpace = 10,
    };

    QColor textColor_;

    RippleAnimation *rippleAnimation_ = nullptr;
};

#endif // SIDEMENUBUTTON_H
