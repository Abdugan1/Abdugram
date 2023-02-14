#ifndef LOGSVIEWPAGE_H
#define LOGSVIEWPAGE_H

#include "titledwindow.h"

#include <vector>
#include <fstream>

class LogsViewPage : public TitledWindow
{
public:
    explicit LogsViewPage(const std::string &fileName);

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

    std::ifstream file_;
    std::string fileName_;
};

#endif // LOGSVIEWPAGE_H
