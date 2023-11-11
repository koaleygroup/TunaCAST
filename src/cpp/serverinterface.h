#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QVariantMap>
#include <QJsonDocument>
#include <QtDebug>

class ServerInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerInterface(QObject *parent = nullptr);

    Q_PROPERTY(bool serverOnline READ serverOnline WRITE setServerOnline NOTIFY serverOnlineChanged FINAL)

    void sendTextMessage(QString message);

    bool startListening();

    bool serverOnline() const;
    void setServerOnline(bool newServerOnline);

signals:
    void serverOnlineChanged(bool isOnline);

private slots:
    void onNewConnection();

    void onDisconnected();
private:
    QWebSocketServer * m_server;

    QList<QWebSocket *> m_clients;
    bool m_serverOnline;
};

#endif // SERVERINTERFACE_H
