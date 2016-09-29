# Listens for a udp packet and considers the IP address in that packet the master
import socket

PORT=30002
HOST=socket.gethostbyname(socket.gethostname())

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # IPv4 UDP
    sock.bind((HOST, PORT))

    # Wait for a master broadcast
    while True:
        data, addr = sock.recvfrom(512)


main()
