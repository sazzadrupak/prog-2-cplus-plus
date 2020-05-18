#include "library.hh"
#include <string>
#include <iostream>
#include <algorithm>

Library::Library()
{

}

/*
 * To show all libraries as a list
 */
void Library::libraries_list(std::map<std::string, std::vector<Book> > libraries)
{
    for (std::map<std::string, std::vector<Book>>::iterator i = libraries.begin(); i != libraries.end(); i++)
    {
        std::cout << i->first << std::endl;
    }
}

/*
 * To show all books in a Library
 */
void Library::material(std::map<std::string, std::vector<Book> > libraries, std::string library)
{
    if(libraries.find(library) != libraries.end()){  // check if library exist in map
        std::vector<Book> books = libraries[library];  // get the books as value from library map for given library name

        // sort the books vector based on author name
        std::sort(books.begin(), books.end(), [](const Book &a, const Book &b)
        {
            return (a.author < b.author);
        });

        // show the books in the given library ordered by author
        for (std::vector<Book>::iterator i = books.begin(); i != books.end(); i++){
            std::cout << i->author
                      << ": "
                      << i->title
                      << std::endl;
        }
    } else {  // library name not found in map
        std::cout<<"Error: unknown library name"<<std::endl;
    }
}

void Library::books(std::map<std::string, std::vector<Book> > libraries, std::string library, std::string author_name)
{
    if(libraries.find(library) != libraries.end()){  // check if library exist in map
        std::vector<Book> books = libraries[library];  // get the books as value from library map for given library name

        // find if the author name is available in the books vector
        auto it = std::find_if(books.begin(), books.end(),
                                   [author_name] (const Book& b) {
                                      return (b.author == author_name);
                                   });

        if(it != books.end()){  // author is available in the books vector

            // sort the books vector based on book title
            std::sort(books.begin(), books.end(), [](const Book &a, const Book &b)
            {
                return (a.title < b.title);
            });

            for (std::vector<Book>::iterator i = books.begin(); i != books.end(); i++){
                if(i->author == author_name){  // only shows those books whose writer matched with the given author name
                    std::string reservation = (i->reservation == 0) ? "on the shelf" : std::to_string(i->reservation) + " reservations";
                    std::cout << i->title
                              << " --- "
                              << reservation
                              << std::endl;
                }
            }
        } else {  // author not found in vector
            std::cout<<"Error: unknown author"<<std::endl;
        }
    } else {  // library not found in map
        std::cout<<"Error: unknown library name"<<std::endl;
    }
}


/*
 * Find those books in all libraries which are reservable
 */
void Library::reservable(std::map<std::string, std::vector<Book> > libraries, std::string book_name)
{
    std::vector<Lib> all_books;  // initialize all_books vector with Lib struct to hold book library and reservation info

    for (std::map<std::string, std::vector<Book>>::iterator i = libraries.begin(); i != libraries.end(); i++)
    {
        std::string library_name = i->first;
        for(auto const& element : i->second)   // Loop over elements of current map's books element
        {
            if(element.title == book_name){  // check if the current book title matched with the given book name
                all_books.push_back({library_name, element.reservation});  // store the book info as Lib struct in all_books vector
            }
        }
    }

    if(all_books.size() == 0){  // vector is empty, means reservable books not available

        std::cout << "Book is not a library book." << std::endl;

    } else { // reservable books are available

        // get the books minimum reservation number
        auto min = std::min_element(all_books.begin(), all_books.end(), [](const Lib &a, const Lib &b)
                            {
                                return (a.reservation < b.reservation);
                            });

        if(min->reservation > 99){  // check if the book reservation is 100 or more
            std::cout << "The book is not reservable from any library." << std::endl;
        } else {  // reservation is less than 100
            if(min->reservation == 0){
                // minimum reservation is 0, means print "on the self"
                std::cout << "on the shelf" << std::endl;
            } else {
                // minimum reservation is more than 1, print the number
                std::cout << min->reservation << " reservations" << std::endl;
            }

            // iterate all the books stored in all_books vector to show the reservable books belonged library
            for (std::vector<Lib>::iterator i = all_books.begin(); i != all_books.end(); i++){

                // show only those books which reservation number matched with the minimum reservation number
                if(i->reservation == min->reservation){
                    std::cout << "--- "
                              << i->library_name
                              << std::endl;
                }
            }
        }
    }
}

/*
 * Show those books which are available on the shelf
 */
void Library::loanable(std::map<std::string, std::vector<Book> > libraries)
{
    // initialize all_books map with author as key and struct Book as value
    std::map<std::string, std::vector<Book>> all_books;

    for (auto const& i : libraries)
    {
        std::string library_name = i.first;
        std::vector<Book> library_books = i.second;

        for(auto const& element : library_books)   // Loop over sorted book elements of current map
        {
            if(element.reservation == 0){  // check if the book is available on shelf or not
                const Book& book = {element.title, element.author, element.reservation};
                all_books[element.author].push_back(book);  // push the book struct to the all_books maps
            }
        }
    }

    // iterate throw the all_books map
    for (std::map<std::string, std::vector<Book>>::iterator i = all_books.begin(); i != all_books.end(); i++)
    {
        std::vector<Book> author_loanable_books = i->second;  // get the books of current author

        // sort the books based on book title
        std::sort(author_loanable_books.begin(), author_loanable_books.end(), [](const Book &a, const Book &b)
        {
            return (a.title < b.title);
        });

        for(auto const& element : author_loanable_books)   // Loop over the books of current current author
        {
            std::cout << i->first
                      << ": "
                      << element.title
                      << std::endl;
        }
    }
}

