#include "ui/components/phonelineedit.h"
#include "ui/components/mainlabel.h"
#include "ui/components/regexes.h"

#include <QBoxLayout>
#include <QKeyEvent>
#include <QRegularExpressionValidator>
#include <QDebug>

inline bool isKeyDigit(int key)
{
    return key >= Qt::Key_0 && key <= Qt::Key_9;
}

PhoneLineEdit::PhoneLineEdit()
    : FieldLineEdit{"─── ─── ── ──"}
    , phoneCode_{new MainLabel{"+7"}}
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(phoneCode_, 0, Qt::AlignLeft | Qt::AlignVCenter);
    hLayout->addSpacerItem(new QSpacerItem{1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum});

    setLayout(hLayout);

    // TODO: Make font monospace
    QFont f = font();
    f.setStyleHint(QFont::TypeWriter);
    setFont(f);

    QMargins tm = textMargins();
    QFontMetrics fm{f};
    tm.setLeft(fm.horizontalAdvance(phoneCode_->text() + " "));

    setTextMargins(tm);

    setValidator(new QRegularExpressionValidator{ui::regex::PhoneRegex});
}

QString PhoneLineEdit::getPhone() const
{
    return "+7" + text().replace(" ", "");
}

void PhoneLineEdit::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() != Qt::Key_Delete)
            && (event->key() != Qt::Key_Backspace)
            && !(isKeyDigit(event->key()))) {
        return;
    }

    if (isKeyDigit(event->key()) && text().length() >= 13) {
        return;
    }
    
    FieldLineEdit::keyPressEvent(event);

    const QString textWithoutSpace = text().remove(" ");
    QString resultText = textWithoutSpace;

    int length = textWithoutSpace.length();
    int spaceCount = 0;
    if (length > 3)
        resultText.insert(3 + (spaceCount++), " ");
    if (length > 6)
        resultText.insert(6 + (spaceCount++), " ");
    if (length > 8)
        resultText.insert(8 + (spaceCount++), " ");

    int curPos = cursorPosition();
    bool stayCurPos = curPos != text().length();
    setText(resultText);
    if (stayCurPos)
        setCursorPosition(curPos);
}
