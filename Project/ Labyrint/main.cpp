// Johannes joujo
//E-nivå

#include "maze.hpp"

int main()
{

    bool programmet = true;
    do
    {
        char in;
        std::cout << "\nVälkommen" << std::endl;
        std::cout << "=============================\n";
        std::cout << "1: Generera en labyrint " << std::endl;
        std::cout << "2: Avsluta Programmet" << std::endl;
        std::cout << "=============================\n";
        std::cout << "\nVälj ett tal mellan 1 och 2: ";
        std::cin >> in;
        switch (in)
        {
        case 49:
            Visa();
            break;
        case 50:
            programmet = false;
            break;
        default:
            std::cout << "Välj ett tal mellan 1 och 2: " << std::endl;
            break;
        }

    } while (programmet);
    std::cout << "\nProgrammet Stoppades\n"
              << std::endl;
    return 0;
}
