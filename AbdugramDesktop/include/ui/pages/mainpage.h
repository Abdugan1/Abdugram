#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "ui/components/widget.h"

class QFrame;
class QSplitter;

class QGraphicsBlurEffect;

class Drawer;
class SettingsWindow;
class ChatListSide;
class ConversationSide;

class MainPage : public Widget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void makeMainWidgetVisuallyInactive();
    void makeMainWidgetNormal();
    void unselectChat();

private:
    void setupUi();

private:
    QSplitter        *splitter_         = nullptr;
    ChatListSide     *chatListSide_     = nullptr;
    ConversationSide *conversationSide_ = nullptr;
    
    Drawer *drawer_ = nullptr;
    SettingsWindow *settingsWindow_ = nullptr;

    QGraphicsBlurEffect *blur_ = nullptr;
};

#endif // MAINPAGE_H
