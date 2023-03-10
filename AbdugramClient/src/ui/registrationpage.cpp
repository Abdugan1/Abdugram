#include "registrationpage.h"
#include "lineedit.h"
#include "headerlabel.h"
#include "secondarylabel.h"
#include "button.h"
#include "imagebutton.h"

#include <net_common/messages/registermessage.h>

#include <QBoxLayout>
#include <QGridLayout>

RegistrationPage::RegistrationPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(nextButton_, &Button::clicked,
            this,        &RegistrationPage::sendRegisterMessage);

    connect(backButton_, &ImageButton::clicked,
            this,        &RegistrationPage::backButtonClicked);

    connect(toLoginPageLabel_, &QLabel::linkActivated,
            this,              &RegistrationPage::toLoginPageClicked);
}

void RegistrationPage::sendRegisterMessage()
{
    AnyMessagePtr<RegisterMessage> registerMessage{new RegisterMessage};
    registerMessage->setFirstName(firstNameEdit_->text());
    registerMessage->setLastName(lastNameEdit_->text());
    registerMessage->setUsername(usernameEdit_->text());
    registerMessage->setEmail(emailEdit_->text());
    registerMessage->setPhone(phoneNumberEdit_->text());
    registerMessage->setPassword(passwordEdit_->text());

    emit registerRequested(static_cast<AbduMessagePtr>(registerMessage));
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

    //
    toLoginPageLabel_ = new SecondaryLabel{tr("Already have an account? "
                                              "<a href=\"to_login\""
                                              "style = \""
                                              "color: #A4508B;"
                                              "text-decoration: underlying;"
                                              "\""
                                              ">Login</a>")};

    // Group
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addLayout(labelsLayout);
    groupLayout->addLayout(gLayout);
    groupLayout->addWidget(nextButton_);
    groupLayout->addWidget(toLoginPageLabel_);

    groupLayout->setAlignment(Qt::AlignCenter);
    groupLayout->setSpacing(15);

    QWidget *group = new QWidget;
    group->setLayout(groupLayout);
    group->setFixedWidth(600);

    // Back button
    backButton_ = new ImageButton{QPixmap{":/images/BackButton.png"}};

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
