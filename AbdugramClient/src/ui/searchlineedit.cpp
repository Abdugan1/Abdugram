#include "searchlineedit.h"
#include <QTimer>

#include <net_common/messages/searchonservermessage.h>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : LineEdit{parent}
    , searchServerTimer_{new QTimer}
{
    searchServerTimer_->setInterval(200);
    searchServerTimer_->setSingleShot(true);

    connect(this, &SearchLineEdit::textEdited, this, [this]() {
        searchServerTimer_->start();
    });

    connect(searchServerTimer_, &QTimer::timeout, this, [this]() {
        AnyMessagePtr<SearchOnServerMessage> searchOnServerMessage{new SearchOnServerMessage{}};
        searchOnServerMessage->setSearchText(text());
        emit searchOnServerRequested(static_cast<AbduMessagePtr>(searchOnServerMessage));
    });
    connect(this, &SearchLineEdit::textEdited, this, &SearchLineEdit::searchOnLocalRequested);
}
