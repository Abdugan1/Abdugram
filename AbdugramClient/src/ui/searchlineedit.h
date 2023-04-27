#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include "lineedit.h"

#include <net_common/messages/abdumessage.h>

class QTimer;

class SearchLineEdit : public LineEdit
{
    Q_OBJECT
public:
    explicit SearchLineEdit(QWidget *parent = nullptr);

signals:
    void searchOnServerRequested(const AbduMessagePtr &searchOnServerMessage);
    void searchOnLocalRequested(const QString &text);

private:
    QTimer *searchServerTimer_ = nullptr;
};

#endif // SEARCHLINEEDIT_H
