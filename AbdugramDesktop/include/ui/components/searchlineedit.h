#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QLineEdit>

#include <net_common/messages/abdumessage.h>

class QTimer;

class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchLineEdit(QWidget *parent = nullptr);

signals:
    void searchIsEmpty();

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void startSearchOnServer();

private slots:
    void onTextEdited(const QString &text);

private slots:
    void searchOnLocal();
    void searchOnServer();

private:
    QTimer *localSearchTimer_  = nullptr;
    QTimer *serverSearchTimer_ = nullptr;
};

#endif // SEARCHLINEEDIT_H
