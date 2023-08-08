#ifndef WELCOMEBUTTON_H
#define WELCOMEBUTTON_H

#include <QPushButton>

class RippleAnimation;

class WelcomeButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit WelcomeButton(QWidget *parent = nullptr);
    explicit WelcomeButton(const QString &text, QWidget *parent = nullptr);
    WelcomeButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

    double cornerRadius() const;
    void setCornerRadius(double newCornerRadius);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

signals:
    void enabled();
    void disabled();

    void backgroundColorChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    void init();

    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);

private:
    double cornerRadius_ = 0;

    QColor disabledColor_;
    QColor backgroundColor_;
    QColor textColor_;

    RippleAnimation *rippleAnimation_ = nullptr;
};

#endif // WELCOMEBUTTON_H
