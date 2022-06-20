#pragma once
#include <QPropertyAnimation>
#include <QRect>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <QPainter>
#include <Qt>

#include "CustomWindow.hpp"
//#include "TEXT.cpp"

CustomWindow::CustomWindow(){
    this -> setWindowTitle("QNetwork");
    this -> setAttribute(Qt::WA_TranslucentBackground,1);
}

void CustomWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setOpacity(0.6);
    painter.setBrush(QColor(0,0,0));
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());
}

void CustomWindow::animation(QRect &start, QRect &stop){
    QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
    anim -> setDuration(80);
    anim -> setStartValue( QRect(start) );
    anim -> setEndValue( QRect(stop) );
    anim -> start();
}

void CustomWindow::select(){
    grid[column][row] -> label -> setStyleSheet("background: rgba(169, 220, 118, 255); color: #000000");
}

void CustomWindow::keyPressEvent(QKeyEvent *event){
    QString key = event -> text();

    grid[column][row] -> label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: #D0D0D0");

    row += -(int)(key=="k") + (int)(key=="j");
    column += (int)(key=="l") - (int)(key=="h");

    column = std::min( std::max(column, 0), 2 );
    row = std::min( std::max(row, 0), maxRows[column] );

    CustomWindow::select();
    //std::cout << maxRows[column] << '\n';
    //std::cout<<column << ' ' << row << "\n\n";
}

void CustomWindow::initGrid(){
    int columnPositions[3] = {10, 100, 250};
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < (int)grid[i].size(); ++j){
            grid[i][j] -> label -> move( columnPositions[i], 25 * j + 5 );
        }
    }
    CustomWindow::select();
}
