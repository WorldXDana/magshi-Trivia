import socket
import json

port = 8826

COMMANDS = {
    'login': 1,
    'signup': 2
}

def bytes_to_num(byte_arr, count):
    num = int(byte_arr[count - 1])
    for i in range(count - 2, -1, -1):
        num |= int(byte_arr[i]) << ((count - 1 - i) * 8)
    return num


def num_to_byte(num, count):
    byte_arr = [0] * count
    for i in range(0, count):
        byte_arr[count - 1 - i] = num >> (i * 8)
    return byte_arr

def build_json_packet(code, json_obj):
    dumped_json_string = json.dumps(json_obj) + '\0'
    #packet = bytes([code.to_bytes(), len(dumped_json_string).to_bytes(4, 'big')])
    packet = bytes([code, *num_to_byte(len(dumped_json_string), 4)])
    packet += dumped_json_string.encode()
    return packet

def readeem_message(s):
    msg = s.recv(1024)
    print(msg)
    print(msg[0])
    print(bytes_to_num(list(msg[1:5]), 4))
    print(json.loads(msg[5:].decode()))

def main():
    logged_in = False
    msg1 = ""

    s = socket.socket()
    s.connect(('127.0.0.1', port))
    if not logged_in:
            action = int(input('Choose option:\n1) Login\n2) Signup\n3) logout\nEnter the number of the option you chose: '))

            if action == 1:
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                s.send(build_json_packet(100, {'username': username, 'password': password}))
                readeem_message(s)
            if action == 2:
                username = input("Enter your username: ")
                password = input("Enter your password: ")
                email = input("Enter your email: ")
                s.send(build_json_packet(200, {'username': username, 'password': password, 'email': email}))
                readeem_message(s)
            if action == 3:
                username = input("Enter your username: ")
                s.send(build_json_packet(214, {'username': username}))
                readeem_message(s)

    s.close()


if __name__ == '__main__':
    main()
'''
       

        # Define the port on which you want to connect
        

        # connect to the server on local computer
        s.connect(('127.0.0.1', port))
        s.send(b"HELLO")

        # receive data from the server and decoding to get the string.
        print(s.recv(1024).decode())
        # close the connection
        s.close()
'''
