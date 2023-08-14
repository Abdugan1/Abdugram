#include "ui/pages/mainpage.h"

#include "ui/components/sidemenu.h"
#include "ui/components/chatlistside.h"
#include "ui/components/conversationside.h"

#include <QPropertyAnimation>
#include <QGraphicsBlurEffect>
#include <QSplitter>
#include <QHBoxLayout>
#include <QMoveEvent>
#include <QResizeEvent>
#include <QDebug>

const auto BlurStart = 1.0;
const auto BlurEnd   = 2.0;

MainPage::MainPage(QWidget *parent)
    : Widget{parent}
{
    setupUi();
    
    connect(chatListSide_, &ChatListSide::selectionWasChanged, conversationSide_, &ConversationSide::setCurrentChatItem);
    connect(chatListSide_, &ChatListSide::newChatItemAdded,    conversationSide_, &ConversationSide::updateCurrentChatIfAddedChatIsEqualToAdded);

    connect(conversationSide_, &ConversationSide::addedChatWasCurrent, chatListSide_, &ChatListSide::setToMainModelAndSelectChat);
    connect(conversationSide_, &ConversationSide::escapePressed, this, &MainPage::unselectChat);
}

void MainPage::resizeEvent(QResizeEvent *event)
{
    Widget::resizeEvent(event);
    sideMenu_->resize(sideMenu_->width(), this->geometry().height());
}

void MainPage::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        unselectChat();
    }
    Widget::keyPressEvent(event);
}

void MainPage::setupUi()
{
    sideMenu_ = new SideMenu{this};

    connect(sideMenu_, &SideMenu::aboutToShow, this, &MainPage::makeMainWidgetVisuallyInactive);
    connect(sideMenu_, &SideMenu::aboutToClose, this, &MainPage::makeMainWidgetNormal);

    chatListSide_        = new ChatListSide;
    connect(chatListSide_, &ChatListSide::sideMenuRequested, sideMenu_, &SideMenu::show);

    conversationSide_ = new ConversationSide;

    splitter_ = new QSplitter;

    splitter_->addWidget(chatListSide_);
    splitter_->addWidget(conversationSide_);

    splitter_->setHandleWidth(1);

    const QList<int> sizes{width() * 1/3, width() * 2/3};
    splitter_->setSizes(sizes);

    blur_ = new QGraphicsBlurEffect;
    blur_->setBlurRadius(BlurStart);
    splitter_->setGraphicsEffect(blur_);

    QHBoxLayout *hLayout = new QHBoxLayout{this};
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addWidget(splitter_);

    setLayout(hLayout);
}

void MainPage::unselectChat()
{
    conversationSide_->unsetCurrentChatItem();
    chatListSide_->clearChatSelection();
}

void MainPage::makeMainWidgetVisuallyInactive()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurStart);
    blurAnimation->setEndValue(BlurEnd);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(100);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainPage::makeMainWidgetNormal()
{
    QPropertyAnimation *blurAnimation = new QPropertyAnimation{blur_, "blurRadius"};
    blurAnimation->setStartValue(BlurEnd);
    blurAnimation->setEndValue(BlurStart);
    blurAnimation->setEasingCurve(QEasingCurve::OutQuint);
    blurAnimation->setDuration(100);

    blurAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
