import random 
import time as tp 
import numpy as np 
import serial 
import socket 
 
Target_ip = "10.177.172.137"
signal_ip ="10.177.172.107"
Target_port = 80

# sr = serial.Serial("COM5", 115200, timeout=1) 

tp.sleep(2) 
print("connecting to esp32....") 

old_direction = 0 

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket,\
     socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_socket2: 
    tcp_socket.settimeout(3) 
    tcp_socket.connect((Target_ip, Target_port)) 
    tcp_socket2.settimeout(3) 
   #tcp_socket2.connect((signal_ip, Target_port)) 
    print("connected to esp32") 
    #print("connected to signal light")

    while True: 
        try:
            traffic = { 
                "1": random.uniform(0, 100), 
                "2": random.uniform(0, 100), 
                "3": random.uniform(0, 100), 
                "4": random.uniform(0, 100), 
            } 
            traffic=max(traffic,key=traffic.get)
            data = f"{traffic}\n".encode('utf-8') 
            tcp_socket.sendall(data) 
 
            print(f"Sending data:{data}") 
            tp.sleep(2)
        except socket.timeout as e: 
            print(f"Error:{e}")