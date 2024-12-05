# Multithreaded-HTTP-Server

About This Project

This project is a lightweight, multithreaded HTTP server built in C++ using the Windows Sockets (WinSock) API. It showcases fundamental concepts of networking, file handling, multithreading, and request-response mechanics for HTTP/1.1.
Features

    1. Multithreaded Client Handling
    Handles multiple clients simultaneously using separate threads, ensuring responsiveness.
    2. Rate Limiting
    Implements a basic rate-limiting mechanism to prevent request floods from the same IP.
    3. File Serving
    Serves static HTML content, such as index.html. If the file is not found, returns a 404 Not Found response.
    4. Logging
    Logs every client request to a file (server.log), including timestamps, client IP, request details, and response codes.
    5. Error Responses
    Sends appropriate HTTP error responses, including 404 Not Found and 429 Too Many Requests.

Technology Stack

    1. Programming Language: C++
    2. Networking API: WinSock2
    3. Threading: Standard C++ Threads (std::thread)
    4. File Handling: File I/O using fstream

How It Works

    1. Start the Server
    The server listens on port 8080 for incoming client connections.
    2. Client Connection
    Each client request is processed in its own thread to allow concurrent handling.
    3. Rate Limiting
    A map tracks the timestamps of the last request from each client IP. If a client sends another request within 1 second, they receive a 429 Too Many Requests response.
    4. Serving Files
    The server attempts to serve an index.html file. If the file is missing, a 404 Not Found response is sent.

How to Use

    1. Compile and Run
    Compile the program using a C++ compiler that supports WinSock2 and threading (e.g., MSVC). Run the executable on a Windows machine.
    2. Access the Server
    Open a web browser or use a tool like curl to access http://<server-ip>:8080. Ensure the index.html file is present in the same directory as the executable.
    3. Check Logs
    View the server.log file to see details of client requests and responses.

Future Enhancements

    1. Support for additional HTTP methods (e.g., POST, PUT).
    2. Dynamic routing and path parsing.
    3. Improved error handling and robust HTTP request parsing.
    4. Integration with SSL/TLS for HTTPS support.
    5. A thread pool for better scalability.
    6. Authentication for protected endpoints.

Author

This project is an exploration of networking and multithreaded programming in C++. It demonstrates how to build a foundational web server from scratch, serving as a learning tool and a starting point for further enhancements.
If you'd like to contribute, share feedback, or collaborate, feel free to reach out! 😊
