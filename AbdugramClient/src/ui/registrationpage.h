#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QWidget>

class LineEdit;

class RegistrationPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegistrationPage(QWidget *parent = nullptr);

signals:

private:
    void setupUi();

private:
    LineEdit *firstNameEdit_       = nullptr;
    LineEdit *lastNameEdit_        = nullptr;
    LineEdit *usernameEdit_        = nullptr;
    LineEdit *emailEdit_           = nullptr;
    LineEdit *phoneNumberEdit_     = nullptr;
    LineEdit *passwordEdit_        = nullptr;
    LineEdit *confirmPasswordEdit_ = nullptr;

};

#endif // REGISTRATIONPAGE_H
