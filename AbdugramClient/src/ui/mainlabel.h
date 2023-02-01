#ifndef MAINLABEL_H
#define MAINLABEL_H

#include <QLabel>

class MainLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MainLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit MainLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
};

#endif // MAINLABEL_H
