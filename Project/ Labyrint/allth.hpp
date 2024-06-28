//Johannes Joujo
//E-nivå
#include "maze.hpp"

// Här bestäms värdet på nodens medlemmar
maze::node::node()
{
    space = ' ';
    start = 'S';
    end = 'E';
    wall = '#';
    visited = false;
    x = 0;
    y = 0;
}

// Fyller alla positioner med '#' i en nod som sedan läggs in i en vector som inehåller noderna
maze::maze()
{
    std::vector<node> n;
    node v;
    for (int i = 0; i < 11; i++)
    {

        for (int j = 0; j < 11; j++)
        {

            n.push_back(v);
        }
        XYVec.push_back(n);
    }
}

// överlagrar utströmmen så att det ska gå att skriva ut innehållet i vectorn
std::ostream &operator<<(std::ostream &COUT, const maze::node &pos)
{
    COUT << pos.wall;
    return COUT;
}

// skriver ut labyrinten
void maze::print()
{

    for (int i = 0; i < 11; i++)
    {

        for (int j = 0; j < 11; j++)
        {

            std::cout << XYVec[i][j];
        }
        std::cout << std::endl;
    }
}

// går igenom labyrinten genom att vara på en pos och kolla fram,bak,upp,ner två pos i taget och bestämmer en godkänn random pos att gå till, sen går den tillbaks ett //steg och gör den till ' ' också.
void maze::DFS()
{
    std::stack<node> stack;
    node current;
    node character;
    node start;
    node end;
    
    //bara för att det ska visas på skärmen 'S' och 'E'
    XYVec[1][1].wall = start.start;
    XYVec[10][7].wall = character.end;
    //start får vara([1][1])
    start.x = 1;
    start.y = 1;
    XYVec[1][1].visited = true;

    stack.push(start);
    std::vector<node> dir;

    while (!stack.empty())
    {
        dir = rand_Dir(stack.top());
        current = stack.top();

        if (!dir.empty())
        {
            stack.pop();
            stack.push(current);

            node temp = dir[rand() % dir.size()];
            XYVec[temp.x][temp.y].visited = true;

            Wall_breaker(temp, current);

            stack.push(temp); // vi sen sätter den som vi slumpmässigt valde ut längst upp på stacken för att sen ta bort den
        }
        else
        {
            stack.pop();
        }
    }
}

// Väljer positioner som labyrinten kan ta rendom. Genom att kolla om det går att ta två steg från nuvarande nod till upp, ner, bak,fram.
std::vector<maze::node> maze::rand_Dir(const node pos)
{

    std::vector<node> hold;

    node temp;
    // flyttar sig i x-ledet två steg till höger om noden inte har varit besökt innan
    if (pos.x + 2 < 10 && XYVec[pos.x + 2][pos.y].visited == false)
    {
            temp.x = pos.x + 2;
            temp.y = pos.y;
            hold.push_back(temp);
    }
    if (pos.x - 2 > 0 && XYVec[pos.x - 2][pos.y].visited == false)
    {
            temp.x = pos.x - 2;
            temp.y = pos.y;
            hold.push_back(temp);
    }

    if (pos.y + 2 < 10 && XYVec[pos.x][pos.y + 2].visited == false)
    {
            temp.x = pos.x;
            temp.y = pos.y + 2;
            hold.push_back(temp);
    }

    if (pos.y - 2 > 0 && XYVec[pos.x][pos.y - 2].visited == false)
    {

            temp.x = pos.x;
            temp.y = pos.y - 2;
            hold.push_back(temp);
    }

    return hold;
}
// går mellan nuvarande pos och den förra för att göra den till en väg också.
void maze::Wall_breaker(const maze::node pos, const maze::node pos2)
{
    // går tillbacka ett steg i x-led för att göra den till en väg.
    if (pos.x > pos2.x && pos.y == pos2.y)
    {
        XYVec[pos.x - 1][pos.y].wall = pos.space;
        XYVec[pos.x][pos.y].wall = pos.space;
    }
    else if (pos.x < pos2.x && pos.y == pos2.y)
    {
        XYVec[pos.x + 1][pos.y].wall = pos.space;
        XYVec[pos.x][pos.y].wall = pos.space;
    }
    else if (pos.y > pos2.y && pos.x == pos2.x)
    {
        XYVec[pos.x][pos.y - 1].wall = pos.space;
        XYVec[pos.x][pos.y].wall = pos.space;
    }
    else
    {
        XYVec[pos.x][pos.y + 1].wall = pos.space;
        XYVec[pos.x][pos.y].wall = pos.space;
    }
}
// genegerar olika labyrinter.
void Visa()
{
    srand((unsigned)time(0));
    maze j;
    j.DFS();
    j.print();
}



