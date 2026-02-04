#include <iostream>
#include "morfeusz2.h"

int main() {
    std::cout << "Hello, Linux!" << std::endl;

    morfeusz::Morfeusz *m = morfeusz::Morfeusz::createInstance();
    m->setCharset(morfeusz::UTF8);

    std::vector<morfeusz::MorphInterpretation> r;
    m->analyse("Załóż gąbkę na klawesyn.", r);

    for (const auto &i : r) {
        std::cout << i.orth << std::endl;
    }
}