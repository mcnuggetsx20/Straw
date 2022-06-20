#include "refresher.hpp"
#include <QTimer>
#include <fstream>
#include <vector>

REFRESHER::REFRESHER(CustomWindow* _win){
    win = _win;
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &REFRESHER::read);
    timer -> start(interval);
}

void REFRESHER::read(){
    std::ifstream eth_list, wifi_list, active_networks;

    eth_list.open("eth_list", std::ios::in);
    wifi_list.open("wifi_list", std::ios::in);
    //active_networks.open("active_networks", std::ios::in);

    for(int i =0 ; i < 6; ++i){
        win -> grid[1][i] -> label -> setText("");
        win -> grid[2][i] -> label -> setText("");
    }

    REFRESHER::refresh(eth_list, 2);
    REFRESHER::refresh(wifi_list, 1);
    //REFRESHER::refresh(active_networks);
}


void REFRESHER::refresh(std::ifstream &file, const int &ind){
    std::string element;
    std::vector <std::string> elements;
    while(file){
        getline(file, element);
        elements.push_back(element);
    }

    win -> maxRows[ind] = std::max( (int)elements.size() - 2, 0 );

    for(int i =0 ; i < std::min((int)elements.size(), 6); ++i){
        win -> grid[ind][i] -> label -> setText( QString::fromStdString(elements[i]) );
        win -> grid[ind][i] -> label -> adjustSize();
    }
    
}

