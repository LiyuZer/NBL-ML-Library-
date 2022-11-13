//
//  layer.hpp
//  openCVtest
//
//  Created by Liyu Zerihun on 8/10/22.
//
#include "Matrix.hpp"
#include "Network.hpp"
#include <iostream>

#ifndef layer_hpp
#define layer_hpp

using namespace std;

class layer{
    
    
public:
    layer(){
        
    }
    
   virtual void propogate(){
        
        
    }
    virtual void getInput(){
        
    }
    
};


class fullyConnected: public layer{
    
public:
    fullyConnected(int array[], int size, Network<Node>* n){
        inputLayer=nullptr;

        numberOfLayers=size;
        for(int i=0; i<size; i++){
            if(i==0 || i==size-1){
                if(i==0){
                    int dimensionsForInput[1]={array[i]};
                    inputLayer= new Matrix<value_node>(array,1,n, true);
               
                }
                else{
                    int dimensions[2]={array[i-1],1};
                    int weightMatrix[2]={array[i],array[i-1]};
                    int dimensionsForOutput[1]={array[i]};
                    
                    Matrix<value_node>* nodeLayer= new Matrix<value_node>(dimensionsForOutput, 1,n, true);
                    outputLayer=nodeLayer;
                    
                    
                    
                   
                }

            }
            else{

                int dimensions[2]={array[i-1],1};
                int oneDimensional[1]={array[i-1]};
                int weightMatrix[2]={array[i],array[i-1]};

                
                
                Matrix<value_node>* hiddenNodes= new Matrix<value_node>(dimensions, 2, n, true);
                hiddenLayer.push_back(hiddenNodes);
            }
        }
        
    
}
    
   void initiateInput(Matrix<value_node>& input){
       for(int i=0; i<input.getHeaders()->size(); i++){
           int array[1]={i};
           inputLayer->setA(array,1,input.getHeaders()->at(i));

           
       }
       
   }

       
       
       
    Matrix<value_node>* getMatrixOutput(){
        return outputLayer;
    }
    
    vector<Matrix<parameter_node>*>& getWeightMatrix(){
        return weights;
    }
    vector<Matrix<value_node>*>& getHiddenMatrix(){
        return hiddenLayer;
    }
    
    vector<parameter_node*>& getBias(){
        return bias;
    }
    
    void propogate(){

        for(int i=0; i<numberOfLayers; i++){
            if(i==0){
                hiddenLayer.at(0)=&((weights.at(0)->linearTransform(*inputLayer)).addBias(*bias.at(i)).attach_collective_nodes(0));
            }
            
           else if(i==numberOfLayers-1){
           }
           else if(i==numberOfLayers-2) {
               outputLayer= &((weights.at(i)->linearTransform(*hiddenLayer.at(i-1))).addBias(*bias.at(i)));


           }
           else{
               hiddenLayer.at(i)= &((weights.at(i)->linearTransform(*hiddenLayer.at(i-1))).addBias(*bias.at(i)).attach_collective_nodes(0));
           }
            
        }
        
    }
    void initiateWeight( vector<Matrix<parameter_node>*>& initialVal){
            
            weights=initialVal;
            
        
    }
    
    void initiateBias(   vector<parameter_node*>& initialVal){
            
            bias=initialVal;
            
        
    }
   
    
    void update(bool timeForUpdate){
        
        
        for(int i=0; i<weights.size(); i++){
            weights.at(i)->update(timeForUpdate);
        }
    for(int i=0; i<bias.size(); i++){
        bias.at(i)->update(timeForUpdate);
    }
    
    
    }
    
    ~fullyConnected(){
        
        delete outputLayer;
        for(int i=0; i< hiddenLayer.size(); i++){
            delete hiddenLayer.at(i);
        }
        delete inputLayer;
    }
private:
   
    vector<Matrix<value_node>*> hiddenLayer;
    Matrix<value_node>* inputLayer;
    vector<Matrix<parameter_node>*> weights;
    Matrix<value_node>* outputLayer;
   vector<parameter_node*> bias;
    int numberOfLayers;
    vector<Matrix<value_node>*> alpha;
    vector<Matrix<value_node>*> beta;
    
    vector<vector<double>> hiddenVals;
    
};


class maxPool: public layer{
public:
    maxPool(){
        
    }
    
    
private:
    vector<Matrix<value_node>*> hiddenLayer;
    Matrix<value_node>* inputLayer;
    vector<Matrix<parameter_node>*> weights;
    Matrix<value_node>* outputLayer;
    int numberOfLayers;
    
};

class convultion: public layer{
public:
    convultion(){
        
    }
    void initiateInput(Matrix<value_node>* v){
        input=v;
    }
    void initiateKernel(Matrix<parameter_node>* v){
        kernel=v;
    }
    void propogate() override{
        output=input->convolution(*kernel,*kernel);
    }
     
    Matrix<value_node>* returnOutput(){
        return output;
    }
    
private:
    Matrix<value_node>* input;
    Matrix<parameter_node>* kernel;
   Matrix<value_node>* output ;

    int numberOfLayers;
    
};


#endif /* layer_hpp */
