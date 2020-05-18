#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void add_word_to_map(map<string, int> &word_appeared_map, map<string, string> &word_appeared_line_map, string word_name, int line_no);
void add_line_count_to_map(map<string, string> &word_appeared_line_map, string word_name, int line_no);
void print_result(const map<string, int> &word_appeared_map, const map<string, string> &word_appeared_line_map);

/*
 * Get the file name from user.
 */
string get_file_name(string message){
    string filename = "";
    cout << message;
    getline(cin, filename);
    return filename;
}

/*
 * Read from the given file name
 */
bool read_from_file(const string &input_file){
    ifstream file_object(input_file);
    if ( not file_object ) { // read failed
        cout << "Error! The file "<< input_file <<" cannot be opened." << endl;
        return false;
    } else { // read succeeded
        map<string, int> word_appeared_map;  // map for word and number of appeared
        map<string, string> word_appeared_line_map;  // map for word and line numbers
        string line;

        unsigned int line_no = 1;  // hold the updated line number after every iteration
        while ( getline(file_object, line) ) {  // loop through every line

            size_t position = line.find(' ');
            size_t initial_pos = 0;
            string word_name = "";
            while (position != string::npos){  // loop through there is no position value for empty space
                word_name = line.substr( initial_pos, position - initial_pos );  // get the word from line
                add_word_to_map(word_appeared_map, word_appeared_line_map, word_name, line_no);  // add word and counter to map
                add_line_count_to_map(word_appeared_line_map, word_name, line_no);  // add word and line numbers to map

                initial_pos = position + 1;
                position = line.find(' ', initial_pos);
            }

            word_name = line.substr( initial_pos, std::min( position, line.size() ) - initial_pos + 1 );  // get the final word in the line
            add_word_to_map(word_appeared_map, word_appeared_line_map, word_name, line_no);  // add word and counter to map
            add_line_count_to_map(word_appeared_line_map, word_name, line_no);  // add word and line numbers to map

            line_no++;  // increment the line number
        }
        file_object.close();
        print_result(word_appeared_map, word_appeared_line_map);  // print the map result
        return true;
    }
}

/*
 * Add word and its associated appeared number to the map
 */
void add_word_to_map(map<string, int> &word_appeared_map, map<string, string> &word_appeared_line_map, string word_name, int line_no){
    map<string, int>::iterator point_iter;
    point_iter = word_appeared_map.find(word_name);

    if ( point_iter == word_appeared_map.end() ) { // name not found in map, insert as a new copy
        word_appeared_map.insert({ word_name, 1 });
    } else {  // name found in map, update the appeared number
        string line_number_value = word_appeared_line_map.at(word_name);
        size_t pos = 0;
        pos = line_number_value.find(to_string(line_no));  // find the line number

        if(pos == string::npos){  // if the line number has not been taken already, add it
            int number_value = word_appeared_map.at(word_name);
            word_appeared_map[word_name] = number_value + 1;
        }
    }
}

/*
 * Add the word and it's associated appeared line number in the map
 */

void add_line_count_to_map(map<string, string> &word_appeared_line_map, string word_name, int line_no){
    map<string, string>::iterator point_iter;
    point_iter = word_appeared_line_map.find(word_name);

    if ( point_iter == word_appeared_line_map.end() ) { // name not found in map, insert as a new copy
        word_appeared_line_map.insert({ word_name, to_string(line_no) });
    } else {  // name found in map, append the line number to the existing value
        string line_number_value = word_appeared_line_map.at(word_name);
        size_t pos = 0;
        pos = line_number_value.find(to_string(line_no));  // find the line number

        if(pos == string::npos){  // if the line number has not been taken already, add it
            string temp = ", "+to_string(line_no);
            word_appeared_line_map[word_name] = line_number_value.append(temp);
        }
    }
}

/*
 * Print the result here
 */

void print_result(const map<string, int> &word_appeared_map, const map<string, string> &word_appeared_line_map){
    for ( auto item : word_appeared_map ) {
        cout<<item.first<<" "<< item.second <<": "<< word_appeared_line_map.at(item.first) <<endl;
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
