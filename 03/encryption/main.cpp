#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

bool check_encryption_key_length(string & encryption_key);
bool check_uppercase(string & encryption_key);
bool check_encryption_key_unique(string & encryption_key);
void encrypt_text(string & text, string & encryption_key);

int main()
{
    cout << "Enter the encryption key: ";
    string encryption_key;
    cin >> encryption_key;

    bool valid_length, check_uppercase_key, check_unique, check_uppercase_text;

    // check the length of encryptin key
    valid_length = check_encryption_key_length(encryption_key);

    if(valid_length){

    } else {
        return EXIT_FAILURE;
    }

    //check if the encryption key contain any uppercase character
    check_uppercase_key = check_uppercase(encryption_key);

    if(check_uppercase_key){

    } else {
        return EXIT_FAILURE;
    }

    //check if the encryption key characters are all unique
    check_unique = check_encryption_key_unique(encryption_key);

    if(check_unique){

    } else {
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    string text;
    cin >> text;

    //check if the text contain any uppercase character
    check_uppercase_text = check_uppercase(text);

    if(check_uppercase_text){
        // encrypt the text
        encrypt_text(text, encryption_key);
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool check_encryption_key_length(string & encryption_key){
    // check the length of encryptin key

    string::size_type len = 0;
    len = encryption_key.length();
    if(len < 26){
        cout << "Error! The encryption key must contain 26 characters.";
        return false;
    }
    return true;
}

bool check_uppercase(string & encryption_key){
    //check if the encryption key contain any uppercase character
    string::size_type len = 0;
    len = encryption_key.length();

    for(int j = 0; j < int(len); j++){
        if(isupper(encryption_key[j])){
            cout << "Error! The encryption key must contain only lower case characters.";
            return false;
        }
    }
    return true;
}

bool check_encryption_key_unique(string & encryption_key){
    string::size_type len = 0;
    len = encryption_key.length();

    for(int i = 0; i < int(len); i++){
        for(int j = i + 1; j < int(len); j++){
            if( encryption_key[i] == encryption_key[j]){
                cout << "Error! The encryption key must contain all alphabets a-z.";
                return false;
            }
        }
    }
    return true;
}

void encrypt_text(string & text, string & encryption_key){
    // encrypt the text
    string::size_type text_len = 0;
    text_len = text.length();

    string::size_type location = 0;
    location = text.find('a', 0);

    int counter = 0;
    string replace_with;
    string copy_text;
    copy_text = text;

    for( char letter = 'a'; letter <= 'z'; ++letter ){
        for(int i = 0; i < int(text_len); i++){
            if(text[i] == letter){
                location = text.find(letter, 0);
                replace_with = encryption_key[counter];
                text.replace(location, 1, "_");
                copy_text.replace(location, 1, replace_with);
            }
        }
        counter++;
    }
    cout << "Encrypted text: " <<copy_text << endl;
}
