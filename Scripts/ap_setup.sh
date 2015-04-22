#!/bin/sh

sudo ip l s enp2s0 up
sudo ip l a br0 type bridge
sudo ip l s enp2s0 master br0
sudo dhcpcd br0
