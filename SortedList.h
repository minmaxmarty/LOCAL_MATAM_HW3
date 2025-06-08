#pragma once

#include <iostream>
#include <random>
#include <stdexcept>

#include "SortedList.h"

namespace mtm {

    template <typename T>
    class SortedList {
        class Node;

        Node* m_head;
        Node* m_tail;
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

        void insert(const T& newData);

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
    class SortedList<T>::Node {
        friend SortedList;

        T m_data;
        Node* m_next;
        Node* m_prev;

        // constructor
        explicit Node(const T& data, Node* next = nullptr, Node* prev = nullptr);
        Node(const Node& other);
        Node& operator=(const Node& other);
    };

    template <class T>
    class SortedList<T>::ConstIterator {
        friend SortedList;

        SortedList* m_SortedList;
        const Node* m_currentNode;

        // private constructors
        ConstIterator(SortedList* sortedList, const Node* node);
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

    // ------------------------------- SortedList ------------------------------- //

    template <typename T>
    SortedList<T>::SortedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

    template<typename T>
    SortedList<T>::SortedList(const SortedList &other) : m_head(nullptr), m_tail(nullptr), m_size(other.m_size) {
        Node* prev = nullptr;
        for (ConstIterator It = other.begin(); It != other.end(); ++It) {
            Node* newNode = new Node(*It, nullptr, nullptr);
            if (m_head == nullptr) {
                m_head = newNode;
            }
            else {
                prev->m_next = newNode;
                prev->m_next->m_prev = prev;
            }
            prev = newNode;
        }
        m_tail = prev;
    }

    template<typename T>
    SortedList<T>::~SortedList() {
        ConstIterator It = begin();
        while (It != end()) {
            Node* toDelete = It.m_currentNode;
            ++It;
            delete toDelete;
        }
    }

    template <typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList& other) {
        if (this == &other) { // if they are the same
            return *this;
        }

        m_size = other.m_size;

        ConstIterator It = begin();
        while (It != end()) {
            Node* toDelete = It.m_currentNode;
            ++It;
            delete toDelete;
        }

        Node* prev = nullptr;
        for (It = other.begin(); It != other.end(); ++It) {
            Node* newNode = new Node(*It, nullptr, nullptr);
            if (m_head == nullptr) {
                m_head = newNode;
            }
            else {
                prev->m_next = newNode;
                prev->m_next->m_prev = prev;
            }
            prev = newNode;
        }
        m_tail = prev;

        return *this;
    }

    // methods

    template<typename T>
    void SortedList<T>::insert(const T& newData) {
        if (m_head == nullptr) {
            m_head = m_tail = new Node(newData, nullptr, nullptr);
        }
        else if (newData < m_head->m_data) {
            Node* newNode = new Node(newData, m_head, nullptr);
            m_head->m_prev = newNode;
            m_head = newNode;
        }
        else if (newData >= m_tail->m_data) {
            Node* newNode = new Node(newData, nullptr, m_tail);
            m_tail->m_next = newNode;
            m_tail = newNode;
        }
        else {
            for (ConstIterator It = begin(); It != end(); ++It) {
                if (newData >= *It && newData < It.m_currentNode->m_next->m_data) {
                    Node* newNode = new Node(newData, It.m_currentNode->m_next, It.m_currentNode);
                    It.m_currentNode->m_next = newNode;
                    newNode->m_next->m_prev = newNode;
                    break;
                }
            }
        }

        m_size++;
    }


    // methods for ConstIterator inside sortedList

    template <typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const {
        return ConstIterator(this, m_head);
    }

    template <typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const {
        return ConstIterator(this, nullptr);
    }

    // ---------------------------------- Node ---------------------------------- //

    template <typename T>
    SortedList<T>::Node::Node(const T& data, Node* next, Node* prev) : m_data(data), m_next(next), m_prev(prev) {}

    template <typename T>
    SortedList<T>::Node::Node(const Node& other) = default;

    template<typename T>
    typename SortedList<T>::Node & SortedList<T>::Node::operator=(const Node &other) = default;

    // -------------------------------- Iterator -------------------------------- //

    // constructors

    template <typename T>
    SortedList<T>::ConstIterator::ConstIterator(SortedList *sortedList, const Node *node) : m_SortedList(sortedList),
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

