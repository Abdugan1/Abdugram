#include "ui/mv/messagelistview.h"
#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messagelistdelegate.h"
#include "ui/mv/messageitem.h"
#include "ui/mv/document.h"

#include "ui/components/scrollbar.h"
#include "ui/components/notificationmanager.h"
#include "ui/components/iconbutton.h"
#include "ui/components/colorrepository.h"
#include "ui/components/contextmenu.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/data_structures/messagereads.h>

#include <sql_client/databaseclient.h>

#include <QWindow>
#include <QClipboard>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QPropertyAnimation>
#include <QBoxLayout>
#include <QAbstractTextDocumentLayout>
#include <QApplication>
#include <QPainter>
#include <QDebug>

int prevMaximuim = 0;

MessageTextSelectionHelper::MessageTextSelectionHelper(MessageListView *view)
    : view_{view}
{
    Q_ASSERT(view_);
}

void MessageTextSelectionHelper::handleMousePress(QMouseEvent *event)
{
    if (!leftButtonPressed(event))
        return;

    const QPoint pressedPos        = event->pos();
    const QModelIndex pressedIndex = view_->indexAt(pressedPos);

    if (!isMessageItem(pressedIndex))
        return;

    pressedPos_           = pressedPos;
    previousPressedIndex_ = pressedIndex_;
    pressedIndex_         = pressedIndex;

    if (pressedIndex_ != previousPressedIndex_) {
        // Repaint previous pressed as static text. Means no selection draws
        view_->update(previousPressedIndex_);
    }

    const QString text = pressedIndex_.data(MessageItem::Text).toString();

    QSharedPointer<Document> doc{new Document};
    doc->setPlainText(text);

    const int startPos = relativeTextCursorPos(doc, pressedIndex_, pressedPos_);
    doc->setCursorPosition(startPos);

    view_->delegate_->setInteractiveIndex(pressedIndex_);
    view_->delegate_->setDoc(doc);

    wordSelection_ = false;
}

void MessageTextSelectionHelper::handleMouseMove(QMouseEvent *event)
{
    if (!leftButtonPressed(event) && !isMessageItem(pressedIndex_))
        return;

    const QPoint currentMousePos = event->pos();

    QSharedPointer<Document> doc = view_->delegate_->doc();

    const int endPos = relativeTextCursorPos(doc, pressedIndex_, currentMousePos);

    if (wordSelection_) {
        doc->extendWordwiseSelection(endPos);
    } else {
        doc->setCursorPosition(endPos, QTextCursor::KeepAnchor);
    }

    view_->update(pressedIndex_);
}

void MessageTextSelectionHelper::handleMouseDoubleClick(QMouseEvent *event)
{
    if (!leftButtonPressed(event) && !isMessageItem(pressedIndex_))
        return;

    const QPoint currentMousePos = event->pos();
    QSharedPointer<Document> doc = view_->delegate_->doc();

    doc->select(QTextCursor::WordUnderCursor);

    view_->update(pressedIndex_);

    wordSelection_ = true;
}

bool MessageTextSelectionHelper::leftButtonPressed(const QMouseEvent *event) const
{
    return event->buttons() & Qt::LeftButton;
}

bool MessageTextSelectionHelper::isMessageItem(const QModelIndex &index) const
{
    return index.data(MessageModelItem::Roles::Type).toInt() == MessageModelItem::Type::MessageItem;
}

int MessageTextSelectionHelper::relativeTextCursorPos(const QSharedPointer<Document> &doc,
                                                      const QModelIndex &index,
                                                      const QPoint &mousePos) const
{
    const bool  senderIsMe = (index.data(MessageItem::SenderId) == networkHandler()->userId());
    const int   hSpacing   = view_->delegate_->messageHSpacing();
    const int   vSpacing   = view_->delegate_->messageVSpacing();

    const QMargins padding{hSpacing, vSpacing, hSpacing, vSpacing};

    const QRect itemRect  = view_->visualRect(index).marginsRemoved(padding);
    QRect bgRect    = index.data(MessageItem::BackgroundRect).toRect().translated(itemRect.topLeft());

    if (senderIsMe) {
        bgRect.translate(itemRect.width() - bgRect.width(), 0);
    }

    const QRect textRect  = index.data(MessageItem::TextRect).toRect();

    QPoint relativePos = mousePos - (bgRect.topLeft() + textRect.topLeft());
    if (senderIsMe) {
        //        relativePos.rx() -=
    }
    return doc->documentLayout()->hitTest(relativePos, Qt::FuzzyHit);
}

MessageListViewContextMenuHelper::MessageListViewContextMenuHelper(MessageListView *view)
    : view_{view}
{
    Q_ASSERT(view_);

    initContextMenus();
}

void MessageListViewContextMenuHelper::popup(const QModelIndex &indexUnderMouse, const QPoint &pos)
{
    lastIndex_ = indexUnderMouse;

    const int type = indexUnderMouse.data(MessageModelItem::Roles::Type).toInt();
    if (type == MessageModelItem::MessageItem) {
        contextMenu_->openMenu(pos);
    }
}

void MessageListViewContextMenuHelper::initContextMenus()
{
    contextMenu_ = new ContextMenu{view_};

    copyAction_ = new QAction{QIcon{":/images/copy.png"}, "Copy", contextMenu_};
    QObject::connect(copyAction_, &QAction::triggered, [this]()->void {
        const QString text = lastIndex_.data(MessageItem::Text).toString();
        qApp->clipboard()->setText(text);
    });

    contextMenu_->addAction(copyAction_);
}


MessageListView::MessageListView(QWidget *parent)
    : QListView{parent}
    , model_{new MessageListModel{this}}
    , delegate_{new MessageListDelegate{this}}
    , textSelectionHelper_{new MessageTextSelectionHelper{this}}
    , contextMenuHelper_{new MessageListViewContextMenuHelper{this}}
{
    setupUi();

    connect(networkHandler(), &NetworkHandler::syncFinished, this, &MessageListView::onSyncFinished);
    connect(networkHandler(), &NetworkHandler::loggedOut, this, &MessageListView::onLoggedOut);

    connect(verticalScrollBar(), &ScrollBar::valueChanged, this, &MessageListView::onScrollChanged);
    connect(verticalScrollBar(), &ScrollBar::rangeChanged, this, &MessageListView::onScrollRangeChanged);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &MessageListView::onContextMenuRequested);

    prevMaximuim = verticalScrollBar()->maximum();
}

void MessageListView::setChatId(int chatId)
{
    delegate_->setDoc(nullptr);
    delegate_->setInteractiveIndex(QModelIndex{});

    const int prevVal = verticalScrollBar()->value();

    model_->setChatId(chatId);
    scrollToBottom();

    if (verticalScrollBar()->value() == prevVal)
        readMessages();

    notificationManager()->removeNotificationsWithChatId(chatId);
}

void MessageListView::setChatIdWithoutSelect(int chatId)
{
    delegate_->setDoc(nullptr);
    delegate_->setInteractiveIndex(QModelIndex{});

    const int prevVal = verticalScrollBar()->value();

    model_->setChatIdWithoutSelect(chatId);
    scrollToBottom();

    if (verticalScrollBar()->value() == prevVal)
        readMessages();

    notificationManager()->removeNotificationsWithChatId(chatId);
}

void MessageListView::mousePressEvent(QMouseEvent *event)
{
    textSelectionHelper_->handleMousePress(event);

    QListView::mousePressEvent(event);
}

void MessageListView::mouseMoveEvent(QMouseEvent *event)
{
    textSelectionHelper_->handleMouseMove(event);

    QListView::mouseMoveEvent(event);
}

void MessageListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    textSelectionHelper_->handleMouseDoubleClick(event);

    QListView::mouseDoubleClickEvent(event);
}

void MessageListView::onSyncFinished()
{
    connect(model_, &MessageListModel::messageAdded, this, &MessageListView::onMessageAdded);
    connect(database(), &DatabaseClient::messageAdded, this, &MessageListView::showNotificationIfMessageIdIsNotCurrent);
}

void MessageListView::onLoggedOut()
{
    disconnect(model_, &MessageListModel::messageAdded, this, &MessageListView::onMessageAdded);
    disconnect(database(), &DatabaseClient::messageAdded, this, &MessageListView::showNotificationIfMessageIdIsNotCurrent);
}

void MessageListView::onMessageAdded(const Message &message)
{
    lastMessage_ = message;
}

void MessageListView::scrollToEndIfNeccessary(const Message &message)
{
    if (autoScroll_ || message.senderId() == networkHandler()->userId()) {
        scrollToBottom();
        readMessages();
    }
}

void MessageListView::showNotificationIfMessageIdIsNotCurrent(const Message &message)
{
    if (message.senderId() == networkHandler()->userId() || message.chatId() == model_->chatId())
        return;

    emit notificationRequested(message);

    notificationManager()->addNotification(message);
}

void MessageListView::onScrollChanged(int value)
{
    const int maxVal = verticalScrollBar()->maximum();
    scrollToBottomButton_->setVisible(maxVal - value > 1000);

    readMessages();
}

void MessageListView::onScrollRangeChanged(int min, int max)
{
    int value = verticalScrollBar()->value();
    autoScroll_ = ((value == prevMaximuim) || (value == max));
    prevMaximuim = max;

    if (lastMessage_.chatId() == model_->chatId()) {
        scrollToEndIfNeccessary(lastMessage_);
    }
}

void MessageListView::smoothScrollToBottom()
{
    auto scrollbar = verticalScrollBar();
    QPropertyAnimation *scrollAnimation = new QPropertyAnimation{scrollbar, "value"};
    scrollAnimation->setStartValue(scrollbar->value());
    scrollAnimation->setEndValue(scrollbar->maximum());
    scrollAnimation->setDuration(210);
    scrollAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    scrollAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MessageListView::onContextMenuRequested(const QPoint &pos)
{
    const QModelIndex index = indexAt(pos);
    const int type = index.data(MessageModelItem::Roles::Type).toInt();

    if (type == MessageModelItem::MessageItem) {
        contextMenuHelper_->popup(index, viewport()->mapToGlobal(pos));
    }
}

void MessageListView::setupUi()
{
    setModel(model_);
    setItemDelegate(delegate_);

    scrollToBottomButton_ = new IconButton{QPixmap{":/images/down_arrow.png"}};
    scrollToBottomButton_->setBackgroundColor(Colors.value(colornames::backgroundLighterHelper2));
    scrollToBottomButton_->setFixedSize(QSize{40, 40});
    scrollToBottomButton_->setVisible(false);
    connect(scrollToBottomButton_, &IconButton::clicked, this, &MessageListView::smoothScrollToBottom);

    auto vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 14, 14);
    vLayout->setSpacing(0);
    vLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Maximum, QSizePolicy::Expanding});
    vLayout->addWidget(scrollToBottomButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(vLayout);

    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBar(new ScrollBar{Qt::Vertical, this});
    setFocusPolicy(Qt::NoFocus);

    setContentsMargins(0, 0, 0, 0);
}

void MessageListView::scrollToEnd()
{
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

void MessageListView::readMessages()
{
    if (!qApp->activeWindow())
        return;

    if (!verticalScrollBar()->isVisible()) {
        readMessagesFromRow(model_->rowCount(QModelIndex{}) - 1);
    } else {
        const QRect r = rect();
        QPoint readPoint{r.center().x(), r.bottom() - 10};
        readMessagesFromRow(indexAt(readPoint).row());
    }
}

void MessageListView::readMessagesFromRow(int row)
{
    QList<MessageRead> messageReads;
    for (int i = row; i >= 0; i--) {
        const auto index = model_->index(i);
        const int type = index.data(MessageModelItem::Roles::Type).toInt();
        if (type != MessageModelItem::Type::MessageItem)
            continue;

        const int senderId = index.data(MessageItem::SenderId).toInt();
        if (senderId == networkHandler()->userId())
            continue;

        const bool isRead = index.data(MessageItem::IsRead).toBool();
        if (isRead)
            break;

        const int messageId = index.data(MessageItem::MessageId).toInt();

        MessageRead messageRead;
        messageRead.setUserId(networkHandler()->userId());
        messageRead.setMessageId(messageId);

        messageReads.append(messageRead);
    }

    if (!messageReads.isEmpty())
        networkHandler()->sendMessageReadRequest(messageReads);
}

int MessageListView::getRelativeCursorPos(const QSharedPointer<Document> &doc,
                                          const QModelIndex &index,
                                          const QPoint &mousePos) const
{
    const bool  senderIsMe = (index.data(MessageItem::SenderId) == networkHandler()->userId());
    const int   hSpacing   = delegate_->messageHSpacing();
    const int   vSpacing   = delegate_->messageVSpacing();

    const QMargins padding{hSpacing, vSpacing, hSpacing, vSpacing};

    const QRect itemRect  = visualRect(index).marginsRemoved(padding);
    QRect bgRect    = index.data(MessageItem::BackgroundRect).toRect().translated(itemRect.topLeft());

    if (senderIsMe) {
        bgRect.translate(itemRect.width() - bgRect.width(), 0);
    }

    const QRect textRect  = index.data(MessageItem::TextRect).toRect();

    QPoint relativePos = mousePos - (bgRect.topLeft() + textRect.topLeft());
    if (senderIsMe) {
//        relativePos.rx() -=
    }
    return doc->documentLayout()->hitTest(relativePos, Qt::FuzzyHit);
}
