#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

void print_numbers(const map<string, int>& players);

string get_file_name(string message){
    string filename = "";
    cout << message;
    getline(cin, filename);
    return filename;
}

/*
* Read from file and
* counting points
*/

bool read_from_file(string input_file){
    ifstream file_object(input_file);
    if ( not file_object ) { // read failed
        cout << "Error! The file "<< input_file <<" cannot be opened." << endl;
        return false;
    } else { // read succeeded
        map<string, int> all_number_map;
        string line;
        string name;
        unsigned int point = 0;

        // loop through every line
        while ( getline(file_object, line) ) {
            const size_t pos1 = line.find(':');
            if (string::npos != pos1){  // split the line and put value to two variable
                name = line.substr(0, pos1);
                point = atoi(line.substr(pos1 + 1).c_str());
            }

            map<string, int>::iterator point_iter;
            point_iter = all_number_map.find(name);

            if ( point_iter == all_number_map.end() ) { // name not found in map, insert as a new copy
                all_number_map.insert({ name, point });
            } else {  // name found, update to point
                int number_value = all_number_map.at(name);
                all_number_map[name] = number_value + point;
            }
        }
        print_numbers(all_number_map);  // print the players individual total points
        file_object.close();
        return true;
    }
}

/*
* Print the names of the players, each on their own line
* with their final point
*/
void print_numbers(const map<string, int>& players){
    cout<<"Final scores:"<<endl;
    for ( auto item : players ) {
        cout<<item.first<<": "<< item.second <<endl;
    }
}

int main()
{
    string input_file = get_file_name("Input file: ");  // get input file name

    if(read_from_file(input_file)){ // read from file succeeded
        return EXIT_SUCCESS;
    } else { // read from file failed
        return EXIT_FAILURE;
    }
}
