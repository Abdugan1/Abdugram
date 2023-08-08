#ifndef RIPPLEANIMATION_H
#define RIPPLEANIMATION_H

#include <QObject>
#include <QList>
#include <QPoint>

#include <memory>

class QPainter;

class RippleAnimation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rippleRadius READ rippleRadius WRITE setRippleRadius NOTIFY rippleRadiusChanged)
    Q_PROPERTY(int rippleOpacity READ rippleOpacity WRITE setRippleOpacity NOTIFY rippleOpacityChanged)
public:
    explicit RippleAnimation(QWidget *parent);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void drawRipple(QPainter *painter) const;

    int rippleRadius() const;
    void setRippleRadius(int newRippleRadius);

    int rippleOpacity() const;
    void setRippleOpacity(int newRippleOpacity);

signals:
    void rippleRadiusChanged();
    void rippleOpacityChanged();

    void startRippleSignal();
    void endRippleSignal();

private:
    void startRipple(const QPoint &startPos);
    void endRipple();

    int parentDiagonal() const;

private:
    QWidget *parent_ = nullptr;

    QPoint startPos_;
    int rippleRadius_ = 0;
    int rippleOpacity_ = 0;
};


#endif // RIPPLEANIMATION_H
