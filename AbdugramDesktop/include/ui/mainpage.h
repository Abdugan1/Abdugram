#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

class QFrame;
class QSplitter;

class QGraphicsBlurEffect;

class SideMenu;
class SidePanel;
class ConversationSide;

class MainPage : public QWidget
{
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onSideMenuRequested();
    void onSideMenuLostFocus();

private:
    void setupUi();
    void makeMainWidgetVisuallyInactive();
    void makeMainWidgetNormal();

private:
    QSplitter        *splitter_         = nullptr;
    SidePanel        *sidePanel_        = nullptr;
    ConversationSide *conversationSide_ = nullptr;

    SideMenu *sideMenu_ = nullptr;

    QGraphicsBlurEffect *blur_ = nullptr;
};

#endif // MAINPAGE_H
