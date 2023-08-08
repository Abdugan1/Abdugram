#ifndef PROBLEMWIDGET_H
#define PROBLEMWIDGET_H

#include <QWidget>

class QLabel;
class SecondaryLabel;

class ProblemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProblemWidget(QWidget *parent = nullptr);

    void setTextToConnecting();
    void setRemainingTime(int remainingSeconds);

signals:
    void reconnectNowClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();

private:
    QLabel *busyIndicator_ = nullptr;
    SecondaryLabel *text_  = nullptr;
    SecondaryLabel *reconnectLink_ = nullptr;

};

#endif // PROBLEMWIDGET_H
