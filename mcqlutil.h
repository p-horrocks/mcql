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

    Q_INVOKABLE void initialiseWorld(const QString& name, int type, int difficulty, int hurting);

signals:
    void creationError(const QString& err);

protected:
    McqlUtil() {}
};

#endif // MCQLUTIL_H
