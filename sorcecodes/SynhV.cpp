#include <iostream>

namespace SynhV {
    double ServerVersion; // Inicjalizacja wartości dla serverVersion
    double ClientVersion; // Inicjalizacja wartości dla clientVersion

    void setServerVersion(double ServerVersion) {
        ServerVersion = ServerVersion;
    }

    void setClientVersion(double ClientVersion) {
        ClientVersion = ClientVersion;
    }
	void SynthVMainF(double ServerVersion, double ClientVersion) {
        // Kod funkcji SynthVMainF
    }
}

int main() {

    double versionDifference = SynhV::ServerVersion - SynhV::ClientVersion;
    int numIterations = static_cast<int>(versionDifference / 0.01); // Konwersja na int

    std::cout << "Liczba iteracji: " << numIterations << std::endl;

    double currentVersion = SynhV::ClientVersion;

    while (numIterations > 0) {
        currentVersion += 0.01;

        if (currentVersion == 0.50) {
            std::cout << "Znaleziono zmienione pliki dla wersji 0.50" << std::endl;
        } else if (currentVersion == 0.51) {
            std::cout << "Znaleziono zmienione pliki dla wersji 0.51" << std::endl;
        } else if (currentVersion == 0.52) {
            std::cout << "Znaleziono zmienione pliki dla wersji 0.52" << std::endl;
        } else if (currentVersion == 0.53) {
            std::cout << "Znaleziono zmienione pliki dla wersji 0.53" << std::endl;
        } else if (currentVersion >= 0.54 && currentVersion <= 0.80) {
            std::cout << "Znaleziono zmienione pliki dla wersji " << currentVersion << std::endl;
        }

        numIterations--;
    }

    return 0;
}
