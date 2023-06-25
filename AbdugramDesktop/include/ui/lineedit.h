#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor placeholderColor READ placeholderColor WRITE setPlaceholderColor NOTIFY placeholderColorChanged)
public:
    explicit LineEdit(QWidget *parent = nullptr);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    QColor placeholderColor() const;
    void setPlaceholderColor(const QColor &newPlaceholderColor);

signals:
    void textColorChanged();
    void placeholderColorChanged();

private slots:
    void setAppropriateColor();

private:
    QColor textColor_ = Qt::black;
    QColor placeholderColor_ = Qt::gray;
};

#endif // LINEEDIT_H
