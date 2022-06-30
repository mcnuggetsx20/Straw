#include <QLabel>
#include <QFont>
#include <QString>
#include "TEXT.hpp"

TEXT::TEXT( QLabel* _label, QString text,  QString font, int fontsize){
        //QLabel *label = new QLabel(window);
        foreground = foreground_default;
        label = _label;
        label -> setText(text);
        label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: " + this -> foreground_default);

        label -> setFont(QFont(font, fontsize, QFont::Bold));
        label -> adjustSize();
}
