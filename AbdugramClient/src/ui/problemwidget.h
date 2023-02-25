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
    explicit ProblemWidget(const QString &text, QWidget *parent = nullptr);

    void setText(const QString &text);
    void setSizeByTemplateText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init(const QString &text);

private:
    QLabel *busyIndicator_ = nullptr;
    SecondaryLabel *text_  = nullptr;

};

#endif // PROBLEMWIDGET_H
