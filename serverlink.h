#ifndef SERVERLINK_H
#define SERVERLINK_H

#include <QObject>
#include <QProcess>

#include "playerlist.h"

class ServerLink :
        public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString     worldName  READ worldName  WRITE setWorldName NOTIFY worldNameChanged)
    Q_PROPERTY(PlayerList* playerList READ playerList                    CONSTANT)

public:
    ServerLink();

    const QString& worldName() const { return worldName_; }
    void setWorldName(const QString& name);

    PlayerList* playerList() { return &playerList_; }

protected slots:
    void readProcessStdout();

signals:
    void worldNameChanged();

    void output(const QString& text);

protected:
    void startServer();

    QString    worldName_;
    QProcess   serverProcess_;
    PlayerList playerList_;
};

#endif // SERVERLINK_H
