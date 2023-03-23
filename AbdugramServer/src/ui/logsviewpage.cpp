#include "logsviewpage.h"

#include <QDebug>

LogsViewPage::LogsViewPage(LogFilePtr &logFile)
    : TitledWindow{"Logs View"}
    , logFile_{logFile}
{
    updateBuffer();
    currentMaxLen_ = getCurrentMaxLen();
    updateView();
}


void LogsViewPage::parseInput(int input)
{
    int w = workingWindow()->width();
    int h = workingWindow()->height();
    int l = currentMaxLen_;

    int prevVPos = vPos_;
    int prevHPos = hPos_;

    switch (input) {
    case KEY_UP:
        vPos_ = std::max(vPos_ - 1, 0);
        break;
    case KEY_DOWN:
        vPos_ = std::min(vPos_ + 1, int(lines_.size()) - h);
        vPos_ = std::max(vPos_, 0);
        break;

    case KEY_LEFT:
        hPos_ = std::max(hPos_- 2, 0);
        break;
    case KEY_RIGHT:
        hPos_ = std::min(hPos_ + 2, l - w);
        vPos_ = std::max(vPos_, 0);
        break;

    case KEY_BACKSPACE:
        choiceParse_(this, "quit");
        break;

    case KEY_PPAGE: // Page Up
        vPos_ = 0;
        break;
    case KEY_NPAGE: // Page Down
        vPos_ = std::max(int(lines_.size() - h), 0);
        break;

    case KEY_HOME:
        hPos_ = 0;
        break;

    case KEY_END:
        hPos_ = std::max(l - w, 0);
        break;
    }

    if (vPos_ != prevVPos) {
        currentMaxLen_ = getCurrentMaxLen();
    }

    if (vPos_ != prevVPos || hPos_ != prevHPos) {
        updateView();
    }
}

void LogsViewPage::updateView()
{
    WindowPtr w = rworkingWindow();
    w->clear();

    int viewBottom = std::min(vPos_ + w->height(), int(lines_.size()));
    int y = 0;
    for (int i = vPos_; i < viewBottom; ++i) {
        int len = lines_[i].size();
        int outLeft  = std::min(hPos_, len);
        int inside   = len - outLeft;
        int outRight = (inside > w->width() ? inside - w->width() : 0);
        std::string middle = lines_[i].substr(outLeft, len - outLeft - outRight);
        w->print(0, y++, middle);
    }
}

void LogsViewPage::updateBuffer()
{
    QMutexLocker lock{&logFile_->mutex()};
    logFile_->moveToBegin();

    lines_.clear();
    lines_.reserve(512);
    std::string str;
    while (!logFile_->atEnd()) {
        str = logFile_->readLine().toStdString();
        lines_.push_back(str);
    }
    lines_.shrink_to_fit();

    updateView();
}

int LogsViewPage::getCurrentMaxLen()
{
    if (lines_.empty())
        return 0;

    int viewTop    = vPos_;
    int viewBottom = std::min(vPos_ + workingWindow()->height(), int(lines_.size()));

    auto begin = lines_.begin() + viewTop;
    auto end   = lines_.begin() + viewBottom + 1;

    return std::max_element(begin, end,
                             [](const std::string &s1, const std::string &s2) {
        return s1.length() < s2.length();
    })
            ->length();
}
