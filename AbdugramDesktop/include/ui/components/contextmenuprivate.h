#ifndef CONTEXTMENUPRIVATE_H
#define CONTEXTMENUPRIVATE_H

#include <QtGlobal>
#include <QStateMachine>
#include <QColor>
#include <QSize>

class ContextMenu;
class ContextMenuStateMachine;

class ContextMenuPrivate
{
    Q_DECLARE_PUBLIC(ContextMenu)
public:
    ContextMenuPrivate(ContextMenu *q);

    void init();

    void openMenu(const QPoint &pos);
    void closeMenu();

    ContextMenu *const q_ptr;

public:
    ContextMenuStateMachine *stateMachine;

    bool canClose = false;

    QColor backgroundColor;
    QColor textColor;
    QColor highlightColor;

    int cornerRadius = 0;

    int itemHeight = 0;

    int leftMargin = 0;
    int spacing    = 0;

    QSize iconSize;
};

class ContextMenuStateMachine : public QStateMachine
{
    Q_OBJECT
public:
    explicit ContextMenuStateMachine(ContextMenu *contextMenu);

    void updatePropertyAssignments();

signals:
    void open();
    void close();

    void closed();

private:
    ContextMenu *const contextMenu_;

    QState *const openedState_;
    QState *const closedState_;
};

#endif // CONTEXTMENUPRIVATE_H
