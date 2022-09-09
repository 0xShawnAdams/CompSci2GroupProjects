#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// really? global vars? and terrible names...
string normal = "abcdefghijklmnopqrstuvwxyz";
string alphabet = "zyxwvutsrqponmlkjihgfedcba";
string key;
string encryption;


void process_key(){
    string tmp = alphabet; // why the fuck are you not using the actual string..???? -0xintel
    string keytmp = key; // you anger me. use the actual string theres no need AAAAAAAAAH

    // delete duplicate letters from the key
    for (string::size_type i = 0; i < keytmp.size(); i++) {
        string::size_type j = i+1;
        while (j < keytmp.size()) {
            if (keytmp[i] == keytmp[j]) {
                keytmp.erase(j, 1);
            }
            else {
                j++;
            }
        }
    }

    //delete duplicate letters in the alphabet from the key for the cypher.
    //cat is actually retarded, s is somehow not being deleted from the tmp string and I cannot fathom as to why. -0xkitkoi
    // why couldn't the assignment use aes256 instead :(
    for (string::size_type i = 0; i < tmp.size(); i++) {
        string::size_type j = 0;
        while (j < keytmp.size()) {
            if (tmp[i] == keytmp[j]) {
                tmp.erase(i, 1);
            }
            else {
                j++;
            }
        }
    }

    // your logic is very sad to watch. -0xintel
    alphabet = tmp;
    keytmp += tmp;
    encryption = keytmp;
}

void encrypt_file(ifstream& in, ofstream& out) {
    // use the encryption string to iterate over a line
    char ch;
    while (in.get(ch)) {
        for (int i = 0; i < normal.length(); i++) {
            if (tolower(ch) == normal[i]) {
                out.put(encryption[i]);
            }
            else if (ch == ' ') {
                out.put(' ');
                break;
            }
        }
    }
}

void decrypt_file(ifstream& in, ofstream& out) {
    char ch;
    while (in.get(ch)) {
        for (int i = 0; i < encryption.length(); i++){
            if (ch == encryption[i]) {
                out.put(normal[i]);
            }
            else if (ch == ' ') {
                out.put(' ');
                break;
            }
        }
    }
}

int main (int argc, char* argv[]) {
    bool Dflag = false;
    int file_count = 0;
    ifstream in_file;
    ofstream out_file;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-d") {
            // Decryption flag.
            Dflag = true;
        }
        else if (arg == "-k") {
            i++;
            key = argv[i];
        }
        else {
            file_count++;
            if (file_count == 1) {
                in_file.open(arg);
                if (in_file.fail()) {
                    cout << "Error opening input file " << arg << endl;
                    return -1;
                }
            }
            else if (file_count == 2) {
                out_file.open(arg);
                if (out_file.fail()) {
                    cout << "Error opening output file " << arg << endl;
                    return -1;
                }
            }
        }
    }
    if (file_count != 2) {
        cout << "Usage: " << argv[0] << " [-d] (optional, for decryption.) [-k] key input_file output_file" << endl;
        return 1;
    }

    
    process_key();
    // I have to do this twice because it's not sanitizing the string correctly and I have spent a total of 4 hours trying to figure out why, to no avail.
    // running it twice seems to work though. Maybe dynamic index is the problem. -Cat.
    process_key();
    
    if (Dflag) {
        decrypt_file(in_file, out_file);
    }
    else {
        encrypt_file(in_file, out_file);
    }

    return 0;
}
