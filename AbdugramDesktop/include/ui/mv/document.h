#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QTextDocument>
#include <QTextCursor>

class Document : public QTextDocument
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);

    int selectionStartPos() const;

    int selectionEndPos()   const;

    void setCursorPosition(int pos, QTextCursor::MoveMode mode = QTextCursor::MoveAnchor);

    bool moveCursorPosition(QTextCursor::MoveOperation op,
                            QTextCursor::MoveMode mm= QTextCursor::MoveAnchor,
                            int n = 1);

    void select(QTextCursor::SelectionType selection);

    void extendWordwiseSelection(int newPos);

    QString selectedText() const;


private:
    void clearSelection();

    void highlightSelection();

private:
    QTextCursor textCursor_;
    QTextCursor selectedWordOnDoubleClick_;
};


#endif // DOCUMENT_H
