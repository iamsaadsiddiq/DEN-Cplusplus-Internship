#include <iostream>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <fstream>
using namespace std;

#pragma comment(lib, "ws2_32.lib") 

template <typename T>
string to_string_custom(T value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

void handleClient(SOCKET clientSocket) {
    const int bufferSize = 1024;
    char buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived > 0) {
        cout << "Request: " << buffer << endl;

        string htmlContent;
        ifstream file("index.html"); 
        if (file.is_open()) {
            htmlContent.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
        }
        else {
            htmlContent = "<html><body><h1>404 Not Found</h1><p>The requested file was not found.</p></body></html>";
        }

        string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + to_string_custom(htmlContent.size()) + "\r\n\r\n" + htmlContent;

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
    }

    closesocket(clientSocket);
}

void createHtmlFile() {
    string title, bodyContent;

    cout << "Enter title for the HTML page: ";
    cin.ignore();
    getline(cin, title); 
    cout << "Enter body content for the HTML page: ";
    getline(cin, bodyContent); 


    ofstream outFile("index.html");
    outFile << "<html>\n<head>\n<title>" << title << "</title>\n</head>\n<body>\n<h1>" << title << "</h1>\n<p>" << bodyContent << "</p>\n</body>\n</html>";
    outFile.close();

    cout << "HTML file created/overwritten successfully!\n";
}

void startServer(int port) {
  
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Failed to initialize Winsock." << endl;
        return;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Failed to create socket." << endl;
        WSACleanup();
        return;
    }

    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Failed to bind to port." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

  
    if (listen(serverSocket, 10) == SOCKET_ERROR) {
        cerr << "Failed to listen on socket." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Server started on port " << port << endl;
    vector<thread> threads;

   
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cerr << "Failed to accept client connection." << endl;
            continue;
        }

        threads.emplace_back(handleClient, clientSocket);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    
    closesocket(serverSocket);
    WSACleanup();
}

int main() {
    int port;
    int choice;
    thread serverThread;  

    do {
        cout << "Multi-threaded Web Server Menu\n";
        cout << "1. Start server\n";
        cout << "2. Create/Overwrite HTML file\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter port number: ";
            cin >> port;

            
            if (serverThread.joinable()) {
                serverThread.join();  
            }

          
            serverThread = thread(startServer, port);

            cout << "Access your server at: http://localhost:" << port << endl;
            break;
        case 2:
            createHtmlFile(); 
            break;
        case 3:
            cout << "Exiting...\n";

            
            if (serverThread.joinable()) {
                serverThread.join();
            }
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 3);

    return 0;
}
