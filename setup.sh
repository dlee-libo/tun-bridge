#!/bin/bash
# run this script after the bridge is ready
ip netns add ns0
ip link set tun1 netns ns0
ip netns exec ns0 ip addr add 10.10.0.100/32 peer 10.10.0.200 dev tun1
ip netns exec ns0 ip link set tun1 up

ip addr add 10.10.0.200/32 peer 10.10.0.100 dev tun0
ip link set tun0 up
