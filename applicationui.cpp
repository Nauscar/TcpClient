#include "applicationui.h"

ApplicationUI::ApplicationUI()
{
    getTcpServer();
}

ApplicationUI::~ApplicationUI()
{
    delete tcpClient;
}

void ApplicationUI::getTcpServer()
{
    QTextStream qIn(stdin);
    QTextStream qOut(stdout);
    qOut << "IP (default=127.0.0.1):" << endl;
    QString host = qIn.readLine();
    qOut << "Port (default=27015):" << endl;
    quint16 port = qIn.readLine().toUInt();

    tcpClient = new TcpClient(host, port);
    handleClient();
}

void ApplicationUI::handleClient()
{
    QTextStream qIn(stdin);
    QTextStream qOut(stdout);
    while(1)
    {
        //qOut << "Input message:" << endl;
        QString input = qIn.readLine();
        if(input.length()){
            tcpClient->SendData(input);
        }
    }
}
