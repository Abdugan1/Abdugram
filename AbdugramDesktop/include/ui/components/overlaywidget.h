#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QWidget>

class OverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OverlayWidget(QWidget *parent = nullptr);

    QWidget *widget() const;
    void setWidget(QWidget *newWidget);

signals:
    void overlayClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QWidget *widget_= nullptr;
};

#endif // OVERLAYWIDGET_H
