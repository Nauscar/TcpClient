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
    QNetworkConfigurationManager manager;
    networkSession = new QNetworkSession(manager.defaultConfiguration(), this);
    connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
    networkSession->open();

    tcpClient = new QTcpSocket(this);

    //connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    tcpClient->connectToHost(host, port, QIODevice::ReadWrite);
}

void TcpClient::SendData(QString message)
{
    if(tcpClient->waitForConnected()){
        qDebug() << tcpClient->write(message.toStdString().c_str());
    } else {
        qCritical() << "Connection timeout occurred";
    }
    tcpClient->waitForReadyRead();
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

void TcpClient::sessionOpened()
{
    //TODO: Add configuration settings here.
}
