#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QMenu>
#include <QScopedPointer>

class ContextMenuPrivate;
class ContextMenu : public QMenu
{
    Q_OBJECT

    Q_DECLARE_PRIVATE(ContextMenu);
public:
    explicit ContextMenu(QWidget *parent = nullptr);
    ~ContextMenu();

    void openMenu(const QPoint &pos);
    void closeMenu();

protected:
    void closeEvent(QCloseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

protected:
    const QScopedPointer<ContextMenuPrivate> d_ptr;
};

#endif // CONTEXTMENU_H
