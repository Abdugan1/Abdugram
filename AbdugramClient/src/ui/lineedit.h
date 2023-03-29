#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
public:
    explicit LineEdit(const QString &placeholder, QWidget *parent = nullptr);

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
    QColor lineColor_ = Qt::black;
};

#endif // LINEEDIT_H
