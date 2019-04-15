#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctype.h>

enum class CharType {
    Space,
    Digit,
    Letter,
    Symbol,
};

CharType getCharType(char c) {
    if(isspace(c)) return CharType::Space;
    if(isdigit(c)) return CharType::Digit;
    if(c == '_' || c >= 128 || isalpha(c)) return CharType::Letter;
    return CharType::Symbol;
}

struct WordSet {
    virtual bool push(char c) = 0;
};

struct Symbol : public WordSet {
    char symbol;
    Symbol(char symbol) : symbol(symbol) {}

    bool push(char c) override {
        symbol = c;
    }
};

struct Word : public WordSet {
    std::string word;
    Word(std::string word) : word(word) {}

    bool push(char c) override {
        word.push_back(c);
    }
};

struct MultiWordSet : public WordSet {
    std::vector<std::unique_ptr<WordSet>> children;
    CharType prev_type = CharType::Space;

    bool push(char c) override {

        CharType type = getCharType(c);

        if(prev_type != type) {
            if(word.length()) {
                words->children.push_back(std::make_unique<Word>(word));
                word.clear();
            }
        }

    }
};

struct Line {

    struct Indent {
        short n_space = 0;
        short n_tab = 0;

        void clear() {
            n_space = 0;
            n_tab = 0;
        }
    } indent;
    std::unique_ptr<WordSet> words;
    bool is_indent = true;

    Line(Indent indent, WordSet* words)
        : indent(indent), words(words) {}

    bool push(char c) {

        if(c == ' ') {
            if(is_indent) indent.n_space++;
        }
        else if(c == '\t') {
            if(is_indent) indent.n_tab++;
        }
        else if(c == '\n' || c == ';' || c == EOF) {
            return false;
        }
        else{
            is_indent = false;
            words->push(c);
        }

        return true;
    }

};



int main(int argc, char *argv[]) {

//  文字の種類から単語に区切る
    while(true) {
        int c = getchar();

        std::cout << c << "\n";

        if(c == EOF) break;
    }

    return 0;
}