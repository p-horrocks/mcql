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
    Q_PROPERTY(bool        running    READ running                       NOTIFY runningChanged)
    Q_PROPERTY(PlayerList* playerList READ playerList                    CONSTANT)

public:
    ServerLink();

    const QString& worldName() const { return worldName_; }
    void setWorldName(const QString& name);

    bool running() const { return running_; }
    PlayerList* playerList() { return &playerList_; }

    Q_INVOKABLE void sendInput(const QString& input);
    Q_INVOKABLE void stopServer();

protected slots:
    void readProcessStdout();
    void onStateChange(QProcess::ProcessState state);

signals:
    void worldNameChanged();
    void runningChanged();

    void output(const QString& text);

protected:
    void startServer();

    QString    worldName_;
    bool       running_;
    QProcess   serverProcess_;
    PlayerList playerList_;
};

#endif // SERVERLINK_H
