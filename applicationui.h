#ifndef APPLICATIONUI_H
#define APPLICATIONUI_H

#include <QString>
#include <QStringList>
#include <QTextStream>

#include "tcpclient.h"
#include "datahandler.h"

class ApplicationUI
{
public:
    ApplicationUI();
    ~ApplicationUI();
    void getTcpServer(void);
private:
    TcpClient* tcpClient;
    DataHandler* dataHandler;
};

#endif // APPLICATIONUI_H
