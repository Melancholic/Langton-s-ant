#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include <utility> 
#include <iostream>
#include <fstream>
#include<string>
struct par_ant_start{
    int x,y, orient;
};


class parser{
    par_ant_start parAntStart;
    std::vector< std::pair<int,int>  > Points;
    bool CfgStatus;
public:
    parser();
    parser(std::string a);
    bool getCfgStatus();
    par_ant_start getParAntStart();
    std::vector< std::pair<int,int>  > getPoints();
    void parse(std::ifstream& file);
};



#endif /*PARSER_H*/
