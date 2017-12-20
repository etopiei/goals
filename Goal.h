#include <iostream>

struct Goal
{
    Goal(const std::string& name_, unsigned max_, unsigned current_)
        :_name(name_)
        ,_max(max_)
        ,_current(current_)
    {}

    friend std::ostream &operator<<( std::ostream &output, const Goal& goal_){ 
        output << goal_.toString();
        return output;            
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << _name << std::endl << _max << std::endl<< _current << std::endl;

        return oss.str();
    }

    const std::string& getName() const{ return _name;}
    unsigned getMax() const{ return _max;}
    unsigned getCurrent() const{ return _current;}
    void incrementBy(int change_) { _current += change_;}
    
private:
        
    std::string       _name;
    unsigned          _max;
    unsigned          _current;
};
