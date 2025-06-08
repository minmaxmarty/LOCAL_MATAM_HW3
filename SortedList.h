#pragma once

#include <iostream>
#include <random>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
    private:
        class m_node;
        m_node* m_head;
        m_node* m_tail;
        int m_size;

    public:

        // constructors

        SortedList();

        SortedList(const SortedList& other);

        ~SortedList();

        SortedList& operator=(const SortedList& other);

        // iterator

        class ConstIterator;

        ConstIterator begin() const;

        ConstIterator end() const;

        // methods

        void insert(T newData);

        void remove(const ConstIterator& It);

        unsigned int length() const;

        SortedList filter(bool (*func)(T)) const;

        SortedList apply(T (*func)(T)) const;


        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template<typename T>
    class SortedList<T>::m_node {
    private:
        friend SortedList<T>;

        T m_data;
        m_node* m_next = nullptr;
        m_node* m_prev = nullptr;
    };

    template <class T>
    class SortedList<T>::ConstIterator {

    private:
        friend SortedList<T>;

        SortedList* m_SortedList;
        const m_node* m_currentNode;

        // private constructors
        ConstIterator(SortedList* sortedList, const m_node* node);
        ConstIterator(const ConstIterator& other);
        ConstIterator& operator=(const ConstIterator& other);
        ~ConstIterator();

    public:

        const T& operator*() const; // unary operator
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& other) const;

    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };





    // ---------------- Iterator ---------------- //

    // constructors

    template <typename T>
    SortedList<T>::ConstIterator::ConstIterator(SortedList *sortedList, const m_node *node) : m_SortedList(sortedList),
        m_currentNode(node) {}

    template <typename T>
    SortedList<T>::ConstIterator::ConstIterator(const ConstIterator& other) = default;

    template<typename T>
    typename SortedList<T>::ConstIterator & SortedList<T>::ConstIterator::operator=(const ConstIterator &other) = default;

    template <typename T>
    SortedList<T>::ConstIterator::~ConstIterator() = default;

    // operators

    template <typename T>
    const T& SortedList<T>::ConstIterator::operator*() const {
        if (m_currentNode == nullptr) {
            throw std::out_of_range("out of range"); // incase we are out of range
        }
        return m_currentNode->m_data; // return the data inside the node that the iterator is pointing to
    }

    template <typename T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++() {
        if (m_currentNode == nullptr) {
            return std::out_of_range("out of range");
        }
        m_currentNode = m_currentNode->m_next;
        return *this;
    }

    template <typename T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
        return m_currentNode != other.m_currentNode;
    }




}

