#ifndef RIPPLEANIMATION_H
#define RIPPLEANIMATION_H

#include <QObject>
#include <QColor>
#include <QPoint>

class QPropertyAnimation;
class QWidget;

class RippleAnimation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double rippleWidth READ rippleWidth WRITE setRippleWidth NOTIFY rippleWidthChanged)
    Q_PROPERTY(double opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool hasRipple READ hasRipple WRITE setHasRipple NOTIFY hasRippleChanged)
public:
    explicit RippleAnimation(QWidget *parent);

    void start();
    void stop();

    double rippleWidth() const;
    void setRippleWidth(double newRippleWidth);

    double opacity() const;
    void setOpacity(double newRippleOpacity);

    void setAppearTime(int msec);
    void setDisappearTime(int msec);

    void setEndRippleWidth(double endWidth);
    void setEndOpacity(double endOpacity);

    QColor color() const;
    void setColor(const QColor &newRippleColor);

    bool hasRipple() const;
    void setHasRipple(bool newHasRipple);

    QPoint startPos() const;
    void setStartPos(QPoint newStartPos);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void drawRipple() const;

signals:
    void rippleWidthChanged();
    void opacityChanged();

    void colorChanged();

    void hasRippleChanged();

private:
    double rippleWidth_   = 0.0;
    double opacity_       = 0.0;

    double endRippleWidth_ = 0.0;
    double endOpacity_     = 0.0;

    int borderRadius_ = 0;

    QColor color_ = Qt::white;
    QPoint startPos_ = QPoint{};

    bool hasRipple_ = false;

    QPropertyAnimation *rippleWidthAnim_      = nullptr;
    QPropertyAnimation *appearOpacityAnim_    = nullptr;
    QPropertyAnimation *disappearOpacityAnim_ = nullptr;

    QWidget *widget_ = nullptr;
};

#endif // RIPPLEANIMATION_H
