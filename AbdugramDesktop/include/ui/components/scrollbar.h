#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QScrollBar>

class ScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit ScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QRect handleRect() const;
    int extent() const;
};

#endif // SCROLLBAR_H
