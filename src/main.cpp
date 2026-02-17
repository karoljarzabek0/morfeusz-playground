//[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>

#include "morfeusz2.h"
#include "pdf.h"

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
    std::map<std::string, int> tagSum;
    std::map<std::string, int> nameSum;
    std::map<std::string, int> labelSum;


    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);

    for (const auto &i : r) {
        tagSum[i.getTag(*m)]++;
        nameSum[i.getName(*m)]++;
        labelSum[i.getLabelsAsString(*m)]++;
        }

    auto printSorted = [](const std::string& title, const std::map<std::string, int>& summaryMap) {
        std::vector<std::pair<std::string, int>> sortedVec(summaryMap.begin(), summaryMap.end());

        std::sort(sortedVec.begin(), sortedVec.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        std::cout << title << ":\n";
        for (const auto& pair : sortedVec) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
        std::cout << "\n";
    };

    printSorted("Tags", tagSum);
    printSorted("Names", nameSum);
    printSorted("Labels", labelSum);

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

std::unordered_map<std::string, int> detectUnknownWords(morfeusz::Morfeusz *m, std::string text) {
    std::unordered_map<std::string, int> unknownWords;

    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse(text, r);
    for (const auto &i : r) {
        if (i.isIgn()) {
            unknownWords[i.orth]++;
        }
    }

    auto printSorted = [](const std::string& title, const std::unordered_map<std::string, int>& summaryMap) {
        std::vector<std::pair<std::string, int>> sortedVec(summaryMap.begin(), summaryMap.end());
        std::sort(sortedVec.begin(), sortedVec.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        std::cout << title << ":\n";
        for (const auto& pair : sortedVec) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
        std::cout << "\n";
    };

    printSorted("Unknown words", unknownWords);


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

    Pdf test_pdf("data/test.pdf");

    auto testText = readFile("data/test.txt");

    detectUnknownWords(m, test_pdf.getText());
    
    //printResults(m, testText);
    //printMorfSummary(m, testText);
    //printDetailedMorfSummary(m, testText);

    delete m;

}