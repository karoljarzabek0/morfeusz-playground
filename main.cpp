#include <format>
#include <iostream>
#include "morfeusz2.h"

std::set<std::string> detectUnknownWords(morfeusz::Morfeusz *m, std::string text) {
    // TODO
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

    auto results = detectUnknownWords(m, "Dane niekliniczne, uzyskane na podstawie konwencjonalnych badań farmakologicznych dotyczących bezpieczeństwa stosowania, toksyczności po podaniu wielokrotnym, genotoksyczności i");
    
    for (const auto &i : results) {
        std::cout << i << " ";
        std::cout << std::endl;
    }

}