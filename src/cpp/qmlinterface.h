#ifndef QMLINTERFACE_H
#define QMLINTERFACE_H

#include <QObject>

class QmlInterface : public QObject
{
    Q_OBJECT
public:
    explicit QmlInterface(QObject *parent = nullptr);

    Q_INVOKABLE void getAvailableScreens();

    Q_INVOKABLE void getAvailableWindows();

signals:
    void availableScreensCompleted();

    void availableWindowsCompleted();

};

#endif // QMLINTERFACE_H
