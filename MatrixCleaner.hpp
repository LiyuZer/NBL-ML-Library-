//
//  MatrixCleaner.hpp
//  openCVtest
//
//  Created by Liyu Zerihun on 8/25/22.
//

#ifndef MatrixCleaner_hpp
#define MatrixCleaner_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>
class MatrixCleaner{
public:
    MatrixCleaner(){
        parameters=0;
        values=0;
        collective=0;
        Matrices.clear();
    }
    vector<T*>* getMatrixCleaner(){
        
        return &Matrices;
    }
    
    void print(){
        
        for(int i=0; i<Matrices.size(); i++){
            if(Matrices.at(i)->getActive()){
                if(Matrices.at(i)->get_is_parameter()){
                    parameters++;
                }
                else if(Matrices.at(i)->get_is_value_node()){
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
        cout<<Matrices.size()<<endl;

        parameters=0;
        values=0;
        collective=0;
    }
      void clear(){
        
        for(int i=0; i<Matrices.size(); i++){
            delete Matrices.at(i);
        }
        Matrices.clear();
        
        for(int i=0; i<Matrices.size(); i++){
            delete Matrices.at(i);
        }
        Matrices.clear();
    }
    ~MatrixCleaner(){

        
    }
    
    
   
    
private:
    
    vector<T*> Matrices;

    int parameters;
    int values;
    int collective;
    
    
    
};

#endif /* MatrixCleaner_hpp */
