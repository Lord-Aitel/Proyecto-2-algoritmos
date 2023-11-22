#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

    string Arch1;
    string Arch2;

    ifstream archivo1("Cities.txt");
    ifstream archivo2("Guardians.txt");

    while(getline(archivo1,Arch1)){
    cout <<Arch1<<endl;
    }
    
    cout<<"\n"<<endl;

    while(getline(archivo2,Arch2)){
    cout <<Arch2<<endl;
    }
    return 0;
}