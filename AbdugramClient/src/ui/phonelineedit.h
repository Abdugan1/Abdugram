#ifndef PHONELINEEDIT_H
#define PHONELINEEDIT_H

#include "lineedit.h"

class MainLabel;

class PhoneLineEdit : public LineEdit
{
public:
    explicit PhoneLineEdit();

    QString getPhone() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    MainLabel *phoneCode_ = nullptr;
};

#endif // PHONELINEEDIT_H
