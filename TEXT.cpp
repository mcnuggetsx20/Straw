#include <QLabel>
#include <QFont>
#include <QString>
#include "TEXT.hpp"

TEXT::TEXT( QLabel* _label, QString text,  QString font, int fontsize){
        //QLabel *label = new QLabel(window);
        label = _label;
        label -> setText(text);
        label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: #D0D0D0");

        label -> setFont(QFont(font, fontsize, QFont::Bold));
        label -> adjustSize();
}
