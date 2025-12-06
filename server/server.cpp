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

    // 建立 socket 檔案描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    // 強制綁定端口
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        std::cerr << "Set socket options error" << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 綁定 socket 到端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return -1;
    }

    // 開始監聽
    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    // 接受連接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        std::cerr << "Accept failed" << std::endl;
        return -1;
    }

    // 讀取資料
    read(new_socket, buffer, 1024);
    std::cout << "Message from client: " << buffer << std::endl;

    // 發送回應
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Hello message sent" << std::endl;

    // 關閉 socket
    close(new_socket);
    close(server_fd);
    return 0;
}
