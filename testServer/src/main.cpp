#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

#include <cstring>
#include <iostream>
#include <thread>

constexpr int PORT = 9000;
constexpr int BUFFER_SIZE = 1024;

void handleClient(int clientFd) {
    char buffer[BUFFER_SIZE];

    while (true) {
        std::string msg;
    
        std::cout << "Enter text: ";

        std::cin >> msg;

        write(clientFd, msg.c_str(), msg.size());
    }

    close(clientFd);
}

int main() {
    signal(SIGPIPE, SIG_IGN);

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverFd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(serverFd, 5) < 0) {
        perror("listen");
        return 1;
    }

    std::cout << "[Server] Listening on port " << PORT << "\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);

        int clientFd = accept(serverFd, (sockaddr*)&clientAddr, &clientLen);
        if (clientFd < 0) {
            perror("accept");
            continue;
        }

        std::cout << "[Server] New client connected\n";
        std::thread(handleClient, clientFd).detach();
    }

    close(serverFd);
    return 0;
}
