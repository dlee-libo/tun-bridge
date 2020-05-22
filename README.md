This project show how to implement simple bridge via `tun` interface. The main program(bridge.c) will create two tun interface: `tun0`, `tun1`. Then keep forwarding IP packet between the two interfaces. To demonstrate the bridging functionality, use the `setup.sh` to create a seperate network namespace and move the `tun1` into that namespace. Then `setup.sh` will config address for each interface. After that we can `ping 10.10.0.100` from host network and `ping 10.10.0.200` from ns0 network namespace.