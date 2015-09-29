#ifndef MCQLUTIL_H
#define MCQLUTIL_H

#include <QObject>
class QJSEngine;
class QQmlEngine;

class McqlUtil :
        public QObject
{
    Q_OBJECT

public:
    static QObject* qmlSingletonProvider(QQmlEngine*, QJSEngine*) { return new McqlUtil(); }

    Q_INVOKABLE void        initialiseWorld(const QString& name, int type, int difficulty, int hurting);
    Q_INVOKABLE QStringList importableWorlds();
    Q_INVOKABLE void        importWorld(const QString& source, const QString& destination);
    Q_INVOKABLE QStringList availableWorlds();
    Q_INVOKABLE QString     genWorldName(const QString& seed);

signals:
    void creationError(const QString& err);

protected slots:
    void logError(const QString& err);

protected:
    McqlUtil();
};

#endif // MCQLUTIL_H
