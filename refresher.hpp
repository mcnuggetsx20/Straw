#pragma once
#include <QLabel>
#include "CustomWindow.cpp"

class REFRESHER : public QWidget{
    public:
        CustomWindow* win;
        int interval = 1000;
        REFRESHER(CustomWindow *_win);
        void read();
        void refresh(std::ifstream &file, const int &ind);
};
