#include "tcpclient.h"

TcpClient::TcpClient(QString host, quint16 port)
{
    this->host = host.length() > 0 ? host : "127.0.0.1";
    this->port = port > 0 ? port : 27015;
    tcpConnect();
}

TcpClient::~TcpClient()
{
    tcpClient->abort();
    delete tcpClient;
    delete networkSession;
}

void TcpClient::tcpConnect()
{
    tcpClient = new QTcpSocket(this);

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    tcpClient->connectToHost(host, port, QIODevice::ReadWrite);
}

void TcpClient::SendData(QByteArray data)
{
    if(tcpClient->waitForConnected()){
        tcpClient->write(data);
    } else {
        qCritical() << "Connection timeout occurred";
    }
}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qCritical() << "Error: Remote Host Closed";
        break;
    case QAbstractSocket::HostNotFoundError:
        qCritical() << "Error: Host Not Found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qCritical() << "Error: Connection Refused";
        break;
    default:
        qCritical() << tcpClient->errorString();
    }
}

void TcpClient::readData()
{
    QTcpSocket* myServer = qobject_cast<QTcpSocket*>(sender());
    QByteArray reply = myServer->readAll();

    qDebug() << QString(reply);

    emit ServerReply(QString(reply));
}
