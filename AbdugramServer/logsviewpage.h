#ifndef LOGSVIEWPAGE_H
#define LOGSVIEWPAGE_H

#include "titledwindow.h"

#include <logger/logfile.h>

#include <vector>
#include <fstream>

class LogsViewPage : public TitledWindow
{
public:
    explicit LogsViewPage(LogFilePtr &logFile);

    void parseInput(int input) override;

    void updateBuffer();

private:
    void updateView();
    int getCurrentMaxLen();

private:
    std::vector<std::string> lines_;
    int vPos_ = 0;
    int hPos_ = 0;
    int currentMaxLen_ = 0;

    LogFilePtr logFile_;
};

#endif // LOGSVIEWPAGE_H
