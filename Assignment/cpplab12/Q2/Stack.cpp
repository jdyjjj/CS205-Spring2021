#include "stack.h"
#include<iostream>
Stack::Stack(int n)
{
	pitems = new Item[n];
	size = n;
	top=0;
}
Stack::Stack(const Stack &st)
{
	pitems = new Item [st.size];
	top = st.top;
	for(int i =0;i<top;i++)
		pitems[i]=st.pitems[i];
	size = st.size;
}
Stack::~Stack()
{
	delete [] pitems;
	pitems=0;
}
 bool Stack::isempty() const
{
	return top==0;
}
 bool Stack::isfull() const
 {
	 return top==size;
 }
 bool Stack::push(const Item & item)
 {
	 if(isfull())
		 return false;
	 pitems[top++]=item;
	 return true;
 }
 bool Stack::pop(Item & item)
 {
	 if(isempty())
		 return false;
	 item =pitems[top--];
	 return true;
 }
 Stack &Stack::operator = (const Stack & st)
 {
	 delete [] pitems;
	 pitems = new Item[st.size];
	 top=st.top;
	 for(int i=0;i<top;i++)
		 pitems[i]=st.pitems[i];
	 size=st.size;
	 return *this;
 }
std::ostream & operator << (std::ostream &os ,const Stack &st){
	 for(int i=0;i<st.top;i++)
	 {
		 os << st.pitems[i] << " " ;
	 }
	 os << std::endl;
	 return os;
 }
