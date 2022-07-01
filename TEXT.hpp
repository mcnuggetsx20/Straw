#pragma once
//#include <QLabel>
//#include <QFont>
#include <QString>
#include <QLabel>

class TEXT {
    public:
        QLabel* label;
        std::string connection;
        QString foreground_default = "#D0D0D0";
        QString foreground;
        void (*fptr)();
        TEXT(QLabel* _label,
             QString text = "", 
             QString font = "Samsung Sans",
             int fontsize = 10);

};
