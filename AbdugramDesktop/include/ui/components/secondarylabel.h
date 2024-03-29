#ifndef SECONDARYLABEL_H
#define SECONDARYLABEL_H

#include <QLabel>

class SecondaryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SecondaryLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit SecondaryLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());

    void setPointSize(int pointSize);
    void setBold(bool bold);

private:
    void init();
};

#endif // SECONDARYLABEL_H
