#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string get_file_name(string message){
    string filename = "";
    cout << message;
    getline(cin, filename);
    return filename;
}

bool read_from_file(string input_file, string output_file){
    ifstream file_object(input_file);
    if ( not file_object ) {
        cout << "Error! The file "<< input_file <<" cannot be opened." << endl;
        return false;
    } else {
        ofstream myfile;
        myfile.open (output_file);
        int i = 1;
        string line;
        while ( getline(file_object, line) ) {
            myfile << i << " " << line << endl;
            i += 1;
        }
        file_object.close();
        return true;
    }
}

int main()
{
    string input_file = get_file_name("Input file: ");  // get input file name
    string output_file = get_file_name("Output file: ");  // get output file name

    if(read_from_file(input_file, output_file)){
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
