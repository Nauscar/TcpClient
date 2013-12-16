#ifndef APPLICATIONUI_H
#define APPLICATIONUI_H

#include <QString>
#include <QTextStream>

#include "tcpclient.h"

class ApplicationUI
{
public:
    ApplicationUI();
    ~ApplicationUI();
    void getTcpServer(void);
private:
    TcpClient* tcpClient;
private:
    void handleClient(void);
};

#endif // APPLICATIONUI_H
