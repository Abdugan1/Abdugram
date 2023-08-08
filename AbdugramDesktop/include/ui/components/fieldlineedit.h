#ifndef FIELDLINEEDIT_H
#define FIELDLINEEDIT_H

#include <QLineEdit>

class FieldLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
public:
    explicit FieldLineEdit(const QString &placeholder, QWidget *parent = nullptr);

    QColor lineColor() const;
    void setLineColor(const QColor &newLineColor);

    void changeColor(const QColor &color);

signals:
    void lineColorChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    void init(const QString &placeholder);

    void showValidInputState();
    void showInvalidInputState();

    void startColorAnimation(const QColor &start, const QColor &end);

private:
    enum {
        LineWidth = 2
    };

    QColor lineColor_;
    QColor textColor_;
    QColor placeholderColor_;
};

#endif // FIELDLINEEDIT_H
