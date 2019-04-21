#include <string>
#include <fstream>
#include <iterator>
#include <memory>

namespace typy {

    class Stream {
    private:
        class Source {
        private:
            std::string str;

        public:
            Source(std::string str);
            Source(std::ifstream& ifs);

            size_t size() const;
            char getc(size_t index) const;

        };
        
        std::shared_ptr<Source> source;
        size_t index;

    public:
        Stream(std::shared_ptr<Source> source, size_t index = 0);
        Stream(std::string str, size_t index = 0);
        Stream(std::ifstream& ifs, size_t index = 0);

        Stream& operator >>(char& c);
        explicit operator bool() const;
        
    };

}