#ifndef __STRING_HPP
#define __STRING_HPP

#include <iostream>

class String
{
    private:
        char* string;
        size_t size;

        void copy(const String& other);
        void deallocate();

    public:
        String();
        String(const char* string);
        String(const String& other);
        ~String();
        
        String& operator = (const String& other);

        char& at(size_t pos);
        const char& at(size_t pos) const;

        char& operator [] (size_t pos);
        const char& operator [] (size_t pos) const;

        char& front();
        const char& front() const;

        char& back();
        const char& back() const;

        bool empty() const;

        size_t getSize() const;
        const char* c_str() const noexcept;

        void push_back(char c);
        void pop_back();

        String& operator += (char c);
        String& operator += (const String& rhs);

        String operator + (char c) const;
        String operator + (const String& rhs) const;

        bool operator == (const String& rhs) const;
        bool operator < (const String& rhs) const;

        friend std::ostream& operator << (std::ostream& out, const String& string);        
};

#endif
