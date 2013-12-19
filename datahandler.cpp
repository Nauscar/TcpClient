#include "datahandler.h"

DataHandler::DataHandler(TcpClient* client) : client(client), index(0)
{
    connect(client, SIGNAL(ServerReply(QString)), this, SLOT(newData(QString)));
}

DataHandler::~DataHandler() {}

void DataHandler::newData(QString action)
{
    if(action == "fist"){
        sendKey(VK_RIGHT);
    }
    else if(action == "fingers_spread") {
        sendKey(VK_LEFT);
    }
}

void DataHandler::sendKey(int vkey)
{
    INPUT* key = new INPUT;
    key->type = INPUT_KEYBOARD;
    key->ki.wVk = vkey;
    key->ki.dwFlags = 0;
    key->ki.time = 0;
    key->ki.wScan = 0;
    key->ki.dwExtraInfo = 0;

    SendInput(1,key,sizeof(INPUT));

    key->ki.dwExtraInfo = KEYEVENTF_KEYUP;

    SendInput(1,key,sizeof(INPUT));
}
