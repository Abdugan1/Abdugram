#include "searchlineedit.h"
#include <QTimer>

#include "net/networkhandler.h"

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
    const QString searchText = text();
    networkHandler()->sendSearchRequest(searchText);
}
