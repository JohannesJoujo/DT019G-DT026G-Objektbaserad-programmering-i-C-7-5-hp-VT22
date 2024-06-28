#include "linked_list.h"
// Constructor
linked_list::linked_list()
{
    head = nullptr;
    tail = nullptr;
}

linked_list::node::node(double value)
{
    this->value = value;
    prev = nullptr;
    next = nullptr;
}

// kopieringskonstrurerare

linked_list::linked_list(const linked_list &src)
{
    node *flytt;
    flytt = src.head;
    if (head) // om den inte är tom
    {
        head = nullptr;
        tail = nullptr;
        while (flytt)
        {
            this->push_back(flytt->value);
            flytt = flytt->next;
        }
    }
    else
    { // Om src är tom.
        head = nullptr;
        tail = nullptr;
    }
}

// Destructor förstör en lista för att hindra minnesläckage
linked_list::~linked_list()
{
    node *flytt;
    flytt = this->head;
    node *next;
    next = nullptr;
    while (flytt != nullptr)
    {
        next = flytt->next;
        delete flytt;
        flytt = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

// operator ger möjligthet att kopiera en lista till en ny lista.
// Assignment operator
linked_list &linked_list::operator=(const linked_list &rhs)
{
    if (this != &rhs) // Om lhs och rhs är olika
    {
        node *flytt;
        flytt = rhs.head;
        while (!is_empty())
        {
            pop_front(); // poppar lhs, så att listan är tom
        }
        while (flytt != nullptr) // efter det lägg in värdena från rhs.
        {
            push_back(flytt->value);
            flytt = flytt->next;
        }
    }
    return *this;
}

// + operator lägger till värden i slutet av en ny lista
linked_list &linked_list::operator+=(const linked_list &rhs)
{
    node *flytt;
    flytt = rhs.head; // så länge som flytt inte är null, för in det kopierade värdet i slutet på nya listan och flytta noden ett steg fram
    while (flytt != nullptr)
    {
        push_back(flytt->value);
        flytt = flytt->next;
    }
    return *this;
}

// lägg till en node i lista.
void linked_list::insert(double value, size_t pos)
{
    node *temp = new node(value); // gör en ny node.
    node *flytt;
    flytt = head;
    for (size_t i = 0; i < pos; i++) // hittar positionen
    {
        if (flytt->next)
        {
            flytt = flytt->next;
        }
        else
        {
            break;
        }
    }
    temp->value = value;
    temp->next = flytt->next;
    flytt->next->prev = temp;
    flytt->next = temp;
    temp->prev = flytt;
}
// för in ett värde i listans bakre del
void linked_list::push_back(double value)
{
    node *flytt = new node(value);
    flytt->value = value;
    node *flyttare;
    if (head)
    {
        flyttare = tail;
        flyttare->next = flytt;
        tail = flytt;
        tail->prev = flyttare;
        tail->next = nullptr;
    }
    else
    {
        head = flytt;
        tail = flytt;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
}

// ligger in ett värde i listan frame del
void linked_list::push_front(double value)
{
    node *flytt = new node(value);
    flytt->value = value;
    node *flyttare;
    if (head)
    {
        flyttare = head;
        flyttare->prev = flytt;
        head = flytt;
        head->prev = nullptr;
        head->next = flyttare;
    }
    else
    {
        head = flytt;
        tail = flytt;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
}

// returnera första element i lista
double linked_list::front() const
{
    return head->value;
}
// returnar sista elemnt i listan
double linked_list::back() const
{
    return tail->value;
}

// returnera element på en specifik position genom att stega sig from till pos med en for loop
double linked_list::at(size_t pos) const
{
    node *flytt;
    flytt = head;

    if (flytt)
    {
        for (size_t i = 1; i < pos; i++)
        {
            if (flytt->next != nullptr)
            {
                flytt = flytt->next;
            }
            else
            {
                return flytt->value;
            }
        }
        return flytt->value;
    }
    else
    {
        return 0;
    }
}

// ta bort en node från en specifik plats genom att stega sig fram med en loop.
void linked_list::remove(size_t pos)
{

    node *flytt;
    flytt = head;
    node *flyttare;
    if (flytt)
    {
        for (size_t i = 0; i < pos; i++) // hittar rätt position med for loopen.
        {
            flytt = flytt->next;
        }
        if (flytt->prev) // byter ut flytt med flyttare.
        {
            flyttare = flytt->prev;
            flyttare->next = flytt->next;
        }
        if (flytt->next)
        {
            flyttare = flytt->next;
            flyttare->prev = flytt->prev;
        }
        delete flytt;
    }
}

// tar bort första noden i listan
double linked_list::pop_front()
{
    node *flytt;
    flytt = head;
    double temp = 0;
    if (is_empty())
    {
        std::cout << "Listan är tom" << std::endl;
    }
    if (head)
    {
        temp = head->value;
        flytt = head;
        head = flytt->next;
        delete flytt;
        if (head)
        {
            head->prev = nullptr;
        }
    }
    return temp;
}

// tar bort den sista noden i listan
double linked_list::pop_back()
{
    double temp = 0;
    node *flytt;
    if (is_empty()) // om listan är tom.
    {
        std::cout << "Listan är tom" << std::endl;
    }
    else
    {
        temp = tail->value;
        flytt = tail;
        tail = flytt->prev;
        delete flytt;
        if (tail)
        {
            tail->next = nullptr; // sista nodenn pekar till nullptr
        }
    }
    return temp;
}

// räkna ut size genom att stega sig fram i hela listan i while loop. räknaren returnerar ett värde med listans längd.
size_t linked_list::size() const
{
    node *flytt;
    size_t counter = 0;
    flytt = head;
    if (flytt) // om head finns counter++
    {
        counter++;
        while (flytt->next) // loopar igenom listan så att counter++ räknar noder.
        {
            counter++;
            flytt = flytt->next; // flyttar flytt till nästa nod.
        }
        return counter;
    }
    else
    {
        return counter;
    }
}
// kollar om listan har noder.
bool linked_list::is_empty() const
{
    return head == nullptr; // tom om head==nullptr (sant).
}

void linked_list::print() const
{
    node *flytt;
    flytt = head;
    if (flytt)
    {
        while (flytt) // från head fram till sista noden
        {
            std::cout << flytt->value << " "; // skriver den ut värdet och en mellanrum.
            flytt = flytt->next;              // flyttar flytt till nästa nod.
        }
    }
    else
    {
        std::cout << "Listan är tom! ";
    }
}

// skriva ut list 2. print fast baklänges
void linked_list::print_reverse() const
{
    node *flytt;
    flytt = tail;
    if (flytt) // från tail fram till första noden.
    {
        while (flytt->prev)
        {
            std::cout << flytt->value << " ";
            flytt = flytt->prev; //ändra på flytt så att den kan loopa igenom och skriva ut alla värden.
        }
    }
    else
    {
        std::cout << "Listan är tom! ";
    }
}