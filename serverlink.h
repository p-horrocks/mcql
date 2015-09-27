#ifndef SERVERLINK_H
#define SERVERLINK_H

#include <QObject>

class ServerLink :
        public QObject
{
    Q_OBJECT

public:
    ServerLink();

signals:
    void output(const QString& text);

protected:
    virtual void timerEvent(QTimerEvent *);
};

#endif // SERVERLINK_H
