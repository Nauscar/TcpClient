#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QObject>
#include <QStringList>
#include <Windows.h>

#include "tcpclient.h"

class DataHandler : QObject
{
    Q_OBJECT
public:
    DataHandler(TcpClient* client);
    virtual ~DataHandler();
private:
    TcpClient* client;
    int index;
private slots:
    void newData(QString);
private:
    void sendKey(int vkey);
};

#endif // DATAHANDLER_H
