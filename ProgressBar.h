#ifndef GOALS_PROGRESS_BAR_H
#define GOALS_PROGRESS_BAR_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <cassert>

class ProgressBar
{
public:
    ProgressBar(unsigned part_, unsigned whole_, unsigned length_)
        :_percentage((float)part_/(float)whole_*100.0)
        ,_partWholePair(std::make_pair(part_,whole_))
        ,_length(length_)
    {
        assert(part_ <= whole_);
    }

    std::string toString(){
        std::ostringstream oss;
        float progressBasedOnLength = (_percentage* _length)/100.0;

        oss << "["
            << generateCharString("#", progressBasedOnLength)
            << generateCharString(" ",_length - progressBasedOnLength)
            << "] "
            << _percentage << "% "
            << "( " << _partWholePair.first << "/"
            << _partWholePair.second << ")";
        
        return oss.str();
    }
                        
    friend std::ostream &operator<<( std::ostream &output, ProgressBar& progressBar_){
        output << progressBar_.toString();
        return output;
    }

    void setLength(unsigned length_){
        _length = length_;
    }

    std::string generateCharString(const char* char_, unsigned count_){
        std::ostringstream oss;
        for(unsigned i = 0; i < count_; i++) {
            oss << char_;
        }
        return oss.str();
    }


private:
    

    float                                _percentage;
    std::pair<unsigned, unsigned>        _partWholePair;
    unsigned                             _length;
};


#endif
