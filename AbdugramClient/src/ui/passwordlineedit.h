#ifndef PASSWORDLINEEDIT_H
#define PASSWORDLINEEDIT_H

#include "lineedit.h"

class SecondaryLabel;

class ToolTip : public QWidget
{
    Q_OBJECT
public:
    explicit ToolTip();

protected:

private:
    SecondaryLabel *passwordRules_ = nullptr;
};

class PasswordLineEdit : public LineEdit
{
    Q_OBJECT
public:
    explicit PasswordLineEdit(const QString &placeholder, QWidget *parent = nullptr);

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    ToolTip toolTip_;
};

#endif // PASSWORDLINEEDIT_H
