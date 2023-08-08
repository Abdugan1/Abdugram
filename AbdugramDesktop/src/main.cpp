#include "application.h"

#include <FramelessHelper/Widgets/framelesswidget.h>
FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[])
{
    FramelessHelper::Widgets::initialize();
    Application app(argc, argv);

    return app.exec();
}
