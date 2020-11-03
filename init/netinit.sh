#!/bin/sh
####################
PASSWD="111111"
MODELPLACE="simcom_wan.ko"
####################
gnome-terminal -x bash
echo $PASSWD | sudo -S su
killall ModemManager
insmod $MODELPLACE
minicom -D /dev/ttyUSB2
AT+CNMP=38
AT$QCRMCAALL=1,1

gnome-terminal -x bash
echo $PASSWD | sudo -S su
ifconfig wwan0 up
udhcpc -i wwan0


