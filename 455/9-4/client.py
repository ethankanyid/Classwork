import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

port = 5050

s.connect(("10.2.6.211", port))

print(s.recv (1024).decode())

s.close()
