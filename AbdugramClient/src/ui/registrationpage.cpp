#include "registrationpage.h"
#include "lineedit.h"

#include <QBoxLayout>
#include <QGridLayout>

RegistrationPage::RegistrationPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

void RegistrationPage::setupUi()
{
    firstNameEdit_ = new LineEdit{tr("First Name")};

    lastNameEdit_ = new LineEdit{tr("Last Name")};

    usernameEdit_ = new LineEdit{tr("Username")};

    emailEdit_ = new LineEdit{tr("Email")};

    phoneNumberEdit_ = new LineEdit{tr("Phone Number")};

    passwordEdit_ = new LineEdit{tr("Password")};

    confirmPasswordEdit_ = new LineEdit{tr("Confirm Password")};

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(firstNameEdit_,       0, 0);
    gLayout->addWidget(lastNameEdit_,        0, 1);
    gLayout->addWidget(usernameEdit_,        1, 0, 1, 2);
    gLayout->addWidget(emailEdit_,           2, 0, 1, 2);
    gLayout->addWidget(phoneNumberEdit_,     3, 0, 1, 2);
    gLayout->addWidget(passwordEdit_,        4, 0);
    gLayout->addWidget(confirmPasswordEdit_, 4, 1);

    setLayout(gLayout);
}
