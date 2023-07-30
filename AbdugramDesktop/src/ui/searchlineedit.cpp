#include "ui/searchlineedit.h"
#include <QTimer>

#include "net/networkhandler.h"

#include <sql_client/databaseclient.h>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : LineEdit{parent}
    , localSearchTimer_{new QTimer}
    , serverSearchTimer_{new QTimer}
{
    localSearchTimer_->setInterval(50);
    localSearchTimer_->setSingleShot(true);

    serverSearchTimer_->setInterval(100);
    serverSearchTimer_->setSingleShot(true);

    connect(this, &SearchLineEdit::textEdited, this, &SearchLineEdit::onTextEdited);

    connect(localSearchTimer_, &QTimer::timeout, this, &SearchLineEdit::searchOnLocal);

    connect(serverSearchTimer_, &QTimer::timeout, this, &SearchLineEdit::searchOnServer);
}

void SearchLineEdit::startSearchOnServer()
{
    if (text().length() < 4)
        return;
    serverSearchTimer_->start();
}

void SearchLineEdit::onTextEdited(const QString &text)
{
    if (!text.isEmpty()) {
        localSearchTimer_->start();
        serverSearchTimer_->stop();
    } else {
        localSearchTimer_->stop();
        emit searchIsEmpty();
    }
}

void SearchLineEdit::searchOnLocal()
{
    database()->likeSearch('%' + text() + '%');
}
void SearchLineEdit::searchOnServer()
{
    networkHandler()->sendSearchRequest(text());
}
