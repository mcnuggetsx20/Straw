#pragma once
#include <QLabel>
#include "CustomWindow.cpp"
//#include "refresh.cpp"

class REFRESHER : public QWidget{
    public:
        CustomWindow* win;
        int interval = 1000;
        REFRESHER(CustomWindow *_win);
        //void (*fptr)(std::ifstream &file, const int &ind, CustomWindow* win) = &refresh;
        void read();
        //void refresh(std::ifstream &file, const int &ind);
};
