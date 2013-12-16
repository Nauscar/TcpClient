#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QAbstractSocket>

class TcpClient : QObject
{
    Q_OBJECT
public:
    TcpClient(QString host, quint16 port);
    virtual ~TcpClient(void);
    void RequestNewFortune(void);
    bool IsConnected(void);
private:
    QTcpSocket* tcpClient;
    QNetworkSession* networkSession;

    QString host;
    quint16 port;
    QString currentFortune;
    quint16 blockSize;
    bool connected;
private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readFortune(void);
};

#endif // TCPCLIENT_H
