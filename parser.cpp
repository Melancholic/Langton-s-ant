#include"parser.h"
#include<vector>
#include <utility> 
#include <iostream>
#include <fstream> 
#include<string>
#include<sstream>

parser::parser(std::string a){
    std::ifstream File(a.c_str());
    if(File.fail()){
        std::cerr<<"\n"<<"Err open file: set default propeties\n";
        CfgStatus = false;
    }else{
        parse(File);
         CfgStatus = true;    
    }
    File.close();
}

parser::parser(){
    CfgStatus = false;
}

void parser::parse( std::ifstream& file){
    while(!file.eof()){
        std::vector<std::string > params;
        std::string ParamLine;
        std::getline(file,ParamLine);
        while(ParamLine[0]==' '){
            ParamLine.erase(0,1);
        }
        if(ParamLine[0]=='#'){
            continue;
        }
        while(ParamLine.find(" ")!=-1){
            params.push_back(ParamLine.substr(0,ParamLine.find(" ")));
            ParamLine.erase(0,ParamLine.find(" ")+1);
        }
        params.push_back(ParamLine);
        switch(params.size()){
           case 2:{
                int x, y;
                std::istringstream th1(params[0]);
                th1>>x;
                std::istringstream th2(params[1]);
                th2>>y;
                Points.push_back(std::make_pair(x,y));
           };break;
           case 3:{
                int x, y, o;
                std::istringstream th1(params[0]);
                th1>>x;
                std::istringstream th2(params[1]);
                th2>>y;
                std::istringstream th3(params[2]);
                th3>>o;
                if(o<0){
                    o+=360;
                }else{
                    o=o%360;
                }
                parAntStart.x=x;
                parAntStart.y=y;
                parAntStart.orient=o;
            };break;
        }
    }
}

std::vector< std::pair<int,int>  > parser::getPoints(){
    return Points;
}

par_ant_start parser::getParAntStart(){
    return parAntStart;
}

bool parser::getCfgStatus(){
    return CfgStatus;
}
