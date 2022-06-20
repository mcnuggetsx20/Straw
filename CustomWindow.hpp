#pragma once
//#include <QMainWindow>
//#include <QPropertyAnimation>
//#include <QRect>
//#include <QKeyEvent>
#include <iostream>
#include <vector>

#include "TEXT.cpp"

class CustomWindow : public QMainWindow {
    public:
        int column = 0;
        int row = 0;
        int maxRows[3] = {1, 6, 6};
        std::vector<TEXT*> grid[3] = { std::vector<TEXT*>(2), std::vector<TEXT*>(6), std::vector<TEXT*>(6) };

        CustomWindow();
        void paintEvent(QPaintEvent *event);
        void animation(QRect &start, QRect &stop);
        void select();
        void keyPressEvent(QKeyEvent *event);
        void initGrid();
};
        
