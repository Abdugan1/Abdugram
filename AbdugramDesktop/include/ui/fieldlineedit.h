#ifndef FIELDLINEEDIT_H
#define FIELDLINEEDIT_H

#include "lineedit.h"

class FieldLineEdit : public LineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
public:
    explicit FieldLineEdit(const QString &placeholder, QWidget *parent = nullptr);

    QColor lineColor() const;
    void setLineColor(const QColor &newLineColor);

signals:
    void lineColorChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    void showValidInputState();
    void showInvalidInputState();

private:
    QColor lineColor_       = Qt::black;
    QColor placeholderColor_ = Qt::black;
};

#endif // FIELDLINEEDIT_H
