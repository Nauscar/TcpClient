#include "tcpclient.h"

TcpClient::TcpClient(QString host, quint16 port)
    : connected(true), host(host), port(port)
{
    this->host = host.length() > 0 ? host : "127.0.0.1";
    this->port = port > 0 ? port : 27015;

    tcpClient = new QTcpSocket(this);

    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

TcpClient::~TcpClient()
{
    delete tcpClient;
    delete networkSession;
}

bool TcpClient::IsConnected()
{
    return connected;
}

void TcpClient::RequestNewFortune()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(host, port);
}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qCritical() << "Error: Remote Host Closed.";
        break;
    case QAbstractSocket::HostNotFoundError:
        qCritical() << "Error: Host Not Found.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qCritical() << "Error: Connection Refused.";
        break;
    default:
        qCritical() << tcpClient->errorString();
    }
    connected = false;
}

void TcpClient::readFortune()
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpClient->bytesAvailable() < (int)sizeof(quint16)){
            return;
        }

        in >> blockSize;
    }

    if (tcpClient->bytesAvailable() < blockSize)
        return;

    QString nextFortune;
    in >> nextFortune;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, SLOT(requestNewFortune()));
        return;
    }

    currentFortune = nextFortune;

    QTextStream qOut(stdout);
    qOut << currentFortune << endl;
}
