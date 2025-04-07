/*  
    Ayush Karki
    Project 1 - Move Semantics
    Professor Tojeira
    CSCI 33500 Fall 2024
    File.cpp 
*/
#include "File.hpp"
#include "Folder.hpp"
      
std::string File::getName() const {
   return filename_;
}

std::string File::getContents() const {
   return contents_;
}

void File::setContents(const std::string& new_contents) {
   contents_ = new_contents;
}

int* File::getIcon() const {
   return icon_;
}

void File::setIcon(int* new_icon) {
   if (icon_) { delete[] icon_; }
   icon_ = new_icon;
} 

std::ostream& operator<< (std::ostream& os, const File& target) {
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents(); 
   return os;
}

bool File::operator<(const File& rhs) const {
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a; 
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================


/**
* @brief Constructs a new File object.
* 
* @param filename A const reference to a string containing alphanumeric characters and exactly one period in the format "filename" or "filename.extension"
*    - If the string contains any non-alphanumeric characters besides *exactly_one* period an InvalidFormatException is thrown
*    - If no extension is provided (e.g. there is no period within the provided filename) or nothing follows the period, then ".txt" is used as the extension
*    - Default value of "NewFile.txt" if none provided or if filename is empty 
* @param contents A string representing the contents of the file. Default to empty string if none provided.
* @param icon A pointer to an integer array with length ICON_DIM. Default to nullptr if none provided.
* @throws InvalidFormatException - An error that occurs if the filename is not valid by the above constraints.
* @note You'll notice we provide a default value for the first possible argument (filename)
*       Yes, this means we can define override the default constructor and define a parameterized one simultaneously.
*/
File::File(const std::string& filename, const std::string& contents, int* icon) 
{
    // If the filename is empty, default to "NewFile.txt"
    if (filename.empty()) 
    {
        filename_ = "NewFile.txt"; // Assign "NewFile.txt" to filename_
    } 
    else 
    {
         // checks if there is a period (.) in the filename
        bool has_period = false; 
        // Loop through each character in the filename string
        for (char ch : filename) 
        {
            // If the character is a period
            if (ch == '.') 
            {
                // If already encountered a period, throw an exception (only one period allowed)
                if (has_period) 
                {
                    throw InvalidFormatException("The filename can only have one period."); // Error for multiple periods
                }
                has_period = true;  // there's at least one period
            }
            // If the character isn't alphanumeric and not a period, throw an invalid character exception 
            if (!std::isalnum(ch) && ch != '.') 
            {
                throw InvalidFormatException("Invalid characters."); // Error if any invalid characters are found
            }
        }
        // If no period was found, append ".txt" as the default extension
        if (!has_period) 
        {
            filename_ = filename + ".txt"; // No period found, add ".txt" extension
        }
        // If the filename ends with a period, add "txt" (e.g., "file." becomes "file.txt")
        else if (filename.back() == '.') 
        {
            filename_ = filename + "txt";
        } 
        else 
        {
            // If all is well, just use the provided filename
            filename_ = filename;
        }
    }
    // Set the contents of the file
    contents_ = contents;
    // Initialize the icon pointer (could be nullptr)
    icon_ = icon;
}


/**
* @brief Calculates and returns the size of the File Object (IN BYTES), using .size()
* @return size_t The number of bytes the File's contents consumes
* @note Consider this: how does this relate to the string's length? Why is that the case?
*/
size_t File::getSize() const 
{
    //The file's size is basically how many bytes its content takes up as a string
   return contents_.size();
}


/**
       * @brief (COPY CONSTRUCTOR) Constructs a new File object as a deep copy of the target File
       * @param rhs A const reference to the file to be copied from
*/
File::File(const File& rhs) : filename_(rhs.filename_), contents_(rhs.contents_), icon_(nullptr) 
{
    // If the file we're copying from has an icon, we need to perform a deep copy
   if(rhs.icon_) 
   {
      // Allocate memory for the new icon
      icon_ = new int[ICON_DIM];
      // Copy the contents of the old icon into the new one
      std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
   }
   // If rhs.icon_ is null, icon_ will stay null, so no deep copy is needed
}


/**
       * @brief (COPY ASSIGNMENT) Replaces the calling File's data members using a deep copy of the rhs File.
       * 
       * @param rhs A const reference to the File object to be copied
       * @return A reference to the new File copy
       * @note If copy assignment operator is invoked upon itself, do nothing.
*/
File& File::operator=(const File& rhs) 
{
    // Check if the object is not being assigned to itself.
    if (this != &rhs) 
    {
        // Copy the filename from the right-hand side (rhs) File to the current object.
        filename_ = rhs.filename_;
        // Copy the contents from the rhs File to the current object.
        contents_ = rhs.contents_; 
        // Delete the current object's icon (if it exists) to avoid memory leaks.
        delete[] icon_;
        // Check if the rhs File has a valid icon (not null).
        if (rhs.icon_) // If the rhs File has an icon, deep copy it
        {
            // Allocate new memory for the icon in the current object.
            icon_ = new int[ICON_DIM];
            // Copy the icon data from rhs to the newly allocated memory in the current object.
            std::copy(rhs.icon_, rhs.icon_ + ICON_DIM, icon_);
        } else 
        {
            // If rhs.icon_ is nullptr, set icon_ to nullptr as well
            icon_ = nullptr;
        }
    }
    return *this; // Return the current object
}


/**
       * @brief (MOVE CONSTRUCTOR) Construct a new File object by moving the data from the righthand side File Object
       * @param rhs The File whose data is moved
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are themselves moved.
       *    - ALl pointers are set to nullptr
*/
File::File(File&& rhs) 
:filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_) 
{
   // After moving the icon pointer, set the rhs's icon to nullptr (so no double-deletion)
   rhs.icon_ = nullptr; 
}


/**
       * @brief (MOVE ASSIGNMENT) Move the rhs data to the calling file object
       * 
       * @param rhs The File whose data is moved
       * @return A reference to the object which the data was moved into
       * @post The rhs File object is left in a valid, but ready to be deleted state:
       *    - All string members are moved.
       *    - ALl pointers are set to nullptr
       * @note If move assignment operator is invoked upon itself, do nothing.
*/
File& File::operator=(File&& rhs) 
{
    // Check if the object is not being assigned to itself.
    if (this != &rhs) 
    {
        // Move the filename from the right-hand side (rhs) File to the current object.
        // This transfers the string without copying it.
        filename_ = std::move(rhs.filename_);
        // Move the contents from the rhs File to the current object in the same way.
        contents_ = std::move(rhs.contents_);
        // Delete the current object's icon (if it exists) to avoid memory leaks.
        delete[] icon_;
        // Transfer ownership of the icon pointer from rhs to the current object.
        // This avoids copying the icon array.
        icon_ = rhs.icon_;
        // Set the icon pointer in rhs to nullptr, so it no longer points to the moved data.
        rhs.icon_ = nullptr;
    }
    // Return the current object (now with the moved data) by reference.
    return *this;
}


/**
       * @brief (DESTRUCTOR) Routine for object deletion
       * @post All dynamically allocated memory is released
*/
File::~File() 
{
   // Free up dynamically allocated memory for the icon
   delete [] icon_; 
}