#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include "tools.cpp"


std::vector<std::string> read(const std::string &file){
    std::string element;
    std::vector <std::string> elements;

    std::ifstream res;
    res.open(file, std::ios::in);

    while(res){
        getline(res, element);
        elements.push_back(element);
    }

    return elements;
}

void refresh(const std::string &file, CustomWindow* win, int &column){
    std::vector<std::string> elements = read(file);
    if(elements.size() < 2){ return; }

    for(int i =0 ; i < 6; ++i){
        win -> grid[column][i] -> label -> setText("");
        win -> grid[column][i] -> connection = "";
        win -> grid[column][i] -> foreground = "#D0D0D0";
        win -> grid[column][i] -> label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: #D0D0D0");
    }

    win -> maxRows[column] = std::max( (int)elements.size() - 2, 0 );

    int currentPage = win -> row[column] / 6;

    for(int i = currentPage*6; i < std::min((int)elements.size(), currentPage*6 + 6); ++i){

        win -> grid[column][i%6] -> label -> setText( QString::fromStdString(elements[i]) );
        win -> grid[column][i%6] -> label -> adjustSize();
        win -> grid[column][i%6] -> connection = elements[i];

        if(elements[i] + '\n' == win -> currentWifi || ( column == 2 &&  isInside(win -> currentEth, elements[i]) ) ){
            win -> grid[column][i%6] -> foreground = "#7A05BE";
            win -> grid[column][i%6] -> label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: #7A05BE");
        }
    }

    win -> grid[win->column][win -> row[win -> column]%6] -> label -> setStyleSheet("background: rgba(169, 220, 118, 255); color: #000000");
    
}

