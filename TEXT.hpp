#pragma once
//#include <QLabel>
//#include <QFont>
//#include <QString>
//#include <QLabel>

class TEXT {
    public:
        QLabel* label;
        TEXT(QLabel* _label,
             QString text = "", 
             QString font = "Samsung Sans",
             int fontsize = 10);

};
