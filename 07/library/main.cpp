#include "library.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*
* Get the file name from user
*/
string get_file_name(string message){
    string filename = "";
    cout << message;
    getline(cin, filename);
    return filename;
}

/*
 * Split the library info line
 */
std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

/*
 * Check if the line from file has all the values
 */
bool check_line_validity(std::string line){
    if (line != ""){
        std::vector<std::string> strings = split(line, ';', true);
        if(strings.size() < 4 || strings[0] == "" || strings[1] == "" || strings[2] == "" || strings[3] == ""){
            cout<<"Error: empty field"<<endl;
            return false;
        }
        return true;
    } else {
        cout<<"Error: empty field"<<endl;
        return false;
    }
}

/*
 * Store the library info into a map and return a map value to parent function
 */

std::map<std::string, std::vector<Book>> save_line_to_container(std::string line, std::map<std::string, std::vector<Book>> libraries){
    std::string library_name = "";
    std::string author_name = "";
    std::string book_name = "";

    // initialize the reservation value as 0, this '0' won't be changed if
    // number_of_reservations info in the line is "on-the-shelf"
    int availability = 0;

    std::vector<std::string> strings = split(line, ';', true);  // split the input line from file

    library_name    = strings[0];
    author_name     = strings[1];
    book_name       = strings[2];

    if(strings[3] != "on-the-shelf"){
        // if the reservation value is not "on-the-shelf", then convert the value from string to int
        availability =  std::stol(strings[3]);
    }
    const Book& book = {book_name, author_name, availability}; // create a object using Book struct for parameter values
    libraries[library_name].push_back(book);  // push the book vector to the map with it's own lirary as key
    return libraries;
}

int main()
{
    std::vector<Book> books;
    std::map<std::string, std::vector<Book>> libraries;

    Library lib = Library();
    string input_file = get_file_name("Input file: ");  // get input file name

    ifstream file_object(input_file);
    if ( not file_object ) {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    } else {
        string line;
        while ( getline(file_object, line) ) {
            if(check_line_validity(line)){
                std::vector<std::string> strings = split(line, ';', true);
                libraries = save_line_to_container(line, libraries);
            } else {
                return EXIT_FAILURE;
            }
        }
    }
    file_object.close();

    while(true){
        std::string command_input;
        std::cout << "> ";
        getline(std::cin, command_input);

        std::vector<std::string> parts = split(command_input, ' ', true);

        std::string command = parts.at(0);
        if(command == "libraries"){
            lib.libraries_list(libraries);
        } else if (command == "material") {

            std::string library_name = parts.at(1);
            lib.material(libraries, library_name);

        } else if (command == "books") {

            if(parts.size() < 3){  // check if the command has 3 parts or not
                std::cout << "Error: error in command books" << std::endl;
            } else {
                std::string library_name = parts.at(1);
                std::string author_name = parts.at(2);
                lib.books(libraries, library_name, author_name);
            }

        } else if (command == "reservable") {

            std::string::size_type pos;
            pos = command_input.find(" ", 0);
            std::string book_name = command_input.substr(pos+1, command_input.length());

            char first = book_name[0];
            char end = book_name.back();

            if (first == '"' && end == '"'){  // check if the book name has '"' character at it's beginning or end position
                book_name = book_name.substr(1, book_name.size() - 2);
            }
            lib.reservable(libraries, book_name);

        } else if (command == "loanable") {
            lib.loanable(libraries);
        } else if(command == "quit"){
            return EXIT_SUCCESS;
         } else {
             std::cout << "Error: Unknown command: "<<command<< std::endl;
         }
    }
}
