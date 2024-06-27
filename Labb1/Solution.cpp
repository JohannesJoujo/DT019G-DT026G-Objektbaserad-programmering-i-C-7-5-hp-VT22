#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
struct Address
{
    std::string street;
    int zip;
    std::string city;
};
struct Person
{
    std::string name;
    std::string id;
    Address location;
};

std::string toUpper(std::string str);
std::istream &operator>>(std::istream &in, Person &p);
std::vector<Person> read_file(std::string filename);
size_t find_in_names(const std::vector<Person> &haystack, std::string skriv);
std::vector<Person> find_person_from_city(const std::vector<Person> &haystack, std::string city);

int main()
{
    std::vector<Person> list = read_file("names.txt");
    std::string skriv, input;
    int option = 0;
    while (option != 3)
    {

        std::cout << "1 - Sök del av personnam!" << std::endl;
        std::cout << "2 - Sök efter personer i stad!" << std::endl;
        std::cout << "3 - Avsluta Programmet" << std::endl;
        do
        {
            std::cout << "Skriv här: ";
            getline(std::cin, input);
        } while (input.empty() || !isdigit(input.front()));
        option = input.front() - '0';
        if (option == 1)
        {
            std::cout << "Skriv ett namn att söka efter: ";
            getline(std::cin, skriv);
            size_t count = find_in_names(list, skriv);
            std::cout << "Hittade " << count << " personer med liknande namn." << std::endl;
        }
        else if (option == 2)
        {
            std::cout << "Skriv en stad att söka efter: ";
            getline(std::cin, skriv);
            std::vector<Person> sublist = find_person_from_city(list, skriv);
            for (const struct Person &per : sublist)
            {
                std::cout << '\n'
                          << "---------------------------------" << '\n'
                          << per.name << " bor i " << per.location.city << '\n'
                          << "---------------------------------"
                          << std::endl;
            };
        }
    }
    return 0;
}
/*
 * Overloads the operator >> to read from an istream, e.g. a * file, to a person. Sets all the attributes of a person.
 * @param in The istream data is read from. * @param p The person to store data in.
 * @returns a reference to the stream (for operator chaining). */
std::istream &operator>>(std::istream &in, Person &p)
{
    std::string name, id, address, street, city, zipcode;
    int zip;

    getline(in, p.name);
    getline(in, p.id);
    getline(in, address);

    p.location.street = address.substr(0, address.find(','));
    address.erase(0, address.find(',') + 2);

    zipcode = address.substr(0, address.find(' ') + 3);
    zipcode.erase(std::remove_if(zipcode.begin(), zipcode.end(), ::isspace), zipcode.end());
    address.erase(0, address.find(' ') + 5);

    std::stringstream input_string(zipcode);
    input_string >> zip;
    p.location.zip = zip;

    p.location.city = address.substr(0, address.find_last_not_of(' ') + 1);

    return in;
}

/*
 * Reads from file <filename> and returns the results in * a vector. Uses overloaded operator >>.
 * @param filename The path to the file to be read.
 * @returns vector <Person > containing all the people listed
 * in the file. An empty vector is returned if no people * are found.
 */
std::vector<Person> read_file(std::string filename)
{
    std::ifstream file(filename.c_str());
    std::vector<Person> haystack;

    if (!file.is_open())
    {
        return haystack;
    }
    struct Person p;
    while (file >> p)
    {
        haystack.push_back(p);
    }
    return haystack;
}

/*
 * Searches in vector <haystack> for names containing the * substring <name_part >. Note that <name_part > is a
 * a substring meaning exact matches are not necessary. * The search is case insensitive.
 * @param haystack The vector containing the people to * search through.
 * @param name_part The name to look for.
 * @returns the number of people where name_part is found and
 * occurs at least once. */
size_t find_in_names(const std::vector<Person> &haystack, std::string skriv)
{
    size_t i = 0;
    struct Person p;
    std::string temp_name;

    transform(skriv.begin(), skriv.end(), skriv.begin(), ::toupper);

    for (Person p : haystack)
    {
        temp_name = p.name;
        transform(temp_name.begin(), temp_name.end(), temp_name.begin(), ::toupper);

        if (temp_name.find(skriv) != std::string::npos) // npos= no position no matches found, type size_t
        {
            i++; // namn counter +1
        }
    }

    return i;
}
std::string toUpper(std::string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    while (str.find("å") != std::string::npos)
    {
        str.replace(str.find("å"), 2, "Å");
    }
    while (str.find("ä") != std::string::npos)
    {
        str.replace(str.find("ä"), 2, "Ä");
    }
    while (str.find("ö") != std::string::npos)
    {
        str.replace(str.find("ö"), 2, "Ö");
    }
    return str;
}

/*
 * Searches in vector <haystack> for people living in a * particular <city >.
 * The search is case insensitive.
 * Exact matches only (except case).
 * @param haystack The vector containing the people to * search through.
 * @param city The city to look for.
 * @returns a vector containing all persons with exactly
 * matching cities. */
std::vector<Person> find_person_from_city(const std::vector<Person> &haystack, std::string city)
{
    std::vector<Person> city_found;
    city = toUpper(city);

    for (const struct Person &p : haystack)
    {
        std::string tmp = p.location.city;
        tmp = toUpper(tmp);

        if (tmp == city)
        {
            city_found.push_back(p);
        }
    }
    return city_found;
}
