#include "ui/pages/hellopage.h"

#include "ui/components/welcomebutton.h"
#include "ui/components/headerlabel.h"
#include "ui/components/secondarylabel.h"

#include <QBoxLayout>

inline QSpacerItem *createHSpacer()
{
    return new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum};
}

inline QSpacerItem *createVSpacer()
{
    return new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding};
}

HelloPage::HelloPage(QWidget *parent)
    : Widget{parent}
{
    setupUi();
    
    connect(startButton_, &WelcomeButton::clicked,
            this,         &HelloPage::startMessagingClicked);
}

void HelloPage::setupUi()
{
    appNameLabel_ = new HeaderLabel{tr("Abdugram Desktop")};
    appNameLabel_->setAlignment(Qt::AlignCenter);

    welcomeLabel_ = new SecondaryLabel{tr("Welcome to the official Abdugram Desktop app.\n"
                                          "It's fast and secure.")};
    welcomeLabel_->setAlignment(Qt::AlignCenter);
    
    startButton_ = new WelcomeButton{tr("Start Messaging")};
    startButton_->setShortcut(QKeySequence{Qt::Key_Return});

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addSpacerItem(createVSpacer());
    vLayout->addWidget(appNameLabel_);
    vLayout->addWidget(welcomeLabel_);
    vLayout->addWidget(startButton_);
    vLayout->addSpacerItem(createVSpacer());

    vLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(vLayout);
}
