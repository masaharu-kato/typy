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
            Source(std::string str)
                : str(str) {}

            Source(std::ifstream& ifs)
                : str({std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>()}) {}

            size_t size() const {
                return str.size();
            }

            char getc(size_t index) const {
                return str[index];
            }

        };
        
        std::shared_ptr<Source> source;
        size_t index;

    public:
        Stream(std::shared_ptr<Source> source, size_t index = 0)
            : source(source), index(index) {}

        Stream(std::string str, size_t index = 0)
            : source(std::make_shared<Source>(str)), index(index) {}

        Stream(std::ifstream& ifs, size_t index = 0)
            : source(std::make_shared<Source>(ifs)), index(index) {}

        Stream& operator >>(char& c) {
            c = source->getc(index);
            index++;
            return *this;
        }

        explicit operator bool() const {
            return index < source->size();
        }
        
    };

}