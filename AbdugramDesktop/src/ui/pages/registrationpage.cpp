#include "ui/pages/registrationpage.h"

#include "ui/components/fieldlineedit.h"
#include "ui/components/headerlabel.h"
#include "ui/components/secondarylabel.h"
#include "ui/components/welcomebutton.h"
#include "ui/components/iconbutton.h"
#include "ui/components/phonelineedit.h"
#include "ui/components/passwordlineedit.h"
#include "ui/components/regexes.h"

#include "net/networkhandler.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QRegularExpressionValidator>
#include <QDebug>

RegistrationPage::RegistrationPage(QWidget *parent)
    : Widget{parent}
{
    setupUi();
    
    connect(nextButton_, &WelcomeButton::clicked,
            this,        &RegistrationPage::sendRegisterMessage);
    
    connect(backButton_, &IconButton::clicked,
            this,        &RegistrationPage::backButtonClicked);

    connect(toLoginPageLabel_, &QLabel::linkActivated,
            this,              &RegistrationPage::toLoginPageClicked);

    // line edits
    connect(firstNameEdit_,       &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(usernameEdit_,        &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(emailEdit_,           &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(phoneNumberEdit_,     &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(passwordEdit_,        &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);

    connect(confirmPasswordEdit_, &FieldLineEdit::textChanged,
            this,                 &RegistrationPage::onLineEditsChanged);
}

void RegistrationPage::sendRegisterMessage()
{
    const QString firstName = firstNameEdit_->text();
    const QString username  = usernameEdit_->text();
    const QString email     = emailEdit_->text();
    const QString phone     = phoneNumberEdit_->getPhone();
    const QString password  = passwordEdit_->text();

    networkHandler()->sendRegisterRequest(firstName, username,  email,
                                          phone,     password);
}

void RegistrationPage::onLineEditsChanged()
{
    nextButton_->setEnabled(firstNameEdit_->hasAcceptableInput()
                            && usernameEdit_->hasAcceptableInput()
                            && emailEdit_->hasAcceptableInput()
                            && phoneNumberEdit_->hasAcceptableInput()
                            && passwordEdit_->hasAcceptableInput()
                            && (confirmPasswordEdit_->text() == passwordEdit_->text()));
}

void RegistrationPage::showEvent(QShowEvent *event)
{
    Widget::showEvent(event);
    firstNameEdit_->setFocus();
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
    firstNameEdit_ = new FieldLineEdit{tr("First Name")};
    firstNameEdit_->setValidator(new QRegularExpressionValidator{ui::regex::NameRegex});

    usernameEdit_ = new FieldLineEdit{tr("Username")};
    usernameEdit_->setValidator(new QRegularExpressionValidator{ui::regex::UsernameRegex});

    emailEdit_ = new FieldLineEdit{tr("Email")};
    emailEdit_->setValidator(new QRegularExpressionValidator{ui::regex::EmailRegex});

    phoneNumberEdit_ = new PhoneLineEdit;

    passwordEdit_ = new PasswordLineEdit{tr("Password")};
    passwordEdit_->setValidator(new QRegularExpressionValidator{ui::regex::PasswordRegex});

    confirmPasswordEdit_ = new FieldLineEdit{tr("Confirm Password")};

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setHorizontalSpacing(50);
    gLayout->setHorizontalSpacing(23);

    gLayout->addWidget(firstNameEdit_,       0, 0);
    gLayout->addWidget(usernameEdit_,        0, 1);
    gLayout->addWidget(emailEdit_,           2, 0, 1, 2);
    gLayout->addWidget(phoneNumberEdit_,     3, 0, 1, 2);
    gLayout->addWidget(passwordEdit_,        4, 0);
    gLayout->addWidget(confirmPasswordEdit_, 4, 1);

    //
    nextButton_ = new WelcomeButton{tr("Next")};
    nextButton_->setEnabled(false);
    nextButton_->setShortcut(QKeySequence{Qt::Key_Return});

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
    backButton_ = new IconButton{QPixmap{":/images/back_button.png"}};

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