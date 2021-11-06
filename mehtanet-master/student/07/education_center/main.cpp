/* Education_center
 *
 * Desc:
 *  Program reads a text file and and stores it's location, themes and course information to a data structure.
 * User can search the data structure for courses by theme or location and see the enrollments of courses.
 *
 * Program author
 * Name: Roope Rothovius, Tommi Meht�nen
 * Student number: 274562, 279330
 * UserID: rothoviu, mehtanet
 * E-Mail: roope.rothovius@tuni.fi, tommi.mehtanen@tuni.fi
 * Feedback language (fi/en): fi
 *
 * */



#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <bits/stdc++.h>

struct Course {
    std::string name;
    std::string theme;
    int enrollments;
};

using Location= std::string;
using Locations = std::map<Location, std::vector<Course>>;


//compares courses names
bool compareCourse(Course i1, Course i2)
{
    return(i1.name < i2.name);
}
//compares amounts of enrollments
bool compareinrollments(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
{
    return (a.second >b.second);
}
bool comparethemes(Course c1, Course c2)
{
    return(c1.theme < c2.theme);
}

//turns the user input to a vector of strings
std::vector<std::string> split(std::string list, char delim)
{
    std::vector<std::string> parts = {};
    std::string part = "";

    bool cont = false;

    for(char c : list){

        if (c =='"'){
            cont = !cont;
        }

        else if(c != delim || cont){
            part += c;
        }

        else{
            parts.push_back(part);
            part = "";
        }
    }
    parts.push_back(part);

    return parts;
}

//cheks if inputfile has errors
int check_input_file(std::vector<std::string> strings)
{

    if (strings.size()!= 4)
    {
        std::cout<<"Error: empty field";
        return EXIT_FAILURE;
    }
    for(unsigned int i = 0; i < 4; ++i)
    {
        if (strings.at(i) == "Error: empty field")
        {
            std::cout<<"";
            return EXIT_FAILURE;
        }
    }
    return true;
}


//stores data from a row of given file to the data structure
void store_data(std::string line, std::map<std::string,std::vector<Course>>& data)
{

    std::string location;
     std::vector<std::string> strings = split(line, ';');
     location = strings.at(0);


     check_input_file(strings);

     Course item;
     if(strings.at(3) == "full")
     {
         item.enrollments = 50;
     }
     else
     {
         item.enrollments = stoi(strings.at(3));
     }
     item.name = strings.at(1);
     item.theme = strings.at(2);


     for(auto it = data.begin(); it != data.cend(); ++it)
     {
         if(it->first == location)
         {
             for(unsigned int i = 0; i < data[location].size(); ++i)
             {
                 if(data[location][i].name == item.name)
                 {
                     if(data[location][i].theme == item.theme)
                     {
                         data[location][i].enrollments = item.enrollments;
                         return;

                     }

                 }
             }
         }
     }
     data[location].push_back(item);
     std::sort(data[location].begin(), data[location].end(), comparethemes);
     std::sort(data[location].begin(), data[location].end(), compareCourse);

}

//goes through locations in data structure
void print_locations(Locations& data)
{
    for(auto it = data.begin(); it != data.cend(); ++it)
    {
        std::cout<< it->first<<std::endl;
    }
}

//goes through all courses in given location and prints them with enrollments
void print_courses(Locations& data, std::string location, std::string course)
{
    std::set<std::string> CoursesByLocation;

    for (unsigned int i = 0 ; i < data[location].size(); i++) {
        if (data[location][i].name == course){
            std::string enrolls = std::to_string(data[location][i].enrollments);
            if (enrolls == "50"){
                enrolls = "full";
                auto text = data[location][i].theme + " --- " + enrolls;
                CoursesByLocation.insert(text);
            }
            else{
                auto text = data[location][i].theme + " --- " + enrolls + " " + "enrollments";
                CoursesByLocation.insert(text);
            }
        }
    }
    for (const auto course : CoursesByLocation){
        std::cout << course << std::endl;;
    }
}

//checks the users input for mistakes in command, location or theme
bool check_command(std::vector<std::string> parts, Locations &data, std::string order)
{
    int truth = 0;
    if(parts.size() < 3){
        std::cout << "Error: error in command " << order << std::endl;
        return false;
    }
    else{
        for(auto &loc : data){
            if(loc.first == parts[1]){
                truth = 1;
            }
        }
        if(truth == 0){
            std::cout << "Error: unknown location name" << std::endl;
            return false;
        }

        else{
            int truth2 = 0;
            for ( auto &loc : data ) {
                for (unsigned int i = 0 ; i < data[loc.first].size(); i++) {
                    if (data[loc.first][i].name == parts[2]){
                        truth2 = 1;
                    }
                }
            }
            if(truth2 == 0){
                std::cout << "Error: unknown theme" << std::endl;
                return false;
            }
        }

    return true;
    }
}

//prints all the courses that are not yet full
void print_availables(Locations &data)
{
    std::set<Course> course_details;
    for(auto it = data.begin(); it != data.cend(); ++it)
    {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if(it2->enrollments < 50)
            {

            std::cout<<it->first<<" : "<<it2->name<<" : "<< it2->theme<<std::endl;
            }
        }
    }
}

//checks the theme and prints all courses in that theme
void print_courses_in_theme(Locations &data, std::string theme)
{
    std::set<std::string> courses_in_theme;

    for(auto it = data.begin(); it != data.cend(); ++it)
    {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if(it2->name == theme)
            {
                courses_in_theme.insert(it2->theme);
            }
        }
    }

    for (auto const& item : courses_in_theme)
    {
        std::cout << item << std::endl;
    }
}

//prints the themes with most enrollments
void print_favourite_themes(Locations& data)
{
    std::map<std::string, int> themes_data;
    int enrollments_sum = 0;
    std::string theme;
    for(auto it = data.begin(); it != data.cend(); ++it)
    {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            theme = it2->name;
            enrollments_sum = it2->enrollments;


            if(themes_data.count(theme))
            {
                themes_data[theme] += it2->enrollments;

            }
            else
            {
            themes_data[theme] = enrollments_sum;

            }
            enrollments_sum = 0;
        }
    }
    //saves data in to a vector for printing
    std::vector<std::pair<std::string,unsigned int>> vec;
    std::map<std::string, int> ::iterator it4;
    for(it4 =themes_data.begin(); it4 != themes_data.end(); ++it4)
    {
        vec.push_back(std::make_pair(it4->first, it4->second));
    }
    if(vec.size() < 1)
    {
        std::cout<<"No enrollments"<<std::endl;
    }
    else
    {
        //prints favorite themes
        std::sort(vec.begin(), vec.end(), compareinrollments);
        unsigned int j = vec.begin()->second;
        std::cout<<vec.begin()->second<<" enrollments in themes"<<std::endl;
        std::cout<<"--- "<<vec.begin()->first<<std::endl;

        for(unsigned int i = 1; i < vec.size(); ++i)
        {
            if(vec.at(i).second == j)
            {
                std::cout<<"--- "<<vec.at(i).first<<std::endl;

            }
        }
    }
}

//checks that given theme is in data structure
bool check_theme(std::string theme, Locations &data)
{
    for ( auto &loc : data ){
        for (unsigned int i = 0 ; i < data[loc.first].size(); i++) {
            if (data[loc.first][i].name == theme){
                return true;
            }
        }
    }
    std::cout << "Error: unknown theme" << std::endl;
    return false;
}


//reads the input file and runs the user interface
int main()
{
    std::string line;
    Locations data;
    std::string file_name;
    std::cout<<"Input file: ";
    getline(std::cin, file_name);
    std::ifstream file_object(file_name);

    if (not file_object)
    {
        std::cout<<"Error: the input file cannot be opened";
        return EXIT_FAILURE;
    }
    while (std::getline(file_object, line))
    {
        store_data(line, data);
    }
    file_object.close();
    std::string command;

    //loops the user interface
    while (command != "quit")
    {
        std::cout<<"> ";
        getline(std::cin, command);
        char denim = ' ';
        std::vector<std::string> parts = split(command,denim);

        std::string order;
        order = parts[0];
        if(order == "quit")
            return EXIT_SUCCESS;
        if(order == "locations")
        {
            print_locations(data);
        }

        else if(order == "courses")
        {
            if (check_command(parts, data, order))
            {
                std::string location = parts[1];
                std::string theme = parts[2];



                for(unsigned int i = 3; i < parts.size(); i++){
                        theme = theme + " " + parts[i];
                }
                print_courses(data, location, theme);
            }
        }

        else if(order == "available")
        {
            print_availables(data);
        }

        else if( order == "courses_in_theme")
        {
            std::string theme = parts[1];

            if (check_theme(theme, data)){
                print_courses_in_theme(data, theme);
            }
        }

        else if(order == "favorite_theme")
        {
            print_favourite_themes(data);
        }

        else{
            std::cout << "Error: Unknown command: " << order << std::endl;
        }
    }
}
