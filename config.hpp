#pragma once
#include <iostream>
#include <QColor>
#include <QString>
using namespace std;

namespace config{
    //Resolution for the animation
    //Set them to equal values to disable animation
    pair <int, int> res_start = {400, 145};
    pair <int, int> res_stop = res_start;

    //Window position for the animation
    //Again: same values = no animation
    pair <int, int> pos_start = {1366, 30};
    pair <int, int> pos_stop = {950, 30};

    //Colors
    QColor background = QColor(255, 255, 255);
    double opacity = 0.6;
    string foreground = "#312D2D";

    //Font
    QString font = "Samsung Sans";
    int fontsize = 10;

    //Window name
    string win_name = "Straw";
    
}
