# Sends a broadcast udp packet with this device's IP
import socket
import time

PORT=30002
HOST=socket.gethostbyname(socket.gethostname())
UDP_BROADCAST_IP="255.255.255.255"
SLAVE_WAIT_TIME=5 # seconds to wait for slaves to respond to broadcast
INIT_MESSAGE="UNHROV"

# Broadcast a packet with our init string.
# Slaves will communicate back with their IPs
def get_slaves(sendsock):
    # Setup a temporary UDP listener on the same port we are broadcasting to
    recvsock = socket.socket(socket.AF_INET, socket.DOCK_DGRAM) # IPv4 UDP
    recvsock.bind((HOST, PORT))

    # Configure sendsock
    sendsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sendsock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    slaves = []
    for _ in range(SLAVE_WAIT_TIME):
        sock.sendto(INIT_MESSAGE, (UDP_BROADCAST_IP, PORT))
        data, addr = recvsock.recvfrom(512)
        slaves.append(addr)
        time.sleep(1)

    return set(slaves)

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # IPv4 UDP
    slaves = get_slaves();
    print(slaves)

main()
