#pragma once
#include <QPropertyAnimation>
#include <QRect>
#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <QPainter>
#include <Qt>
#include <string>

#include "CustomWindow.hpp"
#include "refresh.cpp"
//#include "tools.cpp"
//#include "TEXT.cpp"

CustomWindow::CustomWindow(){
    this -> setWindowTitle("Straw");
    this -> setAttribute(Qt::WA_TranslucentBackground,1);
    passwordInd = new TEXT( new QLabel(this), "" );
    passwordField = new TEXT( new QLabel(this), "" );

    passwordInd -> label -> move(10, 100);
    passwordField -> label -> move(10, 120);
}

void CustomWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setOpacity(0.4);
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
    grid[column][row[column]%6] -> label -> setStyleSheet("background: rgba(169, 220, 118, 255); color: #000000");
}

void CustomWindow::enterPassword(QString &key){
    for(int i =0; i < password.length(); ++i){
        std::cout <<"\b \b" << std::flush;
    }

    if(key=="\r"){
        conToPass = grid[column][row[column]%6] -> label -> text().toStdString();
        bool fakap = connectionSwitch( conToPass, column, currentWifi == conToPass + '\n', password);
        password="";
        coded="";
        Return = true;
        if(!fakap){
            bEnterPassword = false;
            passwordInd -> label -> setText("");
        }
    }

    coded += '*';
    password += key.toStdString();

    if(key=="\b" || Return){
        coded = coded.substr( 0, std::max( (int)coded.length()-2, 0) );
        password = password.substr( 0, std::max( (int)password.length()-2, 0) );
        Return = false;
    }

    passwordField -> label -> setText( QString::fromStdString(coded) );
    passwordField -> label -> adjustSize();

    std::cout << password << std::flush;
}

void CustomWindow::keyPressEvent(QKeyEvent *event){
    QString key = event -> text();

    if(bEnterPassword){ CustomWindow::enterPassword(key); return;}

    if(key == "\r"){
        if(column == 0){
            grid[column][row[column]%6] -> fptr();
            return;
        }
        conToPass = grid[column][row[column]%6] -> label -> text().toStdString();

        if(column == 1){
            cond = conToPass + '\n' == currentWifi;
        }
        else if(column == 2){
            cond = isInside(currentEth, conToPass);
        }

        bool fakap = connectionSwitch( conToPass, column, cond);
        if(fakap){
            passwordInd -> label -> setText("Password:");
            passwordInd -> label -> adjustSize();
            bEnterPassword = true;
            return;
        }
    }

    grid[column][row[column]%6] -> label -> setStyleSheet("background: rgba(0, 0, 0, 0); color: " + grid[column][row[column]%6] -> foreground);

    row[column] += -(int)(key=="k") + (int)(key=="j");
    column += (int)(key=="l") - (int)(key=="h");

    column = std::min( std::max(column, 0), 2 );
    row[column] = std::min( std::max(row[column], 0), maxRows[column] );

    if(row[column]%6 ==0 or row[column]%6==5){
        if(column==1){
            refresh(wifi_list, this, column);
        }
        else if(column==2){
            refresh(eth_list, this, column);
        }
    }

    CustomWindow::select();
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

void CustomWindow::getEth(){
    std::string a = getOutput("nmcli --get-values=NAME,TYPE connection show --active | grep ethernet | awk -F ':' '{print $1}'");
    currentEth.resize(0);
    int c = 0;
    for(int i =0 ;i < a.length(); ++i){
        if(a[i] == '\n'){
            currentEth.push_back( a.substr(c, i-c) );
            c= i+1;
        }
    }
}
