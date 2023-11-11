#include "serverinterface.h"

ServerInterface::ServerInterface(QObject *parent) : QObject(parent)
{
    m_server = new QWebSocketServer("TunaCAST Server",QWebSocketServer::SslMode::NonSecureMode,parent);
    /*
        Add ssl configurations to make it more secure
    */

    connect(m_server,&QWebSocketServer::newConnection,this,&ServerInterface::onNewConnection);
}

bool ServerInterface::startListening()
{
    bool conn = this->m_server->listen(QHostAddress::Any,35793);

    if(!conn) {
        qDebug() << "Error starting server: " << this->m_server->errorString();
    } else {
        qDebug() << "Server started!";
    }

    return conn;
}

void ServerInterface::sendTextMessage(QString message)
{
    // qDebug()<<"How many clients? "<<m_clients.size();

    foreach(QWebSocket * client,m_clients)
    {
        if(client->isValid())
        {
            client->sendTextMessage(message);

            qDebug()<<"Sending -> "<<message;
        }
        else
        {
            qDebug() << "Invalid Client to send to!";
        }
    }
}

void ServerInterface::onNewConnection()
{
    QWebSocket * client = this->m_server->nextPendingConnection();

    connect(client,&QWebSocket::disconnected,this,&ServerInterface::onDisconnected);

    m_clients.append(client);
}

void ServerInterface::onDisconnected()
{
    foreach(QWebSocket * client,m_clients)
    {
        if(!client->isValid())
        {
            qDebug()<<client->errorString();

            m_clients.removeOne(client);
        }
    }
}

bool ServerInterface::serverOnline() const
{
    return m_serverOnline;
}

void ServerInterface::setServerOnline(bool newServerOnline)
{
    if (m_serverOnline == newServerOnline)
        return;
    m_serverOnline = newServerOnline;
    emit serverOnlineChanged(newServerOnline);
}
