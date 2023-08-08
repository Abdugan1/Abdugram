#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "ui/components/widget.h"
#include <QPushButton>

class SystemButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SystemButton();

    QIcon defaultIcon() const;
    void setDefaultIcon(const QIcon &newDefaultIcon);

    QIcon hoverIcon() const;
    void setHoverIcon(const QIcon &newHoverIcon);

    QColor hoverColor() const;
    void setHoverColor(const QColor &newHoverColor);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QIcon defaultIcon_;
    QIcon hoverIcon_;

    QColor hoverColor_;
};

class TitleBar : public Widget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent);

private:
    void setupUi();

private:
    SystemButton *minimizeButton_ = nullptr;
    SystemButton *maximizeButton_ = nullptr;
    SystemButton *closeButton_    = nullptr;
};

#endif // TITLEBAR_H
