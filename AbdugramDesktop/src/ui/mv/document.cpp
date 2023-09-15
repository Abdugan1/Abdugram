#include "ui/mv/document.h"

#include <QApplication>
#include <QPalette>

Document::Document(QObject *parent)
    : QTextDocument{parent}
    , textCursor_{this}
{
    setDocumentMargin(0);
}

int Document::selectionStartPos() const
{
    return textCursor_.selectionStart();
}

int Document::selectionEndPos() const
{
    return textCursor_.selectionEnd();
}

void Document::setCursorPosition(int pos, QTextCursor::MoveMode mode)
{
    clearSelection();
    textCursor_.setPosition(pos, mode);
    highlightSelection();
}

bool Document::moveCursorPosition(QTextCursor::MoveOperation op, QTextCursor::MoveMode mm, int n)
{
    clearSelection();
    const bool result = textCursor_.movePosition(op, mm, n);
    highlightSelection();
    return result;
}

void Document::select(QTextCursor::SelectionType selection)
{
    clearSelection();
    textCursor_.select(selection);
    selectedWordOnDoubleClick_ = textCursor_;
    highlightSelection();
}

void Document::extendWordwiseSelection(int newPos)
{
    QTextCursor selected   = textCursor_;
    QTextCursor tempCursor = textCursor_;
    tempCursor.setPosition(newPos, QTextCursor::KeepAnchor);

    if (!tempCursor.movePosition(QTextCursor::StartOfWord))
        return;

    const int wordStartPos = tempCursor.position();

    if (!tempCursor.movePosition(QTextCursor::EndOfWord))
        return;

    const int wordEndPos = tempCursor.position();

    if (newPos < selectedWordOnDoubleClick_.position()) {
        setCursorPosition(selected.selectionEnd());
        setCursorPosition(wordStartPos, QTextCursor::KeepAnchor);
    } else {
        setCursorPosition(selected.selectionStart());
        setCursorPosition(wordEndPos, QTextCursor::KeepAnchor);
    }
}

QString Document::selectedText() const
{
    return textCursor_.selectedText();
}

void Document::clearSelection()
{
    QTextCharFormat defaultFormat;
    textCursor_.setCharFormat(defaultFormat);
}

void Document::highlightSelection()
{
    QTextCharFormat selectFormat = textCursor_.charFormat();
    selectFormat.setBackground(QApplication::palette().highlight().color());
    selectFormat.setForeground(QApplication::palette().highlightedText().color());

    textCursor_.setCharFormat(selectFormat);
}
