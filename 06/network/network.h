#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>

using namespace std;

struct People{
    std::string name;
    int recruiter;
};

class Network
{
public:
    Network(std::string name);
    string get_name() const;
    void print(std::vector<People> people_) const;
    unsigned int get_id(std::vector<People> people_) const;
    bool check_exist(std::vector<People> people_) const;
    void print_people_network(std::string people_name_, std::vector<People> people_) const;
    void count_subnetwork_size(std::string people_name_, std::vector<People> people_) const;
    void subnetwork_depth(std::string people_name_, std::vector<People> people_) const;
private:
    string name_;
    bool find_people_network(int people_index_, std::vector<People> people_, int i) const;
    unsigned int count_people_network_size(int people_index_, std::vector<People> people_, unsigned int sum_) const;
    unsigned int count_subnetwork_depth(int people_index_, std::vector<People> people_, unsigned int j) const;
};

#endif // NETWORK_H
