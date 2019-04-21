#include "symbol.hpp"
#include <ctype.h>
using namespace typy::symbol;

Word::Word(Stream& stream) {
    if(stream.getc(word, [](char c){ return isalpha(c) || c == '_' || c >= 128; })) {
        while(stream.getc(word, [](char c){ return isalnum(c) || c == '_' || c >= 128; }));
    }
}

Integer::Integer(Stream& stream) {
    std::string str;

    stream.getc(str, [](char c){ return c == '-'; });
    while(stream.getc(str, isdigit));
    
    value = std::stoi(str);
}

Double::Double(Stream& stream) {
    std::string str;

    stream.getc(str, [](char c){ return c == '-'; });
    while(stream.getc(str, isdigit));
    stream.getc(str, [](char c){ return c == '.'; });
    while(stream.getc(str, isdigit));

    value = std::stod(str);
}