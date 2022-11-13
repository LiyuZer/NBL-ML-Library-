//
//  main.cpp
//  openCVtest
//
//  Created by Liyu Zerihun on 5/3/22.
//
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdint.h>
#include "Node.hpp"
#include "layer.hpp"
#include "Matrix.hpp"
#include "MatrixCleaner.hpp"
#include "Utilities.hpp"
#include <cstdlib>
#include "ImageProcessor.hpp"
#include <math.h>
#include <chrono>

#include <filesystem>

#include <vector>
using std::filesystem::directory_iterator;

using  std::cout, std:: cin;
using  std::vector;
using namespace std;
using namespace std::chrono;
#include <iostream>
double learningRate;

double numConnection(int array[], int size){
    double sum=1;
    for(int i=0; i<size; i++){
        sum=sum*array[i];
    }
    return sum;
}

void iterate(int start, int end, vector<Node*> v, int& count){
    for(int i=start; i<end; i++){
        forwardProp(v.at(i), nullptr, v.at(i)->getInput(0),count);
    }
}

void zeroParamters(fullyConnected& c){
    
    for(int i=0; i<c.getWeightMatrix().size(); i++){
        c.getWeightMatrix().at(i)->clearMatrix();
    }
    for(int i=0; i< c.getBias().size(); i++){
        c.getBias().at(i)->zero();
    }
   
}
int main(int argc, const char * argv[]) {
    
    
    vector<vector<string>> files;
     
    

    
    for(int i=0; i<10; i++){
        string file = "/Users/liyuzerihun/Documents/openCVtest/openCVtest/sets/"+to_string(i);

        vector <string> s;
        files.push_back(s);
        int count=0;
        for (const auto & file : directory_iterator(file)){
            if(count==0){
                
            }
            else{
                files.at(i).push_back(file.path());

            }
            count++;
        }
    }
        

     
     
    
     learningRate=0.001;
     
     Network<Node>* main= new Network<Node>();
     //Matrix<value_node> t("(100*100*3)",main, false);
//
 //   Matrix<parameter_node> preBias("(1*1*1)",main,  false);
//     Matrix<parameter_node> param("(1*1*1)",main,  false);
//
       //  Matrix<parameter_node> firstbranchBias("(1*1*1)",main,  false);
         //Matrix<parameter_node> firstBranch("(3*3*1)",main,  false);
//             Matrix<parameter_node> firstbranchBias1("(1*1*1)",main,  false);
//             Matrix<parameter_node> firstBranch1("(1*1*1)",main,  false);
//                         Matrix<parameter_node> firstbranchBias2("(1*1*1)",main,  false);
//                         Matrix<parameter_node> firstBranch2("(3*3*1)",main,  false);
//                             Matrix<parameter_node> firstbranchBias3("(1*1*1)",main,  false);
//                             Matrix<parameter_node> firstBranch3("(1*1*1)",main,  false);
//
//     Matrix<parameter_node> secondbranchBias("(1*1*40)",main,  false);
//     Matrix<parameter_node> secondBranch("(3*3*40)",main,  false);
//         Matrix<parameter_node> secondbranchBias1("(1*1*1)",main,  false);
//         Matrix<parameter_node> secondBranch1("(1*1*1)",main,  false);
//                 Matrix<parameter_node> secondbranchBias2("(1*1*1)",main,  false);
//                 Matrix<parameter_node> secondBranch2("(7*7*1)",main,  false);
                    

     vector<Matrix<parameter_node>*> weights;
     
     vector<parameter_node*> bias;
     
     
      int dimensions[5]={784,16,16,10};
      
      
      for(int x=0; x<3; x++){
          int array[1]= {dimensions[x+1]};
                      parameter_node* v= new parameter_node(uniformRand(0, 0.01, 1000),nullptr, main, false);
          bias.push_back(v);

      }
     
     
     for(int x=0; x<3; x++){
         int dim[2]={dimensions[x+1],dimensions[x]};
         Matrix<parameter_node>* weightMatrix= new Matrix<parameter_node>(dim,2, main, false);

         for(int i=0; i<dimensions[x+1]; i++){
                 for(int m=0; m<dimensions[x]; m++){
                     int array[2]={i,m};
                     parameter_node* v= new parameter_node(uniformRand(-0.3, 0.3, 1000),nullptr, main, false);
                     weightMatrix->setA(array,2,*v);
                 }
             }

         weights.push_back(weightMatrix);

     }
     
     
     
     
     

//     param.randomize();
//     preBias.randomize();
//     firstBranch.randomize();
//     firstBranch1.randomize();
//     firstBranch2.randomize();
//     firstBranch3.randomize();
//
//
//
//     firstbranchBias.randomize();
//     firstbranchBias1.randomize();
//     firstbranchBias2.randomize();
//     firstbranchBias3.randomize();




    


     string s="";
     int count=0;
     double accuracy=0;
     double branch=0;
     double previousAver = 0.0;
     double prevAver=0;
     double averageSum=0;
    double errorAverage=0;
     for(int i=0; i<10000; i++){
         if(s!="q"){
         if(count>=100){
             count=0;
             accuracy=0;
             prevAver=0;
             averageSum=0;
             previousAver=0;
             errorAverage=0;
         }

        int seed= uniformTest(0, 9, 1);
          // int seed=5;
         string animal;
         double cat;
         double dog;
         if(seed==0){
             animal="0";
             cat=1;
             dog=0;
         }
         else if (seed==1){
             animal="1";
             cat=0;
             dog=1;

         }
         else if (seed==2){
             animal="2";
             cat=0;
             dog=1;

         }
         else if (seed==3){
             animal="3";
             cat=0;
             dog=1;

         }
         else if (seed==4){
             animal="4";
             cat=0;
             dog=1;

         }
         else if (seed==5){
             animal="5";
             cat=0;
             dog=1;

         }
         else if (seed==6){
             animal="6";
             cat=0;
             dog=1;

         }
         else if (seed==7){
             animal="7";
             cat=0;
             dog=1;

         }
         else if (seed==8){
             animal="8";
             cat=0;
             dog=1;

         }
         else if (seed==9){
             animal="9";
             cat=0;
             dog=1;

         }
            
             string num=animal;
             int l=stoi(num);
             
             
             
            
                 
            
             
             
         Matrix<value_node>* ptr;
             
        //  string path=files.at(l).at(5);
            string path=files.at(l).at((uniformTest(0, files.at(l).size()-1, 1)));
             
             
         ImageProcessor img(path);
             
            

             ptr=&img.normalizePictureGrey(main);



       


             
 //
 //            else if(i==40){
 //                learningRate=learningRate*1.2;
 //            }
 //
 //            else if(i==80){
 //                learningRate=learningRate*2;
 //            }
 //            else if(i==150){
 //                learningRate=learningRate*3;
 //
 //            }
             

    // Matrix<value_node>* p1= ptr->convolution(param, preBias);
 
 //        value_node averageSplitter(main,false);
 //        collection_node preAverage(3,main,false);
 //        p1->connectNodeWithChannel(preAverage, 0);
 //        preAverage>>averageSplitter;
 //        preAverage.activate();
 //
 //        averageSum=abs(averageSplitter.getInput(0))+averageSum;
 //            prevAver=(averageSum)/(double(count));
 //        previousAver=prevAver-previousAver;
 //        double division=abs(previousAver/10);
 //
 //
 //            if((prevAver-(division))>abs(averageSplitter.getInput(0))){
 //
 //            branch=0;
 //
 //        }
 //
 //
 //        else if(prevAver<=abs(averageSplitter.getInput(0))){
 //            branch=1;
 //        }

             branch=0;
  
//
//         if(branch==0){
//             p2= p1->convolution(firstBranch, firstbranchBias);
//             p3= p2->convolution(firstBranch1, firstbranchBias1);
//             p4= p3->convolution(firstBranch2, firstbranchBias2);
//             p5=p4->convolution(firstBranch3, firstbranchBias3);
//
//
//         }
//
//         else if(branch==1){
//             cout<<"2nd Branch"<<endl;
//
//             p2= p1->convolution(secondBranch, secondbranchBias);
//             p3= p2->convolution(secondBranch1, secondbranchBias1);
//             p4= p3->convolution(secondBranch2, secondbranchBias2);
//
//
//         }
         



        // cout<<"Average: "<<prevAver<<endl;
         //cout<<"Division: "<<division<<endl;

             fullyConnected layer(dimensions,4, main);
             
             layer.initiateBias(bias);
             layer.initiateWeight(weights);
             layer.initiateInput(*ptr);
             layer.propogate();
             


     
             
//
//             value_node* denominator=    &(((layer.getMatrixOutput()->getHeaders()->at(0)&5)+(layer.getMatrixOutput()->getHeaders()->at(1)&5)+(layer.getMatrixOutput()->getHeaders()->at(2)&5)+(layer.getMatrixOutput()->getHeaders()->at(3)&5)+(layer.getMatrixOutput()->getHeaders()->at(4)&5)+(layer.getMatrixOutput()->getHeaders()->at(5)&5)+(layer.getMatrixOutput()->getHeaders()->at(6)&5)+(layer.getMatrixOutput()->getHeaders()->at(7)&5)+(layer.getMatrixOutput()->getHeaders()->at(8)&5)+(layer.getMatrixOutput()->getHeaders()->at(9)&5)));
//
//
//             value_node* numerator;
//
//
//
//             value_node negate(-1,nullptr, main, false);
//             value_node error2(nullptr, main, false);
//
//             value_node* softMax;
//
// //            value_node* softMax1=&((*numerator1)/(*denominator));
// //            value_node* softMax2=&((*numerator2)/(*denominator));
//
//
//             double errors[9];
//
//
//
//                 numerator=&(layer.getMatrixOutput()->getHeaders()->at(stoi(num))&5);
//                 softMax=&((*numerator)/(*denominator));
//                 error2=(((*softMax)%5)*negate);
//
//
//             for(int i=0; i<10; i++){
//
//                 double x= (exp(layer.getMatrixOutput()->getHeaders()->at(i).getInput(0)))/denominator->getInput(0);
//                 errors[i]=x;
//             }
//
             
             
             
             
             double errors[9];
             value_node error2(nullptr, main, false);
             collection_node add(0,main,false);
             int optim;
             int power;
             for(int x=0; x<10; x++){
                 
                

                 if(x==l){
                     optim=1;
                     power=2;
                 }
                 else{
                     optim=0;
                     power=2;
                 }
                 value_node* optimal= new value_node((double)(optim), nullptr, main, true);
                 value_node* two= new value_node((int)2, nullptr, main, true);

                
                 value_node* pointer=&((((*optimal)-layer.getMatrixOutput()->getHeaders()->at(x))^power));
                 (*pointer)>>=add;
                 
                 errors[x]=layer.getMatrixOutput()->getHeaders()->at(x).getInput(0);
             }
             
             add>>error2;
             add.activate();
             
           
             
             
             
             
 //        value_node optimal(cat,nullptr, main, false);
 //        value_node vol(2,nullptr, main, false);
 //        value_node error(nullptr, main, false);
 //        error=((optimal-layer.getMatrixOutput()->getHeaders()->at(0))^2)/vol;
 //
 //        value_node optimal1(dog,nullptr, main, false);
 //        value_node vol1(2,nullptr, main, false);
 //        value_node error1(2,nullptr, main, false);
 //        error1=((optimal1-layer.getMatrixOutput()->getHeaders()->at(1))^2)/vol1;
 //
 //        value_node vol2(2,nullptr, main, false);
 //
 //        error2=(error+error1);

             
            
           

             double largesVal=errors[0];
             int largestIndex=0;
             for(int c=0; c<10; c++ ){

                 if(errors[c]>largesVal){
                     largesVal=errors[c];
                     largestIndex=c;
                 }
             }
            
            
             
             if(largestIndex==stoi(num)){
                 accuracy++;

             }
                                         
            
            
             
             bool timeForUpdate=false;
             if(count%15==0 && i!=0){
                 timeForUpdate=true;
             }

             vector<Node*> one;
             int paramCount=0;
             error2.backProp(&error2, 1, &error2, paramCount, one);
             layer.update(timeForUpdate);
             
       
//         if(branch==0){
//             param.update(timeForUpdate);
//             preBias.update(timeForUpdate);
//             firstBranch.update(timeForUpdate);
//             firstBranch1.update(timeForUpdate);
//             firstBranch2.update(timeForUpdate);
//             firstBranch3.update(timeForUpdate);
//
//
//             firstbranchBias.update(timeForUpdate);
//             firstbranchBias1.update(timeForUpdate);
//             firstbranchBias2.update(timeForUpdate);
//             firstbranchBias3.update(timeForUpdate);
//
//             param.clearMatrix();
//             preBias.clearMatrix();
//             firstBranch.clearMatrix();
//             firstBranch1.clearMatrix();
//             firstBranch2.clearMatrix();
//             firstBranch3.clearMatrix();
//
//             firstbranchBias.clearMatrix();
//             firstbranchBias1.clearMatrix();
//             firstbranchBias2.clearMatrix();
//             firstbranchBias3.clearMatrix();
//
//
//         }

//             if(i==300){
//                 learningRate=learningRate*10;
//             }
             
         

             




 //            if(uniformTest(1, 35, 1)==17){//Dropout
 //                weights.at(uniformTest(0, 1, 1))->getHeaders()->at(uniformTest(0, 100, 1)).getIVector()->at(0)=0;
 //            }
             

            

             if(count%99==0 && count!=0){
             cout<<"Round: "<<i<<endl;
             cout<<animal<<": "<<seed<<endl;
             cout<<"ERROR of: "<<num<<": "<<errors[stoi(num)]<<endl;
                 for(int i=0; i<10; i++){
                     cout<<errors[i]<<" ";
                 }
                 cout<<endl;
             cout<<"ERROR error: "<<error2.getInput(0)<<endl;
             cout<<"I am the mighty number: "<<largestIndex<<endl;
             cout<<"I am actually the mighty number ;) "<<stoi(num)<<endl;
         cout<<"Accruacy: "<<((accuracy/count)*(double)100)<<"%"<<endl;
                 cout<<"Number Of Parameters: "<<paramCount<<endl;
                 cout<<"The learning rate is "<<learningRate<<endl;
                 cout<<"The error average is "<<errorAverage/count<<endl;
             cout<<"------------------------------------------------------------------------"<<endl;
             cout<<"------------------------------------------------------------------------"<<endl;
                // img.show(*ptr);
             }
             delete ptr;

//         delete p1;
//         delete p2;
//         delete p3;
//         delete p4;
             zeroParamters(layer);

        

         //    t1.join();

         main->clear();
             count++;
             errorAverage=error2.getInput(0)+errorAverage;
         }
    
         

     }
}
