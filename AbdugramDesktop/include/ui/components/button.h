#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class RippleAnimation;

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, const QIcon &icon, QWidget *parent = nullptr);
    explicit Button(const QString &text, QWidget *parent = nullptr);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    Qt::Alignment textAlignment() const;
    void setTextAlignment(const Qt::Alignment &newTextAlignment);

    int iconTextSpacing() const;
    void setIconTextSpacing(int newIconTextSpacing);

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
        DefaultLeftMargin = 20,
        DefaultTopMargin = 10,
        DefaultRightMargin = 20,
        DefaultBottomMargin = 10,
        DefaultIconTextSpace = 10,
    };

    QColor textColor_;
    QColor backgroundColor_ = Qt::transparent;

    Qt::Alignment textAlignment_ = Qt::AlignLeft;
    int iconTextSpacing_ = DefaultIconTextSpace;

    RippleAnimation *rippleAnimation_ = nullptr;
};

#endif // BUTTON_H
