#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string tiedoston_nimi = "";
    string output_tiedosto = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    cout << "Output file: ";
    getline(cin, output_tiedosto);

    vector<string> output = {};
    int rivinumero = 1;
    string line;
    ifstream tiedosto_olio(tiedoston_nimi);
    if (not tiedosto_olio)
    {
        cout <<"Error! The file "<<tiedoston_nimi<< " cannot be opened."<<endl;
        return EXIT_FAILURE;
    }

    while(getline(tiedosto_olio, line))
    {
        output.push_back(to_string(rivinumero) +" " + line);
        rivinumero++;
    }
    tiedosto_olio.close();
    ofstream outputFile(output_tiedosto);

    for (auto l : output) {
        outputFile << l << endl;
    }


    outputFile.close();

    return 0;
}
