#include "ui/components/searchlineedit.h"

#include "ui/components/colorrepository.h"

#include "net/networkhandler.h"

#include <sql_client/databaseclient.h>

#include <QPainter>
#include <QTimer>

inline QColor backgroundColor()
{
    return Colors.value(colornames::backgroundLighterHelper5);
}

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit{parent}
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


    // Own frame will be draw in paintEvent
    setFrame(false);

    QPalette p = palette();
    p.setColor(QPalette::Base, backgroundColor());
    p.setColor(QPalette::PlaceholderText, Colors.value(colornames::secondaryLabelColor));
    p.setColor(QPalette::Highlight, Colors.value(colornames::decorationColor));
    setPalette(p);
}

void SearchLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
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
