#include "routes.hh"

Routes::Routes()
{

}

Routes::~Routes()
{
    // remove the pointer of pair Point struct from vector
    for(auto iter: routes_) {
        auto itr = iter.second;
        for (auto it = itr.begin() ; it != itr.end(); ++it){
            it->first = nullptr;
            it->second = nullptr;
        }
    }

    // remove the pointer of Point struct from map
    for(auto iter: points_) {
        delete iter.second;
        iter.second = nullptr;
    }
}

namespace {
    // Add space between the number of map width
    void add_space_to_width(int &val){
        if(val < 10){
            std::cout <<"  "; // add two empty space before the current number if the number is less than 10
        } else {
            std::cout <<" ";  // add one empty space before the current number if the number is less than 10
        }
    }

    // Add space between the number of map height
    void add_space_to_height(int &val){
        if(val < 10){  // add one empty space before the current number if the number is less than 10
            std::cout <<" ";
        }
    }

    // return the greatest rise value from a point in the map
    int get_greatest_rise(std::vector<std::pair<Point *, Point *>> routes, std::string point_name){
        int rise_value = 0;  // variable to store the rise value
        for (auto it = routes.begin() ; it != routes.end(); ++it){
            if(it->first->name == point_name){  // check if the first value of the pair is same wit the given point name
                int height_diff = it->second->height - it->first->height;  // get the height/rise diff between the point pairs
                if( height_diff > rise_value){  // check if height_diff is greater than the stored rise_value
                    rise_value += height_diff;  // add the pair difference with the rise_value
                    point_name = it->second->name;  // update the point_name with pair's second points name
                } else {
                    // break the loop if there is a fall of height rise
                    break;
                }
            }
        }
        // return the summed rise_value from height difference of the given point
        return rise_value;
    }
}

void Routes::set_map_size(int width, int height)
{
    map_width_ = width;  // assign the width from file to map's width variable
    map_height_ = height;  // assign the height from file to map's height variable

    // create a 2D vector from width and height
    for (int i = 1; i <= map_height_+1; i++)
    {
        std::vector<char> temp;
        for (int j = 1; j <= map_width_+1; j++)
        {
            temp.push_back('.');  // initially in every coordinates of 2D vector are filled with '.'
        }
        vec_of_map.push_back(temp);
    }
}

void Routes::add_point(std::string &name, int x, int y, int height, char marker)
{
    Point* new_point = new Point({name, x, y, height, marker});  // Create a struct will value from file
    points_.insert({ name, new_point });  // insert the struct as value and name as key in the map container
    vec_of_map[static_cast<unsigned long long>(y)][static_cast<unsigned long long>(x)] = marker;  // update the coordinates value from '.' to point marker for given x and y
}

bool Routes::connect_route(std::string &from, std::string &to, std::string &route_name)
{
    auto iter = routes_.find(route_name);  // find route name from map container
    if (iter != routes_.end()) {  // route name found
        std::vector<std::pair<Point *, Point *>> route_points = iter->second;  // create a temp vector of Point pair to hold the map's struct value
        route_points.push_back(std::make_pair(points_[from], points_[to]));  // made a pair of from and to Points and insert it to vector
        routes_[route_name] = route_points;  // add the pair vector to the map's route_name key
    } else {
        std::vector<std::pair<Point *, Point *>> route_points;  // initialize an pair of Point's vector
        route_points.push_back(std::make_pair(points_[from], points_[to]));  // made a pair of from and to Points and insert it to vector
        routes_.insert({route_name, route_points});  // insert the pair vector as value and route name as key to the map container
    }
    return true;
}

void Routes::print_map() const
{
    std::cout << " ";  // add an empty space before the map's width values list
    for(int x = 1; x <= map_width_; x++) {
        add_space_to_width(x);  // add space before every number
        std::cout << (x);
    }
    std::cout<<std::endl;

    for(int y = 1; y <= map_height_; y++) {
        add_space_to_height(y);  // add space before every height number
        std::cout<<(y);
        for(int x = 1; x <= map_width_; x++) {
            // print the marker to the exact coordinate position, get marker value from map vector
            std::cout << "  "<<vec_of_map[static_cast<unsigned long long>(y)][static_cast<unsigned long long>(x)];
        }
        std::cout<<std::endl;
    }
}

void Routes::print_route_names() const
{
    std::cout<<"Routes:"<<std::endl;
    for (auto itr = routes_.begin(); itr != routes_.end(); ++itr) {
        std::cout << " - " << itr->first<<std::endl;
    }
}

void Routes::print_points() const
{
    std::cout<<"Points:"<<std::endl;

    for (auto itr = points_.begin(); itr != points_.end(); ++itr) {
        std::cout << " - " << itr->first
             << " : " << itr->second->marker <<std::endl;
    }
}

void Routes::print_route(const std::string &name) const
{
    if(name != " "){
        auto it = routes_.find(name);
        if (it != routes_.end())
        {
            std::vector<std::pair<Point *, Point *>> routes = it->second;
            unsigned long long int vector_size = routes.size();
            if(vector_size == 1){
                // if there's only one pair of Points, just print the first and second Point of vector 0 index
                std::cout<<routes[0].first->name<<std::endl;
                std::cout<<" -> "<<routes[0].second->name<<std::endl;
            } else {
                unsigned long long int i = 1;  // temporarily variable used to check the first Point of the routes
                for (auto it = routes.begin() ; it != routes.end(); ++it){
                    if(i == 1){  // this is the first Point of routes, don't add "->" before it
                        std::cout<<(*it).first->name<<std::endl;
                    } else if(i == vector_size){  // this is the last item of the pair value vector, print both Point of the pair
                        std::cout<<" -> "<<(*it).first->name<<std::endl;
                        std::cout<<" -> "<<(*it).second->name<<std::endl;
                    } else { // this is inbetween first and last element of the vector, just print the first Point of the pair
                        std::cout<<" -> "<<(*it).first->name<<std::endl;
                    }
                    i++;
                }
            }
        } else {
            std::cout<<"Error: Route named "<<name<<" can't be found"<<std::endl;
        }
    } else {
        std::cout<<"Error: Wrong amount of parameters"<<std::endl;
    }
}

void Routes::route_length(const std::string &name) const
{
    if(name != " "){
        auto it = routes_.find(name);
        if (it != routes_.end()){  // name found in map container
            double length = 0.0;  // initialize a double type variable to store the length
            std::vector<std::pair<Point *, Point *>> routes = it->second;  // get the second value of map which is a pair of Point of vector
            for (std::vector<std::pair<Point *, Point *>>::iterator it = routes.begin() ; it != routes.end(); ++it){
                length += double(sqrt(pow(it->first->x - it->second->x, 2) + pow(it->first->y - it->second->y, 2)));
            }
            std::cout<<"Route "<<name<<" length was "<<std::setprecision(2)<<length<<std::endl;
        } else {
            std::cout<<"Error: Route named "<<name<<" can't be found"<<std::endl;
        }
    } else {
        std::cout<<"Error: Wrong amount of parameters"<<std::endl;
    }
}

void Routes::greatest_rise(const std::string &point_name) const
{
    auto iter = points_.find(point_name);
    if (iter != points_.end()){     // found the key in the map container
        int rise_value = 0;     // initialize a int type variable to store the rise value
        std::vector<std::string> route_names;       // initialize a vector to store the routes name
        for (auto itr = routes_.begin(); itr != routes_.end(); ++itr) {
            std::vector<std::pair<Point *, Point *>> shorter_routes = itr->second;
            int temp = get_greatest_rise(shorter_routes, point_name);       // get the sum of rise value for a route name
            if(temp > rise_value){      // current "route name"'s sum of rise value is greater than previous "route name"
                rise_value = temp;      // update the previous ries value with the current rise value
                route_names.clear();        // delete all names from vector as we found new route name with higher rise value
                route_names.push_back(itr->first);      // insert current route name to vector which has highest rise value so far
            } else if (temp == rise_value) {        // the previous route's rise value and current route's rise value are same
                // as previous and current rise value are same, append current route name to the vector
                route_names.push_back(itr->first);
            }
        }

        if(rise_value > 0){ // there are rise of height from given point name
            std::cout<<"Greatest rise after point "<< point_name <<", "<<rise_value<<" meters, is on route(s):\n";
            for (std::vector<std::string>::iterator it = route_names.begin() ; it != route_names.end(); ++it){
                std::cout<<" - "<<*it<<std::endl;
            }
        } else {  // no rise of heights from given point name
            std::cout<<"No route rises after point "<<point_name<<std::endl;
        }
    } else {
        std::cout<<"Error: Point named "<<point_name<<" can't be found"<<std::endl;
    }
}
