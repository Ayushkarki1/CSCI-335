/* 
Ayush Karki 
Project 1 - Move Semantics and Iterators
CSCI 33500 Spring 2024
*/

#include "Book.hpp"

// Default constructor
Book::Book()
    : title_(""),    // Initialize title to empty string
      author_(""),   // Initialize author to empty string
      ISBN_(0),      // Initialize ISBN to 0
      icon_(nullptr),// Initialize icon pointer to nullptr
      price_(0.0),// Initialize price to 0.0
      keywords_(),// Initialize keywords vector to empty
      blurb_("") {// Initialize blurb to empty string
}

// Destructor
Book::~Book() { 
    // Deallocate any dynamically allocated memory (e.g., icon_)
    delete[] icon_; 
}



// Copy constructor
Book::Book(const Book& rhs) : title_(rhs.title_),// Copy title from rhs
      author_(rhs.author_),// Copy author from rhs
      ISBN_(rhs.ISBN_),// Copy ISBN from rhs
      price_(rhs.price_),// Copy price from rhs
      keywords_(rhs.keywords_),// Copy keywords from rhs
      blurb_(rhs.blurb_) {// Copy blurb from rhs
    if (rhs.icon_ != nullptr) {// Check if rhs has a valid icon
        icon_ = new int[80];// Allocate memory for icon
        for (int i = 0; i < 80; i++) {// Copy icon values from rhs
            icon_[i] = rhs.icon_[i];
        }
    } else {
        icon_ = nullptr;// Set icon to nullptr if rhs has no icon
    }
}

// Copy assignment operator
Book& Book::operator=(const Book& rhs) {
    // Copy non-pointer members directly from rhs
    title_ = rhs.title_;
    author_ = rhs.author_;
    ISBN_ = rhs.ISBN_;
    price_ = rhs.price_;
    keywords_ = rhs.keywords_;
    blurb_ = rhs.blurb_;
    // Delete existing icon_ array to avoid memory leak
    delete icon_;
    // Check if rhs has a valid icon_
    if (rhs.icon_ != nullptr) { 
        // Allocate memory for icon_ and copy values from rhs
        icon_ = new int[80];
        std::copy(rhs.icon_, rhs.icon_ + 80, icon_);
    } else
    // If rhs has no icon_, set icon_ to nullptr 
    { icon_ = nullptr;}
    return *this;
}




// Move constructor
Book::Book(Book&& rhs): title_(std::move(rhs.title_)),// Move title_ from rhs
      author_(std::move(rhs.author_)),// Move author_ from rhs
      ISBN_(std::move(rhs.ISBN_)),// Move ISBN_ from rhs
      icon_(rhs.icon_),// Move icon_ pointer from rhs
      price_(std::move(rhs.price_)),// Move price_ from rhs
      keywords_(std::move(rhs.keywords_)),// Move keywords_ from rhs
      blurb_(std::move(rhs.blurb_)) {// Move blurb_ from rhs
    rhs.icon_ = nullptr;// Nullify the pointer in the source object
}

// Move assignment operator
Book& Book::operator=(Book&& rhs) {
        // Move non-pointer members from rhs
        title_ = std::move(rhs.title_);
        author_ = std::move(rhs.author_);
        ISBN_ = std::move(rhs.ISBN_);
        price_ = std::move(rhs.price_);
        keywords_ = std::move(rhs.keywords_);
        blurb_ = std::move(rhs.blurb_);
        // Delete existing icon_ to avoid memory leak
        delete icon_;
        // Move icon_ pointer from rhs
        icon_ = rhs.icon_;
        // Nullify the pointer in rhs to avoid deletion of icon_ in both objects
        rhs.icon_ = nullptr;
        return *this;
}


// Get the title of the book
const std::string& Book::getTitle() const {
    return title_;
}

// Set the title of the book
void Book::setTitle(const std::string& title) {
    title_ = title;
}

// Get the author of the book
const std::string& Book::getAuthor() const {
    return author_;
}

// Set the author of the book
void Book::setAuthor(const std::string& author) {
    author_ = author;
}

// Get the ISBN of the book
long long int Book::getISBN() const {
    return ISBN_;
}

// Set the ISBN of the book
void Book::setISBN(long long int ISBN) {
    ISBN_ = ISBN;
}

// Get the Icon of the book
const int* Book::getIcon() const {
    return icon_;
}

// Set the Icon of the book
void Book::setIcon(int* icon) {
    delete icon_; // Free existing memory
    icon_ = icon;
}

// Get the price of the book
float Book::getPrice() const {
    return price_;
}

// Set the price of the book
void Book::setPrice(float price) {
    price_ = price;
}

// Get the keywords of the book
const std::vector<std::string>& Book::getKeywords() const {
    return keywords_;
}

// Set the keywords of the book
void Book::setKeywords(const std::vector<std::string>& keywords) {
    keywords_ = keywords;
}

// Get the blurb of the book
const std::string& Book::getBlurb() const {
    return blurb_;
}

// Get the blurb of the book
void Book::setBlurb(const std::string& blurb) {
    blurb_ = blurb;
}

void Book::print() const {
    // Print the title of the book
    std::cout << "Title: " << title_ << "\n";
    // Print the author of the book
    std::cout << "Author: " << author_ << "\n";
    // Print the ISBN of the book
    std::cout << "ISBN: " << ISBN_ << "\n";
    // Print the icon of the book
    std::string icon;
    int *icon_ptr = icon_;
    for (int i = 0; i < 80; i++) { 
        icon += std::to_string(*icon_ptr) + " "; icon_ptr++;}
    // Remove the extra space at the end
    icon = icon.substr(0, icon.size() -1); 
    // Print the price of the book
    std::cout << "Icon: " << icon << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price_ << std::endl;
    // Print the keywords of the book
    std::string keywords;
    for (auto kw = this->getKeywords().begin(); kw != this->getKeywords().end(); kw++)
    {keywords += (*kw + ", ");}
    keywords = keywords.substr(0, keywords.size() -2);            
    std::cout << "Keywords: " << keywords << "\n"; 
    // Print the blurb of the book
    std::cout << "Blurb: " << blurb_ << std::endl;
}
