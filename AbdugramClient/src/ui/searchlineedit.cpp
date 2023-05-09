#include "searchlineedit.h"
#include <QTimer>

#include "net/networkhandler.h"

#include <net_common/messages/searchonservermessage.h>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : LineEdit{parent}
    , searchServerTimer_{new QTimer}
{
    searchServerTimer_->setInterval(200);
    searchServerTimer_->setSingleShot(true);

    connect(this, &SearchLineEdit::textEdited, this, [this]() {
        if (!text().isEmpty()) {
            searchServerTimer_->start();
        } else {
            searchServerTimer_->stop();
            emit searchIsEmpty();
        }
    });

    connect(searchServerTimer_, &QTimer::timeout, this, &SearchLineEdit::searchOnServer);
}

void SearchLineEdit::searchOnServer()
{
    if (!networkHandler()->isConnected())
        return;

    AnyMessagePtr<SearchOnServerMessage> searchOnServerMessage{new SearchOnServerMessage{}};
    searchOnServerMessage->setSearchText(text());
    networkHandler()->sendToServer(static_cast<AbduMessagePtr>(searchOnServerMessage));
}
