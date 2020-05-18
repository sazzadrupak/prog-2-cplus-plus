#include "cards.hh"
// TODO: Implement the methods here

Cards::Cards(): top_(nullptr)
{

}


Cards::~Cards()
{
    while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_;
      top_ = top_->next;

      delete item_to_be_released;
   }
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id, top_};
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    if(!is_empty()){
        Card_data* item_to_be_printed = top_;
        int running_number = 1;
        if(item_to_be_printed->next != nullptr){
            while ( item_to_be_printed != nullptr ) {
              s << running_number << ": " << item_to_be_printed->data << std::endl;
              ++running_number;
              item_to_be_printed = item_to_be_printed->next;
            }
        } else {
            s << running_number << ": " << item_to_be_printed->data << std::endl;
        }
    }
}

bool Cards::remove(int &id)
{
    if(!is_empty()){
        Card_data* current_node = top_;
        if(current_node->next != nullptr){
            top_ = current_node->next;
        }
        id = current_node->data;
        delete current_node;
        return true;
    }
    return false;
}

bool Cards::bottom_to_top()
{
    if(!is_empty()){
        Card_data* item_to_be_printed = top_;
        Card_data* last_element = nullptr;
        if(item_to_be_printed->next != nullptr){
            while ( item_to_be_printed->next != nullptr ) {
                last_element = item_to_be_printed;
                item_to_be_printed = item_to_be_printed->next;
            }
            last_element->next = nullptr;
            item_to_be_printed->next = top_;
            top_ = item_to_be_printed;
        }
        return true;
    }
    return false;
}

bool Cards::top_to_bottom()
{
    if(!is_empty()){
        Card_data* first_element = top_;
        Card_data* last_element = top_;
        if(first_element->next != nullptr){
            while ( last_element->next != nullptr ) {
                last_element = last_element->next;
            }
            top_ = first_element->next;
            first_element->next = nullptr;
            last_element->next = first_element;
        }
        return true;
    }
    return false;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if(!is_empty()){
        Card_data* first_element = top_;
        if(first_element->next != nullptr){
            print_recursive(top_);
            print_from_top_to_bottom(s);
        } else {
            s <<"1: "<<first_element->data << std::endl;
        }
    }
}

bool Cards::is_empty() const
{
    if ( top_ == nullptr ) {
          return true;
       } else {
          return false;
    }
}

Cards::Card_data *Cards::print_recursive(Cards::Card_data *top)
{
    if (top == nullptr)
        return nullptr;
    if (top->next == nullptr) {
        top_ = top;
        return top;
    }
    Card_data* card1 = print_recursive(top->next);
    card1->next = top;
    top->next = nullptr;
    return top;
}
