#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>


std::string getOutput(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

bool isInside(std::vector<std::string> &vec, std::string &tar){
    for(auto i: vec){
        if(i == tar){ return true; }
    }
    return false;
}

bool connectionSwitch(std::string connection,  int &column, bool currentCon, std::string password=""){
    if(connection == ""){ return 0; }

    std::string command = "";
    const char* pCommand;

    if(column==1){
        if(currentCon){
            command = "nmcli con down '" + connection + "' &";
            pCommand = command.c_str();
            system(pCommand);
            return 0;
        }

        command = "nmcli dev wifi connect '" + connection + "'";
        if(password!=""){
            command += " password '" + password + "'";
        }

        pCommand = command.c_str();

        std::string shot = getOutput(pCommand);
        if(shot == "Error: Connection activation failed: (7) Secrets were required, but not provided.\n"){
            return 1;
        }
        return 0;

    }

    if(currentCon){
        command = "nmcli con down '" + connection + "' &";
        pCommand = command.c_str();
        system(pCommand);
        return 0;
    }

    command = "nmcli con up '" + connection + "' &";
    pCommand = command.c_str();
    system(pCommand);
    return 0;

    //std::cout << *pConnection << '\n';
}

void eth_switch(){
    std::string device = getOutput("nmcli --get-values=DEVICE,TYPE dev | grep ethernet | awk -F ':' '{print $1}'");
    std::string status = getOutput("nmcli --get-values=STATE,TYPE dev | grep ethernet | awk -F ':' '{print $1}'");
    std::string command;
    const char * pCommand;
    if(status == "connected\n"){
        command = "nmcli dev down ";
    }
    else{
        command = "nmcli dev up ";
    }
    command += device;
    pCommand = command.c_str();
    system(pCommand);

}

void wifi_switch(){
    std::string status = getOutput("nmcli radio wifi");
    if(status=="enabled\n"){
        system("nmcli radio wifi off &");
        return;
    }
    system("nmcli radio wifi on &");
    return;
}
