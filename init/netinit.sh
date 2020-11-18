#!/bin/sh
###########################################################################
PASSWD="111111"
MODELPLACE="/home/giim/Earthquake_monitor/drive_for_sim7600/simcom_wwan.ko"
net_port="/dev/net_port"
###########################################################################
echo $PASSWD | sudo -S killall ModemManager
echo $PASSWD | sudo -S insmod $MODELPLACE
echo $PASSWD | sudo -S ifconfig wwan0 up
sleep 1
echo $PASSWD | sudo -S echo -e "AT+CNMP=38\r" > $net_port
sleep 1
echo $PASSWD | sudo -S echo -e "AT\$QCRMCALL=1,1\r" > $net_port
sleep 1
echo $PASSWD | sudo -S udhcpc -i wwan0


