#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>


int main()
{
    std::map<std::string, int > pistetaulukko = {};

    std::string nimi = "";
    int pisteet = 0;
    std::string apu_muuttuja;
    std::string input_file_name;
    std::cout << "Input file: ";
    getline(std::cin, input_file_name);
    std::ifstream tiedosto_olio(input_file_name);

    std::string line;
    if (not tiedosto_olio)
    {
        std::cout <<"Error! The file "<<input_file_name<<" cannot be opened."<<std::endl;
        return EXIT_FAILURE;
    }

    while (getline(tiedosto_olio, line))
    {
        size_t position;

        position = line.find(":");
        nimi = line.substr(0, position);
        pisteet = std::stoi(line.substr(position+1, line.length()));
        if(pistetaulukko.find(nimi) != pistetaulukko.end())
        {
            pistetaulukko[nimi] += pisteet;
        }
        pistetaulukko.insert({nimi, pisteet});

    }
    std::cout<<"Final scores:"<<std::endl;
    for (auto const& pair : pistetaulukko)
    {
        std::cout<<"" <<pair.first << ": " << pair.second<<"\n";
    }







    return 0;
}
