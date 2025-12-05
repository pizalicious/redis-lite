#include <iostream>
#include <unistd.h> // 這是 Linux 特有的標頭檔，如果在 Windows 跑會報錯

int main() {
    std::cout << "Hello from Linux WSL!" << std::endl;
    return 0;
}