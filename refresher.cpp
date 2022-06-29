#include "refresher.hpp"
#include <QTimer>
#include <fstream>
#include <vector>
#include <stdlib.h>

REFRESHER::REFRESHER(CustomWindow* _win){
    win = _win;
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &REFRESHER::read);
    timer -> start(interval);
}

void REFRESHER::read(){
    int c1 = 1, c2= 2;

    win -> currentWifi = getOutput("nmcli --get-values=NAME,TYPE con show --active | grep wireless | awk -F ':' '{print $1}'");
    win -> getEth();

    refresh(win -> wifi_list,  win, c1);
    refresh(win -> eth_list,  win, c2);

    std::string command = "(nmcli --get-values=SSID,SIGNAL,BSSID --escape=no device wifi list | grep -v BC:1A:E4:84:52:B2 | awk -F ':' '{print $1}' > " + win -> wifi_list + ") &";
    const char * pCommand = command.c_str();
    system(pCommand);

    command = "(nmcli --get-values=NAME,TYPE connection show | grep ethernet | awk -F ':' '{print $1}' > " + win -> eth_list + ") &";
    pCommand = command.c_str();
    system(pCommand);

    //system("(nmcli --get-values=NAME connection show --active > /mnt/hdd/coding/projects/Straw/active_networks) &");
    //REFRESHER::refresh(active_networks);
}

