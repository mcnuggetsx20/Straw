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

    refresh("wifi_list",  win, c1);
    refresh("eth_list",  win, c2);

    system("(nmcli --get-values=SSID,SIGNAL,BSSID --escape=no device wifi list | grep -v BC:1A:E4:84:52:B2 | awk -F ':' '{print $1}' > /mnt/hdd/coding/projects/Straw/wifi_list) &");

    system("(nmcli --get-values=NAME,TYPE connection show | grep ethernet | awk -F ':' '{print $1}' > /mnt/hdd/coding/projects/Straw/eth_list) &");

    system("(nmcli --get-values=NAME connection show --active > /mnt/hdd/coding/projects/Straw/active_networks) &");
    //REFRESHER::refresh(active_networks);
}

