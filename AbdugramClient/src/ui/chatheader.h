#ifndef CHATHEADER_H
#define CHATHEADER_H

#include <QFrame>

class MainLabel;
class SecondaryLabel;

class ChatHeader : public QFrame
{
    Q_OBJECT
public:
    explicit ChatHeader(QWidget *parent = nullptr);

    void setChatName(const QString &text);

signals:

private slots:
    void setLastOnlineLabelAsConnecting();
    void requestLastOnlineTimeOfCurrentUser();

private:
    void setupUi();

private:
    MainLabel       *chatName_          = nullptr;
    SecondaryLabel  *lastOnlineLabel_   = nullptr;
};

#endif // CHATHEADER_H
