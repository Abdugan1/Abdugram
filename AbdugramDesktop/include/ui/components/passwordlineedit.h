#ifndef PASSWORDLINEEDIT_H
#define PASSWORDLINEEDIT_H

#include "fieldlineedit.h"

#include <memory>

class QLabel;
class QState;

class SecondaryLabel;

class ToolTipLineEdit;

class ToolTip : public QWidget
{
    Q_OBJECT
public:
    enum Types {
        Information,
        Critical,
    };

    explicit ToolTip(ToolTipLineEdit *lineEdit);

    void setText(const QString &text);

    Types type() const;
    void setType(Types newType);

    void appear();
    void disappear();

signals:
    void shouldAppear();
    void shouldDisappear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void updateStates();

    void setParameters();
    void setIcon(const QPixmap &pixmap);
    void setTextColor(const QColor &color);
    void setBackgroundColor(const QColor &color);
    void setStrokeColor(const QColor &color);

private:
    enum {
        Radius = 4
    };

    Types type_ = Types::Information;

    QState *hideState_ = nullptr;
    QState *showState_ = nullptr;

    QLabel *icon_ = nullptr;
    SecondaryLabel *text_ = nullptr;

    ToolTipLineEdit* lineEdit_ = nullptr;

    QColor backgroundColor_;
    QColor strokeColor_;
};

class ToolTipLineEdit : public FieldLineEdit
{
    Q_OBJECT
public:
    explicit ToolTipLineEdit(const QString &placeholder, QWidget *parent = nullptr);
};

#endif // PASSWORDLINEEDIT_H
