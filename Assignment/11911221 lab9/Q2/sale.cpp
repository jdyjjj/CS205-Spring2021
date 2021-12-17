#include <iostream>
#include <iomanip>
#include "sale.h"
#include <string>
#include <cstring>
using namespace std;
using namespace SALES;
//void setSales(Sales&s,const double ar[],int n){

//}
void SALES::setSales(Sales&s,const double ar[],int n){
  //s.sales=new double[n];
  double max_1=0;
  double min_1=100000;
  double sum=0;
  for(int i=0;i<n;i++){
      s.sales[i]=ar[i];
      sum+=ar[i];
      if(max_1<ar[i]){
          max_1=ar[i];
      }
      if(min_1>ar[i]){
          min_1=ar[i];
      }
  }
   s.min=min_1;
   s.max=max_1;
   s.average=sum/n;
}

void SALES::setSales(Sales&s) {
    cout << "Enter sales for 4 quarters: ";
    for(int i=0;i<4;i++){
        cin>>s.sales[i];
    }
    double max_1=0;
    double min_1=100000;
    double sum=0;
    for(int i=0;i<4;i++){
        sum+=s.sales[i];
      if(max_1<s.sales[i]){
          max_1=s.sales[i];
      }
      if(min_1>s.sales[i]){
          min_1=s.sales[i];
      }
  }
    s.max=max_1;
    s.min=min_1;
    s.average=sum/4;


}
 void SALES::showSales(const Sales& s){
     cout << "Sales: " ;
     for(int i=0;i<4;i++){
         if(s.sales[i]==0){
             break;
         }
         cout<<s.sales[i];
         cout<<" ";
     }
     cout<<endl;
     cout << "Averages: " <<s.average<<endl;
     cout << "Max: " <<s.max <<endl;
     cout << "Min: " <<s.min <<endl;
 }