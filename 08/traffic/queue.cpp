#include "queue.hh"
#include <iostream>
// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    cycle_(cycle)
{

}

Queue::~Queue()
{
    while ( first_ != nullptr ) {
		Vehicle* v = first_;
		first_ = first_->next;

		delete v;
	}
}

void Queue::enqueue(string reg)
{
    Vehicle* new_vehicle = new Vehicle({reg, nullptr});
    if(!is_green_){
        if(first_ == nullptr){
            first_ = new_vehicle;
        } else {
            last_->next = new_vehicle;
        }

        last_ = new_vehicle;
    } else {
        std::cout<<"GREEN: The vehicle "<< reg <<" need not stop to wait"<<std::endl;
    }
}

void Queue::switch_light()
{
    is_green_ = !is_green_;
    unsigned int i = 1;
    if(is_green_){
        std::cout<<"GREEN: ";
    } else {
        std::cout<<"RED: ";
    }

    if(first_ != nullptr){
        Vehicle * temp = first_;
        std::cout<<"Vehicle(s) ";
        while(temp != nullptr && i <= cycle_){
            std::cout<<temp->reg_num<<" ";
            Vehicle * temp1;
            temp1 = temp->next;
            this->dequeue(temp);
            temp = temp1;
            i++;
        }
        std::cout<<"can go on"<<std::endl;
        is_green_ = !is_green_;
    } else {
        std::cout<<"No vehicles waiting in traffic lights"<<std::endl;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print()
{
    Vehicle * vehicle = first_;
    if (!is_green_){
        std::cout<<"RED: ";
    } else {
        std::cout<<"GREEN: ";
    }

    if(first_ != nullptr){
        std::cout<<"Vehicle(s) ";
        while (vehicle) {
            std::cout<<vehicle->reg_num<<" ";
            vehicle = vehicle->next;
        }
        std::cout<<"waiting in traffic lights"<<std::endl;
    } else {
        std::cout<<"No vehicles waiting in traffic lights"<<std::endl;
    }
}

void Queue::dequeue(Queue::Vehicle *vehicle)
{
    if(is_green_){
        first_ = vehicle->next;
        delete vehicle;
    }
}
