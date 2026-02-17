#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <array>
#include <stdexcept>

class Pdf {
private:
    std::string path;
    std::string text;

public:
    // Constructor for Pdf class
    Pdf(const std::string path);
    std::string getText();
};