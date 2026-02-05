#include <iostream>
#include <fstream>
#include "morfeusz2.h"


std::string readFile(std::string filePath) {

    std::string finalContent = ""; 
    std::ifstream myFile(filePath);
    if (myFile.is_open()) {
        std::string line;
        while (std::getline(myFile, line)) {
            finalContent += line + "\n"; 
        }
        myFile.close();
        
    } else {
        std::cout << "Error: Could not open the file.\n";
    }

    return finalContent;
}

std::set<std::string> detectUnknownWords(morfeusz::Morfeusz *m, std::string text) {
    std::set<std::string> unknownWords;

    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);
    for (const auto &i : r) {
        if (i.isIgn()) {
            unknownWords.insert(i.orth);
        }
    }
    return unknownWords;
}

void printResults(morfeusz::Morfeusz *m, std::string text) {
    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);

    for (const auto &i : r) {
        std::cout << "----------------" << std::endl;
        std::cout << i.orth << " -> ";
        std::cout << i.lemma << std::endl;
    }
}


int main() {
    std::cout << "Hello, Linux!" << std::endl;

    morfeusz::Morfeusz *m = morfeusz::Morfeusz::createInstance();
    m->setCharset(morfeusz::UTF8);
    m->setCaseHandling(morfeusz::IGNORE_CASE);
    m->setAggl("permissive");

    auto testText = readFile("test.txt");

    auto results = detectUnknownWords(m, testText);
    
    for (const auto &i : results) {
        std::cout << i << " ";
        //std::cout << std::endl;
    }

}