#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QThread>

#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QAbstractSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QString host, quint16 port);
    virtual ~TcpClient(void);
    void SendData(QByteArray data);
signals:
    void ServerReply(void);
private:
    QTcpSocket* tcpClient;
    QNetworkSession* networkSession;

    QString host;
    quint16 port;
    QString currentFortune;
    quint16 blockSize;
private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readData(void);
private:
    void tcpConnect(void);
};

#endif // TCPCLIENT_H
