#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>

class RippleAnimation;

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(const QPixmap &pixmap);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init(const QPixmap &pixmap);

    void drawBackground(QPainter *painter);
    void drawIcon(QPainter *painter);

private:
    QColor backgroundColor_ = Qt::transparent;

    RippleAnimation *rippleAnimation_ = nullptr;
};

#endif // IMAGEBUTTON_H
