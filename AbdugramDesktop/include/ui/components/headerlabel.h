#ifndef HEADERLABEL_H
#define HEADERLABEL_H

#include <QLabel>

class HeaderLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HeaderLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit HeaderLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());

private:
    void init();
};

#endif // HEADERLABEL_H
