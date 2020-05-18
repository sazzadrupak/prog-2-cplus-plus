#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <map>
#include <vector>

// Define a struct called Book to bundle book name and availability.
struct Book {
    std::string title;
    std::string author;
    int reservation;
};  // struct Book

// Define a struct called Book to bundle library name and availability for reservable command.
struct Lib {
    std::string library_name;
    int reservation;
};  // struct Library

class Library
{
public:
    Library();
    void libraries_list(std::map<std::string, std::vector<Book>> libraries);
    void material(std::map<std::string, std::vector<Book>> libraries, std::string library);
    void books(std::map<std::string, std::vector<Book>>libraries, std::string library_name, std::string author_name);
    void reservable(std::map<std::string, std::vector<Book>>libraries, std::string book_name);
    void loanable(std::map<std::string, std::vector<Book>>libraries);

private:
    bool compareByAuthor(const Book &a, const Book &b);
};

#endif // LIBRARY_HH
