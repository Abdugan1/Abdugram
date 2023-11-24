#ifndef MAINLABEL_H
#define MAINLABEL_H

#include <QLabel>

class MainLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MainLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit MainLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());

    void setPointSize(int pointSize);
    void setBold(int bold);

private:
    void init();
};

#endif // MAINLABEL_H
