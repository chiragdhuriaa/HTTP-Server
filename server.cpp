#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mutex>
#include <chrono>
#include <map>
#include <ctime>

#pragma comment(lib, "Ws2_32.lib")

std::mutex log_mutex;

std::map<std::string, std::chrono::steady_clock::time_point> rate_limiter;

void log_request(const std::string& client_ip, const std::string& request, const std::string& response_code) {
    std::lock_guard<std::mutex> guard(log_mutex);
    std::ofstream log_file("server.log", std::ios_base::app);
    std::time_t now = std::time(0);
    log_file << "[" << std::ctime(&now) << "] IP: " << client_ip << " Request: " << request << " Response: " << response_code << std::endl;
    log_file.close();
}

bool authenticate(const std::string& auth_header) {
    const std::string expected_auth = "Basic dxN1cjpwXYNz";
    return auth_header == expected_auth;
}

void handle_client(SOCKET client_socket, sockaddr_in client_addr) {
    char buffer[4096];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received > 0) {
        std::string request(buffer, bytes_received);
        std::string client_ip = inet_ntoa(client_addr.sin_addr);
        log_request(client_ip, request, "200 OK");

        auto now = std::chrono::steady_clock::now();
        if (rate_limiter.find(client_ip) != rate_limiter.end() && std::chrono::duration_cast<std::chrono::seconds>(now - rate_limiter[client_ip]).count() < 1) {
        std::string rate_limit_response = "HTTP/1.1 429 Too Many Requests\r\n\r\n";
        send(client_socket, rate_limit_response.c_str(), rate_limit_response.size(), 0);
        closesocket(client_socket);
        return;
        }
    rate_limiter[client_ip] = now;

    std::string path = "/index.html";
    std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    std::ifstream file(path);
    if (file.is_open()) {
        std::stringstream file_stream;
        file_stream << file.rdbuf();
        response += file_stream.str();
    } else {
        response = "HTTP/1.1 404 Not Found\r\n\r\n";
    }

    send(client_socket, response.c_str(), response.size(), 0);
    } 

    closesocket(client_socket);
}

int main() {
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed with error: " << wsaResult << std::endl;
        return 1;
    }

    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(8080);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    int opt_val = 1;
    setsockopt(listening, SOL_SOCKET, SO_REUSEADDR, (char*)&opt_val, sizeof(opt_val));

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    if (listen(listening, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    std::vector<std::thread> threads;
    while (true) {
        sockaddr_in client;
        int client_size = sizeof(client);
        SOCKET client_socket = accept(listening, (sockaddr*)&client, &client_size);

        if(client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

        threads.emplace_back(std::thread(handle_client, client_socket, client));

    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    closesocket(listening);
    WSACleanup();
    return 0;
}
