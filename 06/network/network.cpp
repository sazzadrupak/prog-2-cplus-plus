#include "network.h"
#include <iostream>
#include <algorithm>

Network::Network(string name): name_(name)
{

}

string Network::get_name() const
{
    return name_;
}

/*
 * This method just for test print the vector. Not required for this problem.
 */
void Network::print(std::vector<People> people_) const
{
    unsigned int index = 0;
    for (std::vector<People>::iterator it = people_.begin() ; it != people_.end(); ++it) {
         index = static_cast<unsigned int>(std::distance(people_.begin(), it));
        std::cout << index << "--" << it->recruiter <<' ' << it->name << std::endl;
    }
}

unsigned int Network::get_id(std::vector<People> people_) const
{
    auto it = std::find_if(people_.begin(), people_.end(),
                           [this] (const People& d) {
                              return d.name == name_;
                           });
    unsigned int people_id = static_cast<unsigned int>(it - people_.begin());
    return people_id;
}

bool Network::check_exist(std::vector<People> people_) const
{
    auto it = std::find_if(people_.begin(), people_.end(),
                           [this] (const People& d) {
                              return d.name == name_;
                           });
    return it != people_.end();
}

void Network::print_people_network(std::string people_name_, std::vector<People> people_) const
{
    auto it = std::find_if(people_.begin(), people_.end(),
                           [people_name_] (const People& d) {
                              return (d.name == people_name_);
                           });

    int people_index = static_cast<int>(it - people_.begin());
    std::cout << it->name << std::endl;
    find_people_network(people_index, people_, 0);
}

void Network::count_subnetwork_size(string people_name_, std::vector<People> people_) const
{
    auto it = std::find_if(people_.begin(), people_.end(),
                           [people_name_] (const People& d) {
                              return (d.name == people_name_);
                           });

    int people_index = static_cast<int>(it - people_.begin());
    std::cout << (count_people_network_size(people_index, people_, 0) - 1) << std::endl;
}

void Network::subnetwork_depth(string people_name_, std::vector<People> people_) const
{
    auto it = std::find_if(people_.begin(), people_.end(),
                           [people_name_] (const People& d) {
                              return (d.name == people_name_);
                           });

    int people_index = static_cast<int>(it - people_.begin());
    std::vector<int> people_names;
    std::cout << count_subnetwork_depth(people_index, people_, 0) + 1 << std::endl;
}

bool Network::find_people_network(int recruiter, std::vector<People> args, int i) const
{
    i += 2;
    std::string stuff(i, '.');
    for (std::vector<People>::iterator it = args.begin(); it != args.end(); ++it) {
        int index = static_cast<int>(std::distance(args.begin(), it));
        if (index != recruiter){
            if(recruiter != it->recruiter){
                continue;
            } else {
                std::cout << stuff << it->name << std::endl;
                find_people_network(index, args, i);
            }
        }
    }
    return true;
}

unsigned int Network::count_people_network_size(int recruiter, std::vector<People> args, unsigned int sum) const
{
    sum = 1;
    for (std::vector<People>::iterator it = args.begin(); it != args.end(); ++it) {
        int index = static_cast<int>(std::distance(args.begin(), it));
        if (index != recruiter){
            if(recruiter != it->recruiter){
                continue;
            } else {
                sum = sum + count_people_network_size(index, args, sum);
            }
        }
    }
    return sum;
}

unsigned int Network::count_subnetwork_depth(int recruiter, std::vector<People> args, unsigned int j) const
{
    j = 1;
    for (std::vector<People>::iterator it = args.begin(); it != args.end(); ++it) {
        int index = static_cast<int>(std::distance(args.begin(), it));
        if (index != recruiter){
            if(recruiter != it->recruiter){
                continue;
            } else {
                return j + count_subnetwork_depth(index, args, j);
            }
        }
    }
    return 0;
}
