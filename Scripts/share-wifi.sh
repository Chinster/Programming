#!/bin/sh

ETH=enp3s0f1
WLAN=wlp2s0

# Create a network on eth
#ip a a dev $ETH 192.168.0.14/24

sysctl -w net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -o $WLAN -j MASQUERADE

ip l s $ETH up
