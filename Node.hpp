//
//  Node.hpp
//  openCVtest
//
//  Created by Liyu Zerihun on 8/1/22.
//
#include <vector>
#include "Utilities.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "Network.hpp"
#include <string>


#ifndef Node_hpp
#define Node_hpp
#include <mutex>
#include <thread>

const double momentum=0.9;
using namespace std;
class Node{

    
public:
    std::mutex mut;

    Node(int index, bool is_Value, Network<Node>* n, bool dynamic){
        indexFuntion=index;
        is_collective_node=(!is_Value);// If it is a value then it will switch
        is_value_node=(is_Value);
        is_parameter=false;
        neuralNet=n;
        active=true;
        dynamicallyAllocated=dynamic;
        seen=false;
        derNumber=0;
        derivativeAtNode=0;
        forwardSeen=false;
        if(dynamic){
            
            n->push(this);
        }
        
        previousIncrement=0;
        previousNumber=0;
    }
    
    virtual void activate()=0;// The activation function shall be described in sub classes
    virtual void addInput(double num, Node* prev){// The add input function shall be described in the sub classes

        if(prev!=nullptr){
            previous.push_back(prev);
        }
        input.push_back(num);

    }
    virtual void addI(double num){// The add input function shall be described in the sub classes
        
        input.push_back(num);

        if(is_value_node==true){// if the value node is true tehn teh activated value is the same as teh is_value node
            //I put this here becuase teh intiali creation of an empty node will not have a input and so no activtaed value for propogation, so once it is a added to the input vector it will be passed to the activated value and so it is ready for propogation 
        setActivatedValue(num);
        }
        ;
    }

    virtual void addOutput(double num){// The add output function shall be described in the sub classes
        mut.lock();
        output.push_back(num);
        activated_value=num;
        mut.unlock();
    }

    void addPrev(Node* pointer){// The add input function shall be described in the sub classes
        
        mut.lock();
        previous.push_back(pointer);
        mut.unlock();

    }
    void addNext(Node* pointer){
        mut.lock();
        next.push_back(pointer);
        mut.unlock();
    }
      vector<Node*>* getNext(){
        return &next;
    }
      double getInput(int index){
        return input.at(index);
    }
      vector<double>* getInputVector(){
        return &input;
    }
     vector<double>* getIVector() const{
      return &input;
  }
       vector<double>* getOVector() const{
        return &output;
    }
    vector<double>* getOutputVector(){
      return &output;
  }
  void setInputVector(const vector<double> s){
        input=s;
    }
    void setOutputVector(const vector<double> s){
        output=s;
    }
    
      vector<Node*>* getPrevVector(){
        return &previous;
    }
     vector<Node*>* getNextVector(){
         
        return &next;
    }
    int getIndexValue() const{
        return indexFuntion;
    }
    void setIndex(int s){
        indexFuntion=s;
    }
    vector<Node*>* getPVector() const{
      return &previous;
  }
   vector<Node*>* getNVector() const{
      return &next;
  }
    void setPreviousVector(vector<Node*>& s){
        previous=s;
        
    }
    void setNextVector(vector<Node*>& s){
        next=s;
    }
    void setDerivativeVector(vector<double> s){
        derivative=s;
    }
 
   
    void printInfo( Node* p)const {
         if(p->is_parameter==true){
            cout<<"Type: parameter node"<<endl;
        }
        else if(p->is_value_node==true ){
            cout<<"Type: value node"<<endl;
        }
       
        else{
            cout<<"Type: collection node"<<endl;
        }
        cout<<"Index Value: "<<p->indexFuntion<<endl;
        cout<<"input: "<<endl;
        if(p->getIVector()->size()>0){
        for(int i=0; i<p->getIVector()->size(); i=i+1){
            
            cout<<p->getInput(i)<<endl;
            }
        }
        cout<<"output: ";

        for(int i=0; i<p->getOVector()->size(); i=i+1){
            cout<<p->getOutput(i)<<endl;
            
            }
        if(p->getOVector()->size()==0){
            cout<<endl;
        }
        cout<<"address: "<<p<<endl;
        cout<<"Previous: "<<endl;
        for(int i=0; i< p->getPVector()->size(); i=i+1){
            if(p->getPVector()->at(i)!=nullptr){
            cout<<p->getPVector()->at(i)<<endl;
            }
        }
        cout<<"Derivative: "<<endl;
        for(int i=0; i<p->getDerivative()->size(); i=i+1){
            
            cout<<p->getDerivative()->at(i)<<endl;
        }
        
        cout<<"Derivative At the node: "<<endl;
            
            cout<<p->getDerivativeAtNode()<<endl;
        
        cout<<"Next: "<<endl;
        for(int i=0; i<p->getNVector()->size(); i=i+1){
            if(p->getNVector()->at(i)!=nullptr){
            cout<<p->getNVector()->at(i)<<endl;
            }
        }
        cout<<endl;
    }
    void printInfoConst( Node* const p) const{
        
        cout<<"value: "<<input[0]<<endl;
        cout<<"address: "<<p<<endl;
        cout<<"Previos: "<<endl;
        for(int i=0; i<p->getPVector()->size(); i=i+1){
            if(p->getPVector()->at(i)!=nullptr){
            cout<<p->getPVector()->at(i)<<endl;
            }
        }
        
        cout<<"Next: "<<endl;
        for(int i=0; i<p->getNVector()->size(); i=i+1){
            if(p->getNVector()->at(i)!=nullptr){

            cout<<getNVector()->at(i)<<endl;
            }
        }
        cout<<endl;
    }
    
     const double getOutput(int index){
        return output.at(index);
    }
     int returnIndex(){
        return indexFuntion;
    }
    void print(Node* head){
        printInfo(head);

        
        if(head->getInputVector()->size()!=0){
        }

        for(int i=0; i<head->getNextVector()->size(); i++){

            if(head->getNextVector()->at(i)!=nullptr){
                print(head->getNextVector()->at(i));
            }

        }
    }
    
    void printPrev(Node* head){
        printInfo(head);

        
        if(head->getInputVector()->size()!=0){
        }

        for(int i=0; i<head->getPrevVector()->size(); i++){

            if(head->getPrevVector()->at(i)!=nullptr){
                printPrev(head->getPrevVector()->at(i));
            }

        }
    }
    
    void printCount(Node* head, int& x){
    if(head->is_parameter==true && !head->getSeen())
    {
        x++;
        head->setSeen();
    }
        if(head->getInputVector()->size()!=0){
        }

        for(int i=0; i<head->getPrevVector()->size(); i++){

            if(head->getPrevVector()->at(i)!=nullptr){
                printCount(head->getPrevVector()->at(i), x);
            }

        }
    }
    
        void setActivatedValue(double num){
            activated_value=num;
        }
        double getActivatedValue(){
            return activated_value;
        }
        double getAValue() const{
            return activated_value;
        }
        void operator>>(Node& right){
            this->addNext(&right);
            right.addPrev(this);
            if(right.is_collective_node==false){
            right.addDerivative(1);
            }
            
                
        }
    
    void operator|(Node& right){
        this->addNext(&right);
        right.addPrev(this);
        right.setInputVector(*this->getIVector());
    }
    
    void operator>>=(Node& right){
        this->addNext(&right);
        right.addPrev(this);
        this->propogate();
        if(this->is_collective_node && right.is_value_node){
            right.getDerivative()->push_back(1);
        }

    }
    void propogate(){
       vector<Node*>* nextVector= this->getNextVector();
        for(int i=0; i<nextVector->size(); i=i+1){
            if(nextVector->at(i)!=nullptr){
                if(is_value_node || is_parameter){
                    //This is here becuase during activation for collective node the value is already updated(output value),
                    //thus it only takes place if this node is a value node
                this->addOutput(this->activated_value);// Whenever a computation is made an output is added to the vector, note
                //that the output vector is very important for final calculations as it corresposnds to the derivative vector
                }
                nextVector->at(i)->addI(activated_value);
            }
        }
    }
    bool get_is_collective_node() const{
        return is_collective_node;
    }
    bool get_is_parameter() const{
        return is_parameter;
    }
     bool get_is_value_node() const{
        return is_value_node;
    }
    void setTrueParamter(){
        is_parameter=true;
    }
    void setActiveFalse() const{
        active=false;
    }
    bool getActive(){
        return active;
    }
    Network<Node>* getNetworkPointer() const {
        
        return neuralNet;
    }
    bool isDynamic() const{
        return dynamicallyAllocated;
    }
    void dynamicMemory(){
        dynamicallyAllocated=true;
    }
    void setSeen(){
        seen=true;
    }
    bool getSeen(){
        return seen;
    }
    
    void addDerNuber(){
        derNumber=derNumber+1;
    }
    int getDerNumber(){
        return derNumber;
    }
    
    void setDerivativeAtNode(double d){
        derivativeAtNode=d;
    }
    double getDerivativeAtNode(){
        return derivativeAtNode;
    }
    virtual ~Node(){
        
    }
    
    void updateNode(Node* p, double learningParam){
        
        if(p->is_parameter==true){
            p->getInputVector()->at(0)=p->getInputVector()->at(0) - (double)p->getDerivativeAtNode()*(learningRate);
            
        }
        for(int i=0; i<p->getPrevVector()->size(); i=i+1){
            updateNode(p->getPVector()->at(i),learningParam);
            
        }
        
       
    }
    void update(bool time){
        if(time){

            this->previousDerivatives.push_back((double)this->getDerivativeAtNode());

            double sum=0;
            
            for(int i=0; i<this->previousDerivatives.size(); i++){
                sum=this->previousDerivatives.at(i)+sum;
            }
            
             double average= sum/this->previousDerivatives.size();
           
           //double newWeight=this->getInputVector()->at(0) - ((double)average*(learningRate) + momentum*previousIncrement);

            double newWeight=this->getInputVector()->at(0) - ((double)average*(learningRate) );
            

          
//            if(newWeight>100){
//                cout<<newWeight<<endl;
//
//                //newWeight=-this->getInputVector()->at(0);
//                newWeight=uniformRand(-5, 5, 1000);
//            }
//            else if(newWeight<-100){
//                cout<<newWeight<<endl;
//                newWeight=uniformRand(-5, 5, 1000);
//                //newWeight=-this->getInputVector()->at(0);
//            }
            this->getInputVector()->at(0)=newWeight;
            previousIncrement=(average*(learningRate) + momentum*previousIncrement);
            this->previousDerivatives.clear();
            
        }
        else{
            this->previousDerivatives.push_back((double)this->getDerivativeAtNode());
        }
            
            
        
        
       
    }
    void backProp(Node*p , double der, Node* target, int& count, vector<Node*>& endNodes){

        if(p->is_parameter==true){
            if(p->getSeen()){
            }
            else{
                count++;
                p->setSeen();
                endNodes.push_back(p);

            }
                p->setDerivativeAtNode((double)p->getDerivativeAtNode()+der);
        }
        
        
        
        else{
            p->addDerNuber();

            if(p->getSeen()){// if it hasn't been and has not prev vector add
              

            }
            else if(p->getPrevVector()->size()==0){
                endNodes.push_back(p);
                p->setSeen();
            }
            
            
            
            if(p->getDerNumber()>=p->getNextVector()->size()){
                
               

                        double val=0;
                    

                
                    if(p->getNextVector()->size()==0){
                        val=1;
                    }
                    else{
                        
                        if(p->getDerNumber()==p->getNextVector()->size()){
                            p->setDerivativeAtNode(der+p->getDerivativeAtNode());                            val=p->getDerivativeAtNode();
                        }
                    }
                for(int i=0; i<p->getPrevVector()->size(); i=i+1){
                    
                    double backPropval=val*p->getDerivative()->at(i);
//                    if(backPropval>1){
//                        backPropval=0.9;
//                    }
//                    else if(backPropval<-1){
//                        backPropval=-0.9;
//                    }
//
                        backProp( p->getPrevVector()->at(i), backPropval, target, count, endNodes);
                    
                        }
                
                    }
            else{
                p->setDerivativeAtNode(der+p->getDerivativeAtNode());

            }
            
            
        }
        
    }
    
    int getForwardNumber(){
        return forwardNumber;
    }
    
    int getPreviousNumber(){
        return previousNumber;
    }
    void setprevNumber(int num){
        previousNumber=num;
    }

    
    
    virtual void specialActivation()=0;
    void addForwardNumber(){
        forwardNumber=forwardNumber+1;
    }
    vector<double>* getDerivative() const{
       
        return &derivative;
    
    }
    void forSeen(){
        forwardSeen=true;
    }
    bool hasBeenSeen(){
        return forwardSeen;
    }
   
    void addDerivative(double d) const{
        derivative.push_back(d);
    }
    void zero(){
         output.clear();//ouputed function
         indexFuntion;//Index function for array of functions in utility
        derivative.clear();
        previous.clear();
        next.clear();
          active;
          dynamicallyAllocated;
          seen=false;//Test variable;
          derNumber=0;
          derivativeAtNode=0;
        forwardNumber=0;
         string specialName;
    }
private:
    
   mutable vector<double> input;// input of the node
    mutable double activated_value;
    mutable vector<double> output;//ouputed function
    int indexFuntion;//Index function for array of functions in utility
    mutable vector<Node*> previous;
    mutable vector<Node*> next;
    bool is_value_node;
    bool is_collective_node;
    bool is_parameter;
    mutable vector<double> derivative;
    Network<Node>* neuralNet;
    mutable bool active;
    bool dynamicallyAllocated;
    bool seen;//Test variable;
    int derNumber=0;
    double derivativeAtNode;
    mutable vector<double> previousDerivatives;
    string specialName;
    double previousIncrement;
    bool forwardSeen;
    int forwardNumber;
        int previousNumber;
    
};

class collection_node: public Node{
public:
   collection_node(int index, Network<Node>* n, bool dynamic)
    :Node(index, false, n, dynamic)
    {

    }
    
    collection_node(Network<Node>* n, bool dynamic)
    :Node(0,false,n, dynamic)
    {

    }
    
   

    collection_node( collection_node const& right)
    :Node(0,false, right.getNetworkPointer(), right.isDynamic())
        {
            right.setActiveFalse();

            this->setInputVector(*right.getIVector());
            this->setOutputVector(*right.getOVector());
            this->setNextVector(*right.getNVector());
            this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
            this->setIndex(right.getIndexValue());
            this->setDerivativeVector(*right.getDerivative());
            for(int i=0; i< right.getPVector()->size(); i++){

                if(right.getPVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                        if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                    right.getPVector()->at(i)->getNVector()->at(m)=this;
                }
                    }
                }

            }
                
                for(int i=0; i< right.getNVector()->size(); i++){

                    if(right.getNVector()->at(i)!=nullptr){
                        for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                        if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                            right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                        }
                    }
                    }

                }
        }

    collection_node& operator=(collection_node &right){
        right.setActiveFalse();
        this->setInputVector(*right.getIVector());
        this->setOutputVector(*right.getOVector());
        this->setNextVector(*right.getNVector());
        this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
        this->setIndex(right.getIndexValue());
        this->setDerivativeVector(*right.getDerivative());

        for(int i=0; i< right.getPVector()->size(); i++){

            if(right.getPVector()->at(i)!=nullptr){
                for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                    if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                right.getPVector()->at(i)->getNVector()->at(m)=this;
            }
                }
            }

        }
            
            for(int i=0; i< right.getNVector()->size(); i++){

                if(right.getNVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                    if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                        right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                    }
                }
                }

            }
//            cout<<" Being converted to: "<<endl;
//            this->printInfo(this);
       return *this;
    }
    

    void activate() override{
        collectiveFunc[getIndexValue()](getInputVector(),getOutputVector());
        setActivatedValue(getOutput(0));
        propogate();
        for(int i=0; i<getPrevVector()->size(); i++){
            double temp;
            getDerivative()->push_back(temp);
           
            derivativeFunc[getIndexValue()](getDerivative()->at(i), getOutput(0),getPrevVector()->at(i)->getOutput(0), getInputVector()->size(), *getIVector());
            
        }
    }
    void specialActivation(){
        collectiveFunc[getIndexValue()](getInputVector(),getOutputVector());
        setActivatedValue(getOutput(0));
        
        for(int i=0; i<getPrevVector()->size(); i++){
            double temp;
            getDerivative()->push_back(temp);
            derivativeFunc[getIndexValue()](getDerivative()->at(i), getOutput(0),getPrevVector()->at(i)->getOutput(0), getInputVector()->size(), *getIVector());
            
        }
    }
  
private:
    bool  noActivation=false;
    
    
    
    
};


class value_node: public Node{
public:
    value_node(double value, Node* prev, Network<Node>* n, bool dynamic)
    :Node(0,true, n, dynamic)
    {
    addInput(value, prev);
        setActivatedValue(value);

    }
    value_node(bool val, Network<Node>* n, bool dynamic)
    :Node(0,true, n, dynamic){
        

    }


    value_node(Network<Node>* n, bool dynamic)
    :Node(0,true, n, dynamic)
    {

    }
   
    
    value_node(  const value_node &right)
    :Node(0,true, right.getNetworkPointer(), right.isDynamic())
        {
            right.setActiveFalse();
        this->setInputVector(*right.getIVector());
        this->setOutputVector(*right.getOVector());
        this->setNextVector(*right.getNVector());
        this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
            this->setDerivativeVector(*right.getDerivative());

        for(int i=0; i< right.getPVector()->size(); i++){

            if(right.getPVector()->at(i)!=nullptr){
                for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                    if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                right.getPVector()->at(i)->getNVector()->at(m)=this;
            }
                }
            }

        }
            
            for(int i=0; i< right.getNVector()->size(); i++){

                if(right.getNVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                    if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                        right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                    }
                }
                }

            }
//            cout<<" Being converted to: "<<endl;
//            this->printInfo(this);

            

        }

    
    
//    value_node operator=(value_node& right){
//        this->addNext(&right);
//        right.addPrev(this);
//
//        return *this;
   // }
    
    value_node& operator=(const value_node &right){
        right.setActiveFalse();

        this->setInputVector(*right.getIVector());
        this->setOutputVector(*right.getOVector());
        this->setNextVector(*right.getNVector());
        this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
        this->setDerivativeVector(*right.getDerivative());

        for(int i=0; i< right.getPVector()->size(); i++){

            if(right.getPVector()->at(i)!=nullptr){
                for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                    if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                right.getPVector()->at(i)->getNVector()->at(m)=this;
            }
                }
            }

        }
            
            for(int i=0; i< right.getNVector()->size(); i++){

                if(right.getNVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                    if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                        right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                    }
                }
                }

            }
//            cout<<" Being converted to: "<<endl;
//            this->printInfo(this);
       return *this;
    }

    value_node& operator+(value_node &right){
       // cout<<this<<" "<<&right<<endl<<endl;
//        collection_node* c= new collection_node(0,this->getNetworkPointer(), true);
//        *this>>=*c;
//        right>>=*c;
//        value_node* sum_pointer= new value_node (this->getNetworkPointer(), true);
//        *c>>*sum_pointer;
//        c->activate();
        

       value_node* sum_pointer= new value_node (this->getInput(0)+right.getInput(0),&right, right.getNetworkPointer(), true);
        sum_pointer->addPrev(this);

        this->addNext(sum_pointer);
        right.addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        right.addOutput(right.getInput(0));
        sum_pointer->getDerivative()->push_back(1);
        sum_pointer->getDerivative()->push_back(1);

        return *sum_pointer;
    }
//    value_node& operator+(double right){
//       // cout<<this<<" "<<&right<<endl<<endl;
//
//
//       value_node* sum_pointer= new value_node (this->getInput(0)+right,this, this->getNetworkPointer(), true);
//        this->addNext(sum_pointer);
//        this->addOutput(this->getInput(0));
//        sum_pointer->getDerivative()->push_back(1);
//
//        return *sum_pointer;
//    }
    
    
    value_node& operator&(double right){
    
        

        value_node* sum_pointer= new value_node (pow(exp(1),this->getInput(0)),this, this->getNetworkPointer(), true);
        this->addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        sum_pointer->getDerivative()->push_back(pow(exp(1),this->getInput(0)));
        return *sum_pointer;
    }
                                        
    value_node& operator%(double right){
        value_node* sum_pointer= new value_node (log(this->getInput(0)),this, this->getNetworkPointer(), true);
        
        this->addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        sum_pointer->getDerivative()->push_back((double)1/this->getInput(0));
        return *sum_pointer;
        
    }
    
    value_node& operator-(value_node &right){
       // cout<<this<<" "<<&right<<endl<<endl;
//        collection_node* c= new collection_node(4,this->getNetworkPointer(), true);
//        *this>>=*c;
//        right>>=*c;
//        value_node* sum_pointer= new value_node (this->getNetworkPointer(), true);
//        *c>>*sum_pointer;
//        c->activate();
        value_node* sum_pointer= new value_node (this->getInput(0)-right.getInput(0),&right, right.getNetworkPointer(), true);
        sum_pointer->addPrev(this);
        this->addNext(sum_pointer);
        right.addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        right.addOutput(right.getInput(0));
        sum_pointer->getDerivative()->push_back(-1);
        sum_pointer->getDerivative()->push_back(1);

        return *sum_pointer;
    }
    
    
    value_node& operator/(value_node &right){
        value_node* sum_pointer= new value_node (this->getInput(0)/right.getInput(0),&right, right.getNetworkPointer(), true);
         sum_pointer->addPrev(this);

         this->addNext(sum_pointer);
         right.addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        right.addOutput(right.getInput(0));
        sum_pointer->getDerivative()->push_back(-1*this->getInput(0)*((double)1/pow(right.getInput(0),2)));
        sum_pointer->getDerivative()->push_back((double)1/right.getInput(0));
        
         return *sum_pointer;
        
    }
    value_node& operator*(value_node& right){
        

        value_node* sum_pointer= new value_node (this->getInput(0)*right.getInput(0),this, right.getNetworkPointer(), true);
        sum_pointer->addPrev(&right);
         this->addNext(sum_pointer);
        right.addNext(sum_pointer);

        this->addOutput(this->getInput(0));
        right.addOutput(right.getInput(0));
        sum_pointer->addDerivative(right.getInput(0));
        sum_pointer->addDerivative(this->getInput(0));
        
        
         return *sum_pointer;
       
    }
    
    
//    value_node& operator*(double right){
//
//
//        value_node* sum_pointer= new value_node (this->getInput(0)*right,this, this->getNetworkPointer(), true);
//
//         this->addNext(sum_pointer);
//        this->addOutput(this->getInput(0));
//        sum_pointer->getDerivative()->push_back(right);
//
//
//         return *sum_pointer;
//
//    }
    
    
    value_node& operator^(double right){
        value_node* sum_pointer= new value_node ((double)pow(this->getInput(0),right),this, this->getNetworkPointer(), true);

         this->addNext(sum_pointer);
        this->addOutput(this->getInput(0));
        sum_pointer->getDerivative()->push_back((double)(right)*pow(this->getInput(0),right-1));
         return *sum_pointer;
        
    }
    
   

    void activate(){
        
        setActivatedValue(getInput(0));
        propogate();

    }
    
    void specialActivation(){
        setActivatedValue(getInput(0));
        
    }
    
};


class parameter_node: public value_node{
public:
    parameter_node(double value, Node* prev, Network<Node>* n, bool dynamic)
    :value_node(n, dynamic)
    {
    addInput(value, prev);
        setActivatedValue(value);
        setTrueParamter();


    }
    parameter_node(Network<Node>* n, bool dynamic)
    : value_node(true, n, dynamic)
    {

        setTrueParamter();

    }
   
    
    parameter_node(  const parameter_node &right)
    : value_node(right.getNetworkPointer(), right.isDynamic())
        {
            right.setActiveFalse();

            setTrueParamter();
        this->setInputVector(*right.getIVector());
        this->setOutputVector(*right.getOVector());
        this->setNextVector(*right.getNVector());
        this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
            this->setDerivativeVector(*right.getDerivative());

        for(int i=0; i< right.getPVector()->size(); i++){

            if(right.getPVector()->at(i)!=nullptr){
                for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                    if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                right.getPVector()->at(i)->getNVector()->at(m)=this;
            }
                }
            }

        }
            
            for(int i=0; i< right.getNVector()->size(); i++){

                if(right.getNVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                    if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                        right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                    }
                }
                }

            }
//            cout<<" Being converted to: "<<endl;
//            this->printInfo(this);




        }

    
    
//    value_node operator=(value_node& right){
//        this->addNext(&right);
//        right.addPrev(this);
//
//        return *this;
   // }
    
    parameter_node& operator=(parameter_node &right){
        setTrueParamter();
        right.setActiveFalse();

        this->setInputVector(*right.getIVector());
        this->setOutputVector(*right.getOVector());
        this->setNextVector(*right.getNVector());
        this->setPreviousVector(*right.getPVector());
            this->setActivatedValue(right.getAValue());
        this->setDerivativeVector(*right.getDerivative());

        for(int i=0; i< right.getPVector()->size(); i++){

            if(right.getPVector()->at(i)!=nullptr){
                for(int m=0; m<right.getPVector()->at(i)->getNextVector()->size(); m=m+1){
                    if(right.getPVector()->at(i)->getNVector()->at(m)==&right){

                right.getPVector()->at(i)->getNVector()->at(m)=this;
            }
                }
            }

        }
            
            for(int i=0; i< right.getNVector()->size(); i++){

                if(right.getNVector()->at(i)!=nullptr){
                    for(int m=0; m<right.getNVector()->at(i)->getPVector()->size(); m=m+1){
                    if(right.getNVector()->at(i)->getPrevVector()->at(m)==&right){
                        right.getNVector()->at(i)->getPrevVector()->at(m)=this;
                    }
                }
                }

            }
//            cout<<" Being converted to: "<<endl;
//            this->printInfo(this);
       return *this;
    }

  
   

    void activate(){
        
        setActivatedValue(getInput(0));
        propogate();

    }
    
};


static void forwardProp(Node* p, Node* prev ,double val, int& count){
    
    
    if(p->get_is_parameter()){
        count++;
    }
    if(p->hasBeenSeen()){
        
    }
    
    else{
        p->setprevNumber(p->getPrevVector()->size());
        p->zero();
        p->forSeen();
        
    }
        
        
    if(prev!=nullptr){
    p->addForwardNumber();
    }

    p->addInput(val, prev);
    if(p->getForwardNumber()==p->getPreviousNumber()){
       
        p->specialActivation();
        p->addOutput(p->getActivatedValue());

    for(int i=0; i<p->getNext()->size(); i++){
        
        forwardProp(p->getNextVector()->at(i), p, p->getActivatedValue(),count);
        }
        
    }
}



#endif /* Node_hpp */
