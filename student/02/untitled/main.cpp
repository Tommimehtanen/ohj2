#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int check_lenght(string encryption_key)
{
    string::size_type pituus = 0;
    pituus = encryption_key.length();
    if (pituus != 26)
    {
        cout << "Error! The encryption key must contain 26 characters.";
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }

}

int check_for_uppers(string encryption_key)
{
    for (const char& c : encryption_key)
    {
        if (isupper(c))
        {
            cout << "Error! The encryption key must contain only lower case characters.";
            return 0;
        }
    }
    return 1;
}
int check_alphabets(string encryption_key)
{
    for (int i = 0; i < 26; ++i)
    {
        char k = encryption_key.at(i);


        int ascii_value = static_cast< int > (k);
        if (ascii_value < 97 || ascii_value > 122)
        {
            cout << "Error! The encryption key must contain all alphabets a-z.";
            return 0;
        }
        for (char kirjain = 'a'; kirjain < 'z'; ++kirjain)
        {
            string::size_type apu = 0;
            apu = encryption_key.find(kirjain);
            if (apu == string::npos)
            {
                cout << "Error! The encryption key must contain all alphabets a-z.";
                return 0;
            }
        }
    }
    return 1;

}

void encrypt_text(string text, string encrypt_key)
{


    string uusi;
    string :: size_type pituus = 0;
    pituus = text.length();
    for (long unsigned int i = 0; i < pituus; ++i)
    {
        char string_to_crypt = text.at(i);
        int ascii = static_cast <int > (string_to_crypt);
        int place = ascii - 97;
        char key = encrypt_key.at(place);
        uusi += key;
    }
    cout <<"Encrypted text: "<< uusi;



}

int main()
{
    string encryption_key = "";
    string text = "";
    cout <<"Enter the encryption key: ";
    getline(cin, encryption_key);
    if (check_lenght(encryption_key) == 0)
    {
        return EXIT_FAILURE;
    }
    if (check_for_uppers(encryption_key) == 0)
    {
        return EXIT_FAILURE;
    }
    if (check_alphabets(encryption_key) == 0)
    {
        return EXIT_FAILURE;
    }
    cout << "Enter the text to be encrypted: ";
    getline(cin, text);
    for (int i = 0; i < 26; ++i)
    {
        char k = text.at(i);


        int ascii_value = static_cast< int > (k);
        if (ascii_value < 97 || ascii_value > 122)
        {
            cout << "Error! The encryption key must contain only lower case characters.";
    {
        return EXIT_FAILURE;
    }
        }
    }
    encrypt_text(text, encryption_key);
    return EXIT_SUCCESS;





}
