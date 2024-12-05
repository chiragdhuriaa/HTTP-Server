# Multithreaded-HTTP-Server
About This Project

Welcome to the Multithreaded HTTP Server! This project is a lightweight, multithreaded HTTP server built in C++ using the Windows Sockets (WinSock) API. It showcases fundamental concepts of networking, file handling, multithreading, and request-response mechanics for HTTP/1.1.
Features

    Multithreaded Client Handling
    Handles multiple clients simultaneously using separate threads, ensuring responsiveness.

    Rate Limiting
    Implements a basic rate-limiting mechanism to prevent request floods from the same IP.

    File Serving
    Serves static HTML content, such as index.html. If the file is not found, returns a 404 Not Found response.

    Logging
    Logs every client request to a file (server.log), including timestamps, client IP, request details, and response codes.

    Error Responses
    Sends appropriate HTTP error responses, including 404 Not Found and 429 Too Many Requests.

Technology Stack

    Programming Language: C++
    Networking API: WinSock2
    Threading: Standard C++ Threads (std::thread)
    File Handling: File I/O using fstream

How It Works

    Start the Server
    The server listens on port 8080 for incoming client connections.

    Client Connection
    Each client request is processed in its own thread to allow concurrent handling.

    Rate Limiting
    A map tracks the timestamps of the last request from each client IP. If a client sends another request within 1 second, they receive a 429 Too Many Requests response.

    Serving Files
    The server attempts to serve an index.html file. If the file is missing, a 404 Not Found response is sent.

How to Use

    Compile and Run
    Compile the program using a C++ compiler that supports WinSock2 and threading (e.g., MSVC). Run the executable on a Windows machine.

    Access the Server
    Open a web browser or use a tool like curl to access http://<server-ip>:8080. Ensure the index.html file is present in the same directory as the executable.

    Check Logs
    View the server.log file to see details of client requests and responses.

Future Enhancements

    Support for additional HTTP methods (e.g., POST, PUT).
    Dynamic routing and path parsing.
    Improved error handling and robust HTTP request parsing.
    Integration with SSL/TLS for HTTPS support.
    A thread pool for better scalability.
    Authentication for protected endpoints.

Author

This project is an exploration of networking and multithreaded programming in C++. It demonstrates how to build a foundational web server from scratch, serving as a learning tool and a starting point for further enhancements.

If you'd like to contribute, share feedback, or collaborate, feel free to reach out! 😊
