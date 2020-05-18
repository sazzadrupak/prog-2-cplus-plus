#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "N                  = List ordered by student numbers\n"
                              "U                  = List ordered alphabetically by user ids\n"
                              "C <student_number> = Change the given student's phone number\n"
                              "Q                  = Quit\n";

struct Student {
    std::string student_number;
    std::string user_id;
    std::string name;
    std::string phone_number;
    std::string email;
    std::string skype;
};

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool read_data(const std::string file_name,
               std::map< std::string, Student* >& alphabetical_order,
               std::map< std::string, Student* >& numerical_order) {
    std::ifstream file_object(file_name);
    if( !file_object ) {
        return false;
    }

    std::string line = "";

    while( getline( file_object, line ) ) {
        std::vector<std::string> parts = split(line, ';');
        if(parts.size() != 6) {
            return false;
        }

        Student* new_student = new Student({parts[0], parts[1], parts[2], parts[3], parts[4], parts[5]});
        numerical_order[parts[0]] = new_student;
        alphabetical_order[parts[1]] = new_student;
    }
    file_object.close();
    return true;
}


void print_data(const Student o) {
    std::cout << o.student_number << " " << o.user_id << std::endl
              << o.name << std::endl
              << o.phone_number << std::endl
              << o.email << std::endl
              << o.skype << std::endl << std::endl;
}

bool is_valid_phone_number(const std::string number) {
    for(unsigned int i = 0; i < number.length(); ++i) {
        if(!(('0' <= number[i] && number[i] <= '9') || number[i] == ' ' || number[i] == '-')) {
            std::cout << "Erroneous phone number: " << number << std::endl << std::endl;
            return false;
        }
    }
    return true;
}

bool modify_file(const std::string phn_number, const std::string student_id, std::string output_file, std::map< std::string, Student* >& student_map){
    std::ofstream myfile;
    myfile.open (output_file);
    std::string line;

    for(auto pair: student_map) {
        if(pair.second->student_number == student_id){
            myfile << pair.second->student_number << ";" << pair.second->user_id << ";" << pair.second->name << ";" << phn_number << ";" << pair.second->email << ";" << pair.second->skype << std::endl;
        } else {
            myfile << pair.second->student_number << ";" << pair.second->user_id << ";" << pair.second->name << ";" << pair.second->phone_number << ";" << pair.second->email << ";" << pair.second->skype << std::endl;
        }
    }
    return true;
}

int main() {
    std::string file_name = "";
    std::cout << "Student file: ";
    std::getline(std::cin, file_name);

    std::map< std::string, Student* > user_ids;
    std::map< std::string, Student* > student_numbers;
    if(not read_data(file_name, user_ids, student_numbers)) {
        std::cout << "Error in reading file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << HELP_TEXT << std::endl;

    while(true) {
        std::string line;
        std::cout << "register> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        if(parts.empty()) {
            continue;
        }
        std::string command = parts.at(0);

        // Printing in alphabetical order by user ids
        if(command == "U" or command == "u") {
            if(parts.size() != 1) {
                std::cout << "Erroneous parameters!" << std::endl  << HELP_TEXT;
                continue;
            } else {
                for(auto pair: user_ids) {
                    print_data(*(pair.second));
                }
            }

            // Printing in numerical order by student numbers
        } else if(command == "N" or command == "n") {
            if(parts.size() != 1){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            } else {
                for(auto pair: student_numbers) {
                    print_data(*(pair.second));
                }
            }

            // Changing student data
        } else if(command == "C" or command == "c") {
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            } else {
                std::string student_id = parts.at(1);
                Student* some_struct = nullptr;
                some_struct = student_numbers[student_id];
                if(student_numbers[student_id]){
                    std::string phone_number;
                    std::cout << "Enter a new phone number: ";
                    getline(std::cin, phone_number);
                    std::cout << "\n";
                    bool is_valid = is_valid_phone_number(phone_number);
                    if(is_valid == true){
                        student_numbers[student_id]->phone_number = phone_number;
                        user_ids.at(some_struct->user_id)->phone_number = phone_number;
                        modify_file(phone_number, student_id, file_name, student_numbers);
                    }
                } else {
                    std::cout << "There is no student with the given number!" << std::endl;
                    continue;
                }
            }
        } else if(command == "Q" or command == "q") {
            // Deleting the data structure: deallocating memory and nullifying pointers
            for(auto pair: student_numbers) {
                pair.second = nullptr;
            }

            for(auto pair: user_ids) {
                delete pair.second;
                pair.second = nullptr;
            }

            return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}


