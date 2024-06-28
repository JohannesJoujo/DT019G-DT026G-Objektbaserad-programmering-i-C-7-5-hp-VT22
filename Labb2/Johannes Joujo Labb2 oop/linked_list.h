#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include <iostream>
#include <iostream>
#include <string>

class linked_list
{
public:
    linked_list();
    linked_list(const linked_list &src);

    ~linked_list();

    linked_list &operator=(const linked_list &rhs); 

    // appends elements from rhs
    linked_list &operator+=(const linked_list &rhs); 

    // inserting elements
    void insert(double value, size_t pos);
    void push_front(double value);
    void push_back(double value);

    // accessing elements
    double front() const;
    double back() const;
    double at(size_t pos) const;

    // removing elements
    void remove(size_t pos);
    double pop_front();
    double pop_back();
    // status
    size_t size() const;
    bool is_empty() const;

    // output
    void print() const;
    void print_reverse() const;

private:
    struct node
    {
        node(double value);
        double value;
        node *prev;
        node *next;
    };
    node *head;
    node *tail;

    node *find(size_t pos) const;
};
#endif // LLIST_H_INCLUDED Z