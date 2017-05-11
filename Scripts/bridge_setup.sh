#!/bin/sh

BRIDGE=br0
ETH=enp3s0f1
WIFI=wlp2s0

if [ $# == 1 ];
then
    BRIDGE=$1
fi

ip l s dev $ETH down

ip l a dev $BRIDGE type bridge
ip l s dev $ETH master $BRIDGE

ip l s dev $ETH up
ip l s dev $BRIDGE up
