import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Socket successfully created")

port = 5050

s.bind (("10.2.7.142", port))
print("socket binded to % s"%(port))

s.listen(5)
print("socket is listening")

c, addr = s.accept()
print("Got connection from", addr)

c.send("Thank you for connecting".encode())

c.close()
