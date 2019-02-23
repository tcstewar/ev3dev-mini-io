import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto('test', ('192.168.0.1', 8877))

data, server = sock.recvfrom(4)
print(data, server)
