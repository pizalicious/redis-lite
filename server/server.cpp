// C++ 標準庫
#include <iostream>

// C 標準庫 (用 C++ 版本)
#include <cstring> // memset
#include <cstdio>  // perror

// POSIX 系統呼叫
#include <sys/socket.h> // 核心 socket header
#include <netinet/in.h> // 用於 sockaddr_in 結構
#include <unistd.h>     // 用於 close, read, write

#define PORT 8080

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *hello = "Server says: Hello from C++!";

    // 1. 建立 Socket 檔案描述符 (File Descriptor)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return -1;
    }

    // 設定 Socket 選項，讓它可以重複使用 Port (避免重開時報錯 "Address already in use")
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return -1;
    }

    // 2. 設定 IP 與 Port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 監聽本機所有 IP
    address.sin_port = htons(PORT);       // 設定 Port 8080

    // 3. Bind: 將 Socket 綁定到指定的 IP 和 Port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return -1;
    }

    // 4. Listen: 開始監聽連線，等待佇列長度設為 3
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }

    std::cout << "Waiting for connections on port " << PORT << "..." << std::endl;

    // 5. Accept: 阻塞 (Block) 直到有 Client 連進來
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        return -1;
    }

    std::cout << "Client connected!" << std::endl;

    // 6. Read: 讀取 Client 傳來的資料
    int valread = read(new_socket, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    // 7. Send: 回傳資料給 Client
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent\n";

    // 關閉連線
    close(new_socket);
    close(server_fd);
    return 0;
}
