#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QRect>

#include "CustomWindow.cpp"
#include "refresher.cpp"
//#include "TEXT.pp"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    CustomWindow *window = new CustomWindow;

    QRect start = QRect(2*1920, 30, 400, 145);
    QRect stop = QRect(1920 + 1500, 30, 400, 145); 

    REFRESHER* refresh = new REFRESHER( window );

    window -> grid[0] = { new TEXT( new QLabel(window), "Ethernet" ), new TEXT( new QLabel(window), "WiFi" ) };
    window -> grid[1] = { new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ) };
    window -> grid[2] = { new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ), new TEXT( new QLabel(window) ) };

    window -> grid[0][0] -> fptr = &eth_switch;
    window -> grid[0][1] -> fptr = &wifi_switch;

    //std::cout << (window -> grid[0][0] -> label -> text()).toStdString() << '\n';

    window -> show();
    window -> animation(start, stop);
    window -> initGrid();
    refresh -> read();

    return app.exec();
}

