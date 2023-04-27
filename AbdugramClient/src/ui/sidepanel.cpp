#include "sidepanel.h"
#include "imagebutton.h"
#include "searchlineedit.h"
#include "mv/chatlistview.h"

#include <QBoxLayout>

SidePanel::SidePanel(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(searchLineEdit_, &SearchLineEdit::searchOnServerRequested,
            this,            &SidePanel::searchOnServerRequested);

    connect(searchLineEdit_, &SearchLineEdit::searchOnLocalRequested,
            this,            &SidePanel::searchOnLocalRequested);
}

void SidePanel::setupUi()
{
    openDrawer_ = new ImageButton{QPixmap{":/images/drawer_button.png"}};
    searchLineEdit_ = new SearchLineEdit;
    searchLineEdit_->setPlaceholderText(tr("Search"));

    QHBoxLayout *hLayout = new QHBoxLayout;
    const int m = 8;
    hLayout->setContentsMargins(m, m, m, m);
    hLayout->setSpacing(m);
    hLayout->addWidget(openDrawer_);
    hLayout->addWidget(searchLineEdit_);

    chatListView_ = new ChatListView;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(chatListView_);

    setLayout(vLayout);
}
