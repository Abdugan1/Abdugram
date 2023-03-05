#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>
#include <QEasingCurve>

class StackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit StackedWidget(QWidget *parent = nullptr);

    void toWidget(QWidget *widget);
    void toIndex(int index);

    int slideDuration() const;
    void setSlideDuration(int newSlideDuration);

    QEasingCurve easingCurve() const;
    void setEasingCurve(const QEasingCurve &newEasingCurve);

    QWidget *previousWidget();

private:
    void setupToSlideWidget();

    void slideForward();
    void slideBackward();

    void startAnimation(const QPoint &currentBegin, const QPoint &currentEnd,
                        const QPoint &toSlideBegin, const QPoint &toSlideEnd);

private:
    int          slideDuration_ = 200;
    QEasingCurve easingCurve_   = QEasingCurve::OutQuad;

    QWidget *previousWidget_ = nullptr;
    QWidget *currentWidget_  = nullptr;
    QWidget *toSlideWidget_  = nullptr;
};

#endif // STACKEDWIDGET_H
