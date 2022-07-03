#pragma once
//#include <QMainWindow>
//#include <QPropertyAnimation>
//#include <QRect>
//#include <QKeyEvent>
#include <iostream>
#include <vector>
#include "tools.cpp"

#include "TEXT.cpp"

typedef void(*functionPointer)();

class CustomWindow : public QMainWindow {
    public:
        TEXT* passwordInd;
        TEXT* passwordField;
        std::string conToPass = "";
        std::string currentWifi = "";
        std::vector<std::string> currentEth;
        std::string coded = "";
        std::string password = "";
        std::string home = getOutput("printf $HOME");
        const std::string wifi_list = home + "/.config/Straw/wifi_list";
        const std::string eth_list = home + "/.config/Straw/eth_list";
        int row[3] = {0,0,0};
        int column = 0;
        int maxRows[3] = {1, 6, 6};
        int pages = 0;
        bool bEnterPassword = false;
        bool Return = false;
        bool cond;
        //functionPointer fptrs[3] = {nullptr, &wifi_switch, &eth_switch};
        std::vector<TEXT*> grid[3] = { std::vector<TEXT*>(2), std::vector<TEXT*>(6), std::vector<TEXT*>(6) };

        CustomWindow();
        void paintEvent(QPaintEvent *event);
        void animation(QRect &start, QRect &stop);
        void select();
        void enterPassword(QString &key);
        void keyPressEvent(QKeyEvent *event);
        void initGrid();
        void getEth();
};
        
