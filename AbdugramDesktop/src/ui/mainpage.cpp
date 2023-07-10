#include "ui/mainpage.h"
#include "ui/sidemenu.h"
#include "ui/sidepanel.h"
#include "ui/conversationside.h"

#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QSplitter>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QDebug>

const auto BlurStart = 0.0;
const auto BlurEnd   = 5.0;

MainPage::MainPage(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
    
    connect(sidePanel_, &SidePanel::selectionWasChanged, conversationSide_, &ConversationSide::setCurrentChatItem);
    connect(sidePanel_, &SidePanel::newChatItemAdded,    conversationSide_, &ConversationSide::checkCurrentChatItem);
}

void MainPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    sideMenu_->resize(sideMenu_->geometry().width(), this->geometry().height());
}

void MainPage::onSideMenuRequested()
{
    sideMenu_->show();
    makeMainWidgetVisuallyInactive();
}

void MainPage::onSideMenuLostFocus()
{
    sideMenu_->close();
    makeMainWidgetNormal();
}

void MainPage::setupUi()
{
    sidePanel_        = new SidePanel;
    connect(sidePanel_, &SidePanel::sideMenuRequested, this, &MainPage::onSideMenuRequested);

    conversationSide_ = new ConversationSide;

    splitter_ = new QSplitter;

    splitter_->addWidget(sidePanel_);
    splitter_->addWidget(conversationSide_);

    splitter_->setHandleWidth(1);

    blur_ = new QGraphicsBlurEffect;
    blur_->setBlurRadius(BlurStart);
    splitter_->setGraphicsEffect(blur_);

    QHBoxLayout *hLayout = new QHBoxLayout{this};
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addWidget(splitter_);

    setLayout(hLayout);

    sideMenu_ = new SideMenu{this};
    sideMenu_->hide();

    connect(sideMenu_, &SideMenu::lostFocus, this, &MainPage::onSideMenuLostFocus);
}

void MainPage::makeMainWidgetVisuallyInactive()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurStart);
    blurAnimation->setEndValue(BlurEnd);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(300);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainPage::makeMainWidgetNormal()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurEnd);
    blurAnimation->setEndValue(BlurStart);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(300);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
