#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class RippleAnimation;

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ImageButton(const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init(const QPixmap &pixmap);

private:
    RippleAnimation *rippleAnimation_ = nullptr;

};

#endif // IMAGEBUTTON_H
