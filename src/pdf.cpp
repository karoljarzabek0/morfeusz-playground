#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <array>
#include <stdexcept>

// Cross-platform defines for pipe functions
#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
    #define READ_MODE "rt"
#else
    #define POPEN popen
    #define PCLOSE pclose
    #define READ_MODE "r"
#endif

std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;

    // Open the pipe
    FILE* pipe = POPEN(cmd.c_str(), READ_MODE);
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    try {
        // Read until end of file
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
            result += buffer.data();
        }
    } catch (...) {
        PCLOSE(pipe);
        throw;
    }

    PCLOSE(pipe);
    return result;
}

int main() {
    // Note: We wrap the path in quotes to handle potential spaces 
    // and add '-' to tell pdftotext to output to stdout.
    
#ifdef _WIN32
    std::string command = "\"external\\xpdf\\bin\\pdftotext.exe\" -enc UTF-8 data/test.pdf -";
#else
    std::string command = "./external/xpdf/bin/pdftotext -enc UTF-8 data/test.pdf -";
#endif

    try {
        std::cout << "Running command: " << command << std::endl;
        std::string output = exec(command);
        std::cout << "--- Captured Output ---\n" << output << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}