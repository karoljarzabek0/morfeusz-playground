#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <array>
#include <stdexcept>

#include "pdf.h"

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
    #define READ_MODE "rt"
#else
    #define POPEN popen
    #define PCLOSE pclose
    #define READ_MODE "r"
#endif

// Function that executes a CLI command and retrun its stdout
std::string exec(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;


    FILE* pipe = POPEN(cmd.c_str(), READ_MODE);
    if (!pipe) {
        throw std::runtime_error("popen() failed");
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

Pdf::Pdf(const std::string path) {
    this->path = path;
}

std::string Pdf::getText() {
    // If we already processed it, don't do it again (Caching)
    if (!text.empty()) {
        return text;
    }

    // Logic for the command strings
    #ifdef _WIN32
        std::string command = "\"external\\xpdf\\bin\\pdftotext.exe\" -enc UTF-8 " + path + " -";
    #else
        std::string command = "./external/xpdf/bin/pdftotext -enc UTF-8 " + path + " -";
    #endif

    try {
        // Assuming exec() is a global helper or defined elsewhere
        // We assign the result directly to our private 'text' variable
        this->text = exec(command); 
        return text;
    } catch (const std::exception& e) {
        std::cerr << "Error extracting PDF: " << e.what() << std::endl;
        return "";
    }
}

#ifdef DEBUG
int main() {
    Pdf test_pdf("data/test.pdf");

    std::cout << test_pdf.getText() << std::endl;;

    return 0;
}
#endif