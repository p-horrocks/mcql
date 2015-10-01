#ifndef SERVERLINK_H
#define SERVERLINK_H

#include <QObject>
#include <QProcess>

#include "mcqlutil.h"
#include "playerlist.h"

class ServerLink :
        public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString              worldName  READ worldName  WRITE setWorldName  NOTIFY worldNameChanged)
    Q_PROPERTY(bool                 running    READ running                        NOTIFY runningChanged)
    Q_PROPERTY(PlayerList*          playerList READ playerList                     CONSTANT)
    Q_PROPERTY(McqlUtil::Difficulty difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)

public:
    ServerLink();

    const QString& worldName() const { return worldName_; }
    void setWorldName(const QString& name);

    bool running() const { return running_; }
    PlayerList* playerList() { return &playerList_; }

    McqlUtil::Difficulty difficulty() const { return difficulty_; }
    void setDifficulty(McqlUtil::Difficulty d);

    Q_INVOKABLE void sendInput(const QString& input);
    Q_INVOKABLE void stopServer();

protected slots:
    void readProcessStdout();
    void onStateChange(QProcess::ProcessState state);

signals:
    void worldNameChanged();
    void runningChanged();
    void difficultyChanged();

    void output(const QString& text);

protected:
    void _setDifficulty(McqlUtil::Difficulty d);
    void startServer();
    void readServerDefaults(const QString& dir);
    void readStdoutLine(const QString& line);

    QString              worldName_;
    bool                 running_;
    QProcess             serverProcess_;
    PlayerList           playerList_;
    McqlUtil::Difficulty difficulty_;
};

#endif // SERVERLINK_H
