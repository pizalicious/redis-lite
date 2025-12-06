import socket

HOST = '127.0.0.1'  # 本機 IP
PORT = 8080         # 跟 C++ 設定的 Port 一樣

# 1. 建立 Socket (IPv4, TCP)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    print(f"Connecting to {HOST}:{PORT}...")

    # 2. 連線到 Server
    s.connect((HOST, PORT))

    # 3. 傳送資料
    message = "Hello from Python Client!"
    s.sendall(message.encode()) # 字串轉 bytes

    # 4. 接收 Server 回傳的資料
    data = s.recv(1024)

print(f"Received from Server: {data.decode()}")
