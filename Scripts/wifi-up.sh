#!/bin/sh

INTERFACE=wlp2s0

if [[ $EUID -ne $ROOT_UID ]]; then
    echo "This script must be run as root"
    exit 1
fi

if [ ! $# == 1 ]; then
    echo -e 'Calls wpa_supplicant on conf file at /etc/wpa_supplicant/[CONFIG-NAME].conf, then dhcpcd
    \nUsage: wifi-up [CONFIG-NAME]'
    exit 1
fi

sudo wpa_supplicant -Dnl80211 -i "$INTERFACE" -c/etc/wpa_supplicant/"$1".conf & disown
sleep 2
sudo dhcpcd "$INTERFACE"
