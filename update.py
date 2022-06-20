#!/usr/bin/python
from time import sleep
from subprocess import Popen

wifi_list = "nmcli --get-values=SSID,SIGNAL,BSSID --escape=no device wifi list | grep -v BC:1A:E4:84:52:B2 | awk -F ':' '{print $1}' > /mnt/hdd/coding/projects/qnetwork/wifi_list"
eth_list = "nmcli --get-values=NAME,TYPE connection show | grep ethernet | awk -F ':' '{print $1}' > /mnt/hdd/coding/projects/qnetwork/eth_list"
active = "nmcli --get-values=NAME connection show --active > /mnt/hdd/coding/projects/qnetwork/active_networks"

commands = [wifi_list, eth_list, active]

while True:
    for i in commands:
        Popen(i, shell=True)
    sleep(2)




