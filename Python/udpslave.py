# Listens for a udp packet and considers the IP address in that packet the master
# Assumes a singular interface on the slave device. Otherwise we are at the will
# of the kernel
import socket

PORT=30002
#HOST=socket.getaddrinfo(None, PORT, socket.AF_INET6, socket.SOCK_DGRAM)[0][4]
HOST="::"
INIT_RESPONSE=b"Hi"

def main():
    recvsock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM) # IPv4 UDP
    #recvsock.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_JOIN_GROUP, socket.inet_pton(socket.AF_INET6, "ff02::1") + b"1")
    recvsock.bind(('', PORT))

    sendsock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM) # IPv4 UDP

    # Wait for a master broadcast
    while True:
        data, addr = recvsock.recvfrom(512)
        if data == b'UNHROV':
            sendsock.sendto(INIT_RESPONSE, (addr[0], PORT))
            break

main()
