#ifndef PHONELINEEDIT_H
#define PHONELINEEDIT_H

#include "fieldlineedit.h"

class MainLabel;

class PhoneLineEdit : public FieldLineEdit
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
