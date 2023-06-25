#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = nullptr);

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
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor placeholderColor READ placeholderColor WRITE setPlaceholderColor NOTIFY placeholderColorChanged)
};

#endif // TEXTEDIT_H
