#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
public:
    explicit Widget(QWidget *parent = nullptr);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor backgroundColor_;
};

#endif // WIDGET_H
