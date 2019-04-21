#include "stream.hpp"
#include <string>
#include <functional>

namespace typy::symbol {

    class Symbol {
    };

    class Word : public Symbol {
    private:
        std::string word;

    public:
        Word(Stream&);
    };

    class Integer : public Symbol {
    private:
        int value;

    public:
        Integer(Stream&);
    };

    class Double : public Symbol {
    private:
        double value;

    public:
        Double(Stream&);
    };

}