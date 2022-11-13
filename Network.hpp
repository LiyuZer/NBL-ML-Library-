//
//  Network.hpp
//  openCVtest
//
//  Created by Liyu Zerihun on 8/17/22.
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>

class Network{
public:
    std::mutex mutel;

    Network(){
        parameters=0;
        values=0;
        collective=0;
        Nodes.clear();
    }
    vector<T*>* getNodes(){
        
        return &Nodes;
    }
    
    void push(T* num){
        mutel.lock();
        Nodes.push_back(num);
        mutel.unlock();
    }
    void print(){
        
        for(int i=0; i<Nodes.size(); i++){
            if(Nodes.at(i)->getActive()){
                if(Nodes.at(i)->get_is_parameter()){
                    parameters++;
                }
                else if(Nodes.at(i)->get_is_value_node()){
                    values++;
                }
                else{
                    collective++;
                }
            }
            
        }
        
        
        cout<<"These are the amount of nodes in the network:"<<endl;
        cout<<"Paramter Nodes: "<<parameters<<endl;
        cout<<"Value Nodes: "<<values<<endl;
        cout<<"Collective Nodes: "<<collective<<endl;
        cout<<Nodes.size()<<endl;

        parameters=0;
        values=0;
        collective=0;
    }
      void clear(){
        
        for(int i=0; i<Nodes.size(); i++){
            delete Nodes.at(i);
        }
        Nodes.clear();
        
    }
    ~Network(){

        
    }
    
    
   
    
private:
    
    vector<T*> Nodes;

    int parameters;
    int values;
    int collective;
    
    
    
};

#endif /* Network_hpp */
