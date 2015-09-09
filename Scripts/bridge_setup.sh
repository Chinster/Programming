#!/bin/sh

ip l s  enp2s0 down
ip l a br0 type bridge

ip l s enp2s0 promisc on
ip l s enp2s0 up
ip l s enp2s0 master br0

dhcpcd br0
