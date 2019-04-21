#include "stream.hpp"
using namespace typy;

Stream::Source::Source(std::string str)
    : str(str) {}

Stream::Source::Source(std::ifstream& ifs)
    : str({std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()}) {}

size_t Stream::Source::size() const {
    return str.size();
}

char Stream::Source::getc(size_t index) const {
    return str[index];
}

Stream::Stream(std::shared_ptr<Source> source, size_t index)
    : source(source), index(index) {}

Stream::Stream(std::string str, size_t index)
    : source(std::make_shared<Source>(str)), index(index) {}

Stream::Stream(std::ifstream& ifs, size_t index)
    : source(std::make_shared<Source>(ifs)), index(index) {}

char Stream::getc() {
    return source->getc(index++);
}

void Stream::getc(char& c) {
    c = getc();
}

bool Stream::getc(char& c, std::function<bool(char)> is_valid) {
    if(!is_valid(source->getc(index))){
        getc(c);
        return true;
    }
    return false;
}

void Stream::getc(std::string& str) {
    str.push_back(getc());
}

bool Stream::getc(std::string& str, std::function<bool(char)> is_valid) {
    if(!is_valid(source->getc(index))){
        getc(str);
        return true;
    }
    return false;
}

Stream& Stream::operator >>(char& c) {
    c = getc();
    return *this;
}

Stream::operator bool() const {
    return index < source->size();
}