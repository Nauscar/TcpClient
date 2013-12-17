#include "datahandler.h"

DataHandler::DataHandler(TcpClient* client) : client(client), index(0)
{
    this->debug = QString("This is a debug statement").split(" ");
    connect(client, SIGNAL(ServerReply()), this, SLOT(fetchNewData()));
    fetchNewData();
}

DataHandler::~DataHandler() {}

void DataHandler::fetchNewData()
{
    QString tmp = debug.at(++index % debug.length());
    client->SendData(QByteArray(tmp.toStdString().c_str()));
}
