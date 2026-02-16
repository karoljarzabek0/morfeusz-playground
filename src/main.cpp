#include <iostream>
#include <fstream>
#include <unordered_map>
#include "morfeusz/include/morfeusz2.h"


void printMorfSummary(morfeusz::Morfeusz *m, std::string text) {
    std::unordered_map<std::string, int> counts = {
            {"valid_words", 0},
            {"ignored_words", 0},
            {"total_words", 0}
        };

    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);

    for (const auto &i : r) {
        counts["total_words"] += 1;
        if (i.isIgn()) {
            counts["ignored_words"] += 1;
        } else {
            counts["valid_words"] += 1;
        }
    }

    std::cout << "Valid: " << counts["valid_words"] 
              << " | Ignored: " << counts["ignored_words"] << std::endl;

}

void printDetailedMorfSummary(morfeusz::Morfeusz *m, std::string text) {
    std::unordered_map<std::string, int> tagSum;
    std::unordered_map<std::string, int> nameSum;
    std::unordered_map<std::string, int> labelSum;


    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);

    for (const auto &i : r) {
        tagSum[i.getTag(*m)]++;
        nameSum[i.getName(*m)]++;
        labelSum[i.getLabelsAsString(*m)]++;
        }

    std::cout << "Tags:\n";

    for (const auto &i : tagSum) {
        std::cout << i.first << ": " << i.second << std::endl;;
    }

    std::cout << "Names:\n";

    for (const auto &i : nameSum) {
        std::cout << i.first << ": " << i.second << std::endl;;
    }

    std::cout << "Lables:\n";

    for (const auto &i : labelSum) {
        std::cout << i.first << ": " << i.second << std::endl;;
    }

}



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
        std::cout << i.orth 
            << " -> "
            << i.lemma << ", "
            << "Tag: " << i.getTag(*m) << ", "
            << "Name: " << i.getName(*m) << ", "
            << "Label: " << i.getLabelsAsString(*m) << ", "
            << std::endl;
    }
}


int main() {

    morfeusz::Morfeusz *m = morfeusz::Morfeusz::createInstance();
    m->setCharset(morfeusz::UTF8);
    m->setCaseHandling(morfeusz::CONDITIONALLY_CASE_SENSITIVE);
    m->setAggl("permissive");
    m->setPraet("composite");

    auto testText = readFile("test.txt");

    auto results = detectUnknownWords(m, testText);
    
    for (const auto &i : results) {
        std::cout << i << " ";
        //std::cout << std::endl;
    }
    std::cout << std::endl;

    //printResults(m, testText);
    printMorfSummary(m, testText);
    printDetailedMorfSummary(m, testText);

    delete m;

}