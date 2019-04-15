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

};

struct Symbol : public WordSet {
    char symbol;
    Symbol(char symbol) : symbol(symbol) {}
};

struct Word : public WordSet {
    std::string word;
    Word(std::string word) : word(word) {}
};

struct MultiWordSet : public WordSet {
    std::vector<std::unique_ptr<WordSet>> children;
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
    Line(Indent indent, WordSet* words)
        : indent(indent), words(words) {}
};



int main(int argc, char *argv[]) {

//  文字の種類から単語に区切る
    CharType prev_type = CharType::Space;
    std::string word;
    std::unique_ptr<MultiWordSet> words(new MultiWordSet());
    bool is_indent = true;
    Line::Indent indent;
    std::vector<Line> lines;

    while(true) {
        int c = getchar();

        CharType type = getCharType(c);

        if(prev_type != type) {
            if(word.length()) {
                words->children.push_back(std::make_unique<Word>(word));
                word.clear();
            }
        }

        std::cout << c << "\n";

        if(c == ' ') {
            if(is_indent) indent.n_space++;
        }
        else if(c == '\t') {
            if(is_indent) indent.n_tab++;
        }
        else if(c == '\n' || c == ';' || c == EOF) {
            std::cout << "EOL (indent s:" << indent.n_space << ", tab:" << indent.n_tab << ")\n";
            lines.push_back(Line(indent, words.get()));
            indent.clear();
            words.reset(new MultiWordSet());
            is_indent = true;
        }
        else{
            is_indent = false;
            if(type == CharType::Symbol) {
                words->children.push_back(std::make_unique<Symbol>(c));
            }
            else{
                word.push_back(c);
            }
        }

        prev_type = type;

        if(c == EOF) break;
    }

    return 0;
}