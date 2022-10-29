#include "string.hpp"

#include <cassert>
#include <cstring>
#include <exception>

String::String() : string(nullptr), size(0)
{ }

String::String(const char* string)
{
    if(!string)
    {
        this->string = nullptr;
        this->size = 0;
    }
    else
    {
        char* buffer = nullptr;
        size_t size = strlen(string);

        try
        {
            buffer = new char[size + 1];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }
        
        strcpy(buffer, string);
        this->string = buffer;
        this->size = size;
    }
}

String::String(const String& other)
{
    this->copy(other);
}

String::~String()
{
    this->deallocate();
}

String& String::operator = (const String& other)
{
    if(this != &other)
    {
        this->deallocate();
        this->copy(other);
    }
    return *this;
}

void String::copy(const String& other)
{
    if(!other.string)
    {
        this->string = nullptr;
        this->size = 0;
    }
    else
    {
        char* buffer = nullptr;

        try
        {
            buffer = new char[other.size + 1];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        strcpy(buffer, other.string);
        this->string = buffer;
        this->size = other.size;
    }
}

void String::deallocate()
{
    delete[] this->string;
    this->string = nullptr;
}

char& String::at(size_t pos)
{
    if(pos >= this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->string[pos];
}

const char& String::at(size_t pos) const
{
    if(pos >= this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->string[pos];
}

char& String::operator [] (size_t pos)
{
    if(pos >= this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->string[pos];
}

const char& String::operator [] (size_t pos) const
{
    if(pos == this->size)
    {
        return '\0';
    }
    else if(pos > this->size)
    {
        throw std::out_of_range("Invalid index!");
    }
    return this->string[pos];
}

char& String::front()
{
    assert(!this->empty());
    return this->string[0];
}

const char& String::front() const
{
    assert(!this->empty());
    return this->string[0];
}

char& String::back()
{
    assert(!this->empty());
    return this->string[this->size - 1];
}

const char& String::back() const
{
    assert(!this->empty());
    return this->string[this->size - 1];
}

bool String::empty() const
{
    return this->size == 0;
}

size_t String::getSize() const
{
    return this->size;
}

const char* String::c_str() const noexcept
{
    return this->string;
}

void String::push_back(char c)
{
    if(c == '\0')
    {
        return;
    }

    char* newString = nullptr;
    size_t newSize = this->size + 1;

    try
    {
        newString = new char[newSize + 1];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

    if (!this->empty())
    {
        strcpy(newString, this->string);
    }

    newString[this->size] = c;
    newString[this->size + 1] = '\0';

    this->deallocate();

    this->string = newString;
    this->size = newSize;    
}

void String::pop_back()
{
    assert(!this->empty());

    if (this->size == 1)
    {
        this->deallocate();
        return;
    }

    this->string[this->size - 1] = '\0';
    this->size--;
}

String& String::operator += (char c)
{
    this->push_back(c);
    return *this;
}

String& String::operator += (const String& rhs)
{
    if (!this->string)
    {
        *this = rhs;
        return *this;
    }

    if(!rhs.string)
    {
        return *this;
    }

    size_t newSize = this->size + rhs.size;
    char* newString = nullptr;

    try
    {
        newString = new char[newSize + 1];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return *this;
    }

    strcpy(newString, this->string);
    strcat(newString, rhs.string);
    newString[newSize] = '\0';
    
    this->deallocate();

    this->string = newString;
    this->size = newSize;    
}

String String::operator + (char c) const
{
    String newString = *this;
    newString += c;
    return newString;
}

String String::operator + (const String& rhs) const
{
    String newString = *this;
    newString += rhs;
    return newString;
}

bool String::operator == (const String& rhs) const
{
    if (this->size != rhs.size)
    {
        return false;
    }

    if (this->empty())
    {
        return true;
    }

    return strcmp(this->string, rhs.string) == 0;
}

bool String::operator < (const String& rhs) const
{
    if(this->empty())
    {
        return true;
    }

    if(rhs.empty())
    {
        return false;
    }

    return strcmp(this->string, rhs.string) < 0;
}

std::ostream& operator << (std::ostream& out, const String& string)
{
    if(!string.empty())
    {
        out << string.c_str();
    }
    return out;
}
