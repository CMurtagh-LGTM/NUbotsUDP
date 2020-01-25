import socket
import vector_pb2

UDP_IP = "127.0.0.1"

#RECIEVE
UDP_IN_PORT = 5002

sockIn = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sockIn.bind((UDP_IP, UDP_IN_PORT))

#SEND
#UDP_OUT_PORT = 5003
#MESSAGE = "cool"
#MESSAGE = MESSAGE.encode('ASCII')

print("UDP target IP:", UDP_IP)
#print("UDP target port:", UDP_OUT_PORT)

sockOut = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

#PROTOBUF
vec16 = vector_pb2.vec16()

while True:
    data, addr = sockIn.recvfrom(1024) # buffer size is 1024 bytes
    print("received message:",data)
    vec16.ParseFromString(data)
    print("received message:",vec16)
    #sockOut.sendto(MESSAGE, (UDP_IP, UDP_OUT_PORT))
    #print("sent message:", MESSAGE)