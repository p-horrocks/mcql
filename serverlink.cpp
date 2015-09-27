#include "serverlink.h"

ServerLink::ServerLink()
{
    startTimer(1000);
}

void ServerLink::timerEvent(QTimerEvent *)
{
    static int c = 0;
    auto str = QString("output %1").arg(c++);
    emit output(str);
}
