#pragma once
//#include <QLabel>
//#include <QFont>
#include <QString>
#include <QLabel>
#include "config.hpp"

class TEXT {
    public:
        QLabel* label;
        std::string connection;
        QString foreground_default = config::foreground;
        QString foreground;
        void (*fptr)();
        TEXT(QLabel* _label,
             QString text = "", 
             QString font = config::font,
             int fontsize = config::fontsize);

};
