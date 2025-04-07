/* 
Ayush Karki 
Project 1 - Move Semantics and Iterators
CSCI 33500 Spring 2024
*/

#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Book
{
    public:
        // Signatures for the zero-argument (default) constructor, the "big five", accessors, and mutators.
        // Implement and document these in Book.cpp.
        // DO NOT MODIFY THIS FILE.

        Book();
        ~Book();
        Book(const Book& rhs);
        Book& operator=(const Book& rhs);
        Book(Book&& rhs);
        Book& operator=(Book&& rhs);
        const std::string& getTitle() const;
        void setTitle(const std::string& title);
        const std::string& getAuthor() const;
        void setAuthor(const std::string& author);
        long long int getISBN() const;
        void setISBN(long long int ISBN);
        const int* getIcon() const;
        void setIcon(int* icon);
        float getPrice() const;
        void setPrice(float price);
        const std::vector<std::string>& getKeywords() const;
        void setKeywords(const std::vector<std::string>& keywords);
        const std::string& getBlurb() const;
        void setBlurb(const std::string& blurb);
        void print() const;

    private:
        std::string title_;
        std::string author_;
        long long int ISBN_;
        int* icon_;
        float price_;
        std::vector<std::string> keywords_;
        std::string blurb_;
};

#endif
