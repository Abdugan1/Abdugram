#include "registrationpage.h"
#include "lineedit.h"
#include "headerlabel.h"
#include "secondarylabel.h"
#include "button.h"

#include <QBoxLayout>
#include <QGridLayout>

RegistrationPage::RegistrationPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
}

void RegistrationPage::setupUi()
{
    //
    tellUsAboutLabel_ = new HeaderLabel{tr("Tell Us About You")};
    tellUsAboutLabel_->setAlignment(Qt::AlignCenter);

    pageInfo_         = new SecondaryLabel{tr("Please enter your information "
                                              "in corresponding forms")};
    pageInfo_->setAlignment(Qt::AlignCenter);

    //
    QVBoxLayout *labelsLayout = new QVBoxLayout;
    labelsLayout->addWidget(tellUsAboutLabel_);
    labelsLayout->addWidget(pageInfo_);

    labelsLayout->setSpacing(6);

    // Line edits configuration
    firstNameEdit_       = new LineEdit{tr("First Name")};
    lastNameEdit_        = new LineEdit{tr("Last Name")};
    usernameEdit_        = new LineEdit{tr("Username")};
    emailEdit_           = new LineEdit{tr("Email")};
    phoneNumberEdit_     = new LineEdit{tr("Phone Number")};
    passwordEdit_        = new LineEdit{tr("Password")};
    confirmPasswordEdit_ = new LineEdit{tr("Confirm Password")};

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setHorizontalSpacing(50);
    gLayout->setHorizontalSpacing(23);

    gLayout->addWidget(firstNameEdit_,       0, 0);
    gLayout->addWidget(lastNameEdit_,        0, 1);
    gLayout->addWidget(usernameEdit_,        1, 0, 1, 2);
    gLayout->addWidget(emailEdit_,           2, 0, 1, 2);
    gLayout->addWidget(phoneNumberEdit_,     3, 0, 1, 2);
    gLayout->addWidget(passwordEdit_,        4, 0);
    gLayout->addWidget(confirmPasswordEdit_, 4, 1);

    //
    nextButton_ = new Button{tr("Next")};

    // Group
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addLayout(labelsLayout);
    groupLayout->addLayout(gLayout);
    groupLayout->addWidget(nextButton_);

    groupLayout->setAlignment(Qt::AlignCenter);
    groupLayout->setSpacing(15);

    QWidget *group = new QWidget;
    group->setLayout(groupLayout);
    group->setFixedWidth(600);

    // Back button
    backButton_ = new Button{tr("Back")};

    //
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(backButton_);
    topLayout->addStretch();

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(group, 0, Qt::AlignCenter);

    setLayout(mainLayout);
}
