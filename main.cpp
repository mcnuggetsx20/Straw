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

    QRect start = QRect(config::pos_start.first, config::pos_start.second, config::res_start.first, config::res_start.second);
    QRect stop = QRect(config::pos_stop.first, config::pos_stop.second, config::res_stop.first, config::res_stop.second);

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

