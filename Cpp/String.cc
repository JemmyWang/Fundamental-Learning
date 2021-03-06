/*
 * Created by Jemmy on 2018/8/20.
 *
 */
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class String{
    friend ostream& operator<<(ostream&, const String&);
    friend istream& operator>>(istream&, const String&);
public:
    String() = default;
    String(const char*);
    String(const String&);
    String(String&&) noexcept;
    String& operator=(const String&);
    String& operator=(String&&) noexcept;
    String operator+(const String&);
    char& operator[](unsigned int);
    bool operator==(const String&);
    size_t size() {
        return strlen(data);
    }
    ~String() {
        delete[] data;
    }
private:
    char *data;
};

inline String::String(const char *str) {
    if (!str) {
        data = nullptr;
    } else {
        data = new char[strlen(str)+1];
        strcpy(data, str);
    }
}

inline String::String(const String& other) {
    if (other.data) {
        data = new char[strlen(other.data)+1];
        strcpy(data, other.data);
    } else {
        data = nullptr;
    }
}

inline String::String(String&& other) noexcept {
    data = other.data;
    other.data = nullptr;
}

inline String& String::operator=(const String& other) {
    if (this != &other) {
        delete[] data;
        if (other.data) {
            data = new char[strlen(other.data)+1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

inline String& String::operator=(String&& other) noexcept {
    data = other.data;
    other.data = nullptr;

    return *this;
}


inline String String::operator+(const String& other) {
    String newString;

    if (!other.data) {
        newString = *this;
    } else if (!data) {
        newString = other;
    } else {
        newString.data = new char[strlen(data)+strlen(other.data)+1];
        strcpy(newString.data, data);
        strcat(newString.data, other.data);
    }

    return newString;
}

inline char &String::operator[](unsigned int pos) {
    if (pos >= 0 && pos <= strlen(data)) {
        return data[pos];
    }

    throw std::out_of_range(std::to_string(pos) + " out of range [0, " + std::to_string(strlen(data)) + "}");
}

inline bool String::operator==(const String& other) {
    if (strlen(data) != strlen(other.data))
        return false;
    return strcmp(data, other.data) ? false : true;
}

ostream &operator<<(ostream &os, const String& str) {
    os << str.data;
    return os;
}

istream &operator>>(istream &is, const String& str) {
    is>>str.data;
    return is;
}

int main() {
    String str("hello world");
    cout << str << endl;
    String ss;
    ss = str;
    ss = ss + " Ni hao";
    ss[0] = 'A';
    cout << ss << endl;
}