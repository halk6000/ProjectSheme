#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
double ServerVersion = 0.01; // Wersja serwera
double ClientVersion;

double convertToDouble(char* buffer); // Deklaracja funkcji

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    char buffer[1024];

    // Inicjalizacja Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Utworzenie gniazda serwera
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;

    std::string ipInput;
    std::cout << "Podaj adres IP serwera (wpisz 'local' dla lokalnego adresu lub konkretny adres IP): ";
    std::cin >> ipInput;

    if (ipInput == "local") {
        serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Lokalny adres IP (127.0.0.1)
    } else {
        serverAddr.sin_addr.s_addr = inet_addr(ipInput.c_str()); // Konkretny adres IP podany przez użytkownika
    }

    serverAddr.sin_port = htons(5555);

    // Powiązanie gniazda z adresem i portem
    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    // Nasłuchiwanie połączeń przychodzących
    listen(serverSocket, 0);

    std::cout << u8"Serwer jest uruchomiony i nasłuchuje na porcie 5555...\n";

    // Akceptacja połączenia
    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
    std::cout << u8"Połączenie z klientem nawiązane.\n";

    // Odbieranie danych od klienta
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string receivedData = buffer;

    // Logika sprawdzająca i aktualizująca pliki
    if (receivedData == "dom") {
        // Logika sprawdzania różnic w wersji, aktualizacji plików, itp.

        // Odpowiedź klientowi "true" i oczekiwanie na ClientVersion
        send(clientSocket, "true", 4, 0);

        // Odbierz ClientVersion od klienta
        char VersionBuffer[20]; // Załóżmy, że maksymalna długość wersji to 20 znaków
        recv(clientSocket, VersionBuffer, 20, 0);
        ClientVersion = convertToDouble(VersionBuffer);

        // Załadowanie biblioteki DLL
        HINSTANCE hDLL = LoadLibrary("SynhV.dll");

        if (hDLL != NULL) {
            // Pobranie funkcji SynthVMainF z biblioteki DLL
            typedef void (*SynthVFunction)(double, double);
            SynthVFunction SynthVF = (SynthVFunction)GetProcAddress(hDLL, "SynthVMainF");

            if (SynthVF != NULL) {
                // Wywołanie funkcji SynthVMainF przekazując wersje serwera i klienta

                SynthVF(ServerVersion, ClientVersion);
            }
            // Zwolnienie biblioteki DLL
            FreeLibrary(hDLL);
        }

    } else {
        send(clientSocket, "false", 5, 0);
    }

    // Zamknięcie gniazd
    closesocket(clientSocket);

    return 0;
}

double convertToDouble(char* buffer) {
    std::string versionString(buffer); // Konwersja bufora na łańcuch znaków
    return std::stod(versionString); // Konwersja łańcucha znaków na typ double
}
