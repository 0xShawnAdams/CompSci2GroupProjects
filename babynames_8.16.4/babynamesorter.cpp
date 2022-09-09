#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


void process_name(ifstream& in_file, double& total, ofstream& out_file) {
    int rank;
    string name;
    int frequency;
    double percent;

    string tmp;
    getline(in_file, tmp);
    istringstream line(tmp);
    line >> rank >> name >> frequency >> percent;
    
    cout << rank << " " << name << " " << frequency << " " << percent << endl;
    out_file << rank << " " << name << " " << frequency << " " << percent << endl;
    total--;
}



int main(int argc, char* argv[]) {
    int file_count = 0;
    ifstream in_file;
    ofstream boi_file;
    ofstream girl_file;
    in_file.open(argv[1]);
    if (in_file.fail()) {
        cout << "Please pass babynames.txt as an argument to this program.\n";
        return -1;
    }
    boi_file.open("boynames.txt");
    girl_file.open("girlnames.txt");
    if (!boi_file) {
        boi_file.open("boynames.txt", fstream::in | fstream::out | fstream::trunc);
    }
    if (!girl_file) {
        girl_file.open("girlnames.txt", fstream::in | fstream::out | fstream::trunc);
    }
    double boy_total = 500;
    double girl_total = 500;

    while (boy_total > 0 || girl_total > 0) {
        int rank;
        string name;
        int frequency;
        double percent;

        string tmp;
        getline(in_file, tmp);
        istringstream line(tmp);
        line >> rank >> name >> frequency >> percent;
        boi_file << rank << " " << name << " " << frequency << " " << percent << endl;
        line >> name >> frequency >> percent;
        girl_file << rank << " " << name << " " << frequency << " " << percent << endl;
        boy_total--;
        girl_total--;
        //process_name(in_file, boy_total, boi_file);
        //process_name(in_file, girl_total, girl_file);
    }
}
