#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector<std::string> split( std::string line, char separator, bool empty_string = false){
    std::string::size_type pos = 0;
    std::vector<std::string> result;

    while(line.size() > 0){
        pos = line.find(separator);
        if(pos != std::string::npos){
            if(!empty_string){
                result.push_back(line.substr(0, pos));
            } else {
                if(line.substr(0, pos) != ""){
                    result.push_back(line.substr(0, pos));
                }
            }

            line = line.substr(pos+1);

            if(line.size() == 0)result.push_back(line);
        } else {
            result.push_back(line);
            line = "";
        }
    }
    return result;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        std::cout << o << std::endl;
    }
}
