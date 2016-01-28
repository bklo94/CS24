// words2.h - version 2 of class Words

#include <string>

#ifndef WORDS2_H
#define WORDS2_H

namespace lab04_2
{
    class Words
    {
    public:
        Words(unsigned int initial_capacity = 10); // revised
        Words(const Words &source); // new
        ~Words(); // new
        
        void append(std::string word);
        std::string& operator[] (unsigned int index);
        void operator=(const Words &source); // new
        
        unsigned int size() const;
        unsigned int get_capacity() const;
        std::string operator[] (unsigned int index) const;
        
    private:
        std::string *data; // now a pointer
        unsigned int used;
        unsigned int capacity;
    };

}

#endif
