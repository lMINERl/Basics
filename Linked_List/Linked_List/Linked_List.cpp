// Linked_List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdint.h>			//for int_fast32_t

struct LL_Node sealed{		//liniked list Node
	int_fast32_t _val;
	LL_Node* _nptr;
	LL_Node(){
		_val=0;
		_nptr=NULL;
	}
};
struct LL_InitNode sealed{		// Linked List initial Node
	uint_fast32_t _length;		//contains the Length of linked list
	int_fast32_t _maxval;
	LL_Node* _headPtr;
	LL_Node* _tailPtr;
	LL_InitNode(){
		_length=0;
		_maxval=INT32_MIN;
		_headPtr=NULL;
		_tailPtr=NULL;
	}
};

LL_InitNode& fn_InitializeLL(); // initalize Linked List
void fn_InsertLinkedList(int_fast32_t val,uint_fast32_t pos,LL_InitNode &startPTR); //insert in linked list
void fn_EditLinkedList(uint_fast32_t pos,int_fast32_t val,LL_InitNode &startPTR);	//edit
void fn_PushBack(int_fast32_t val, LL_InitNode &startPTR);							// add last
void fn_Display(LL_InitNode & startPTR);											//display all


int _tmain(int argc, _TCHAR* argv[]){

	LL_InitNode & startPtr = fn_InitializeLL();
	fn_InsertLinkedList(9,startPtr._length,startPtr); // add last
	fn_InsertLinkedList(5,1,startPtr);				//add first
	fn_InsertLinkedList(4,1,startPtr);
	fn_InsertLinkedList(3,2,startPtr);				//add pos
	fn_InsertLinkedList(2,2,startPtr);
	fn_PushBack(10,startPtr);
	fn_PushBack(11,startPtr);
	fn_Display(startPtr);					// display			

	fn_EditLinkedList(3,10,startPtr);	//edit at 4th pos 10

	fn_Display(startPtr);

	return 0;
}
LL_InitNode& fn_InitializeLL(){
	LL_InitNode *NewNode =new LL_InitNode;
	NewNode-> _length=0; // this val will indicate the length of all list
	NewNode->_headPtr=NULL;
	NewNode->_tailPtr=NULL;
	return *NewNode;
}
void fn_InsertLinkedList(int_fast32_t val,uint_fast32_t pos,LL_InitNode &startPTR){
	LL_Node* t1 = startPTR._headPtr;
	LL_Node *NewNode = new LL_Node;
	NewNode->_val=val;
	if(!pos){							//insert at First Pos if Pos==0
		if(!startPTR._length){			//if its the 1st element in array assign tail pointer to it
			startPTR._tailPtr=NewNode;
		}
		NewNode->_nptr=t1;
		startPTR._headPtr=NewNode;
		startPTR._length++;
		if(startPTR._maxval<val)
			startPTR._maxval=val;

	}else if(pos==startPTR._length){			//insert at last Pos
		NewNode->_nptr=NULL;
		startPTR._tailPtr->_nptr=NewNode;
		startPTR._tailPtr=NewNode;
		startPTR._length++;
		if(startPTR._maxval<val)
			startPTR._maxval=val;
	}else{
		LL_Node* t2 = startPTR._headPtr;
		uint_fast32_t i(0); //loop till the pos to insert
		while (i<pos){
			++i;
			t2=t2->_nptr;
			if(!t2){	
				break;
			}
			if(i==pos){
				break;
			}
			if(t2->_nptr){
				t1=t2;
			}
		}
		if(startPTR._length<pos&&!t2){			//out of range Exception
			printf("list is Smaller than The position you specified");
			delete NewNode;
			return;
		}else{										//insert at pos
			NewNode->_nptr=t1->_nptr;
			t1->_nptr=NewNode;
			if(startPTR._maxval<val)
				startPTR._maxval=val;
		}
		startPTR._length++;
		t2=NULL;
	}
	t1=NULL;
}
void fn_EditLinkedList(uint_fast32_t pos,int_fast32_t val,LL_InitNode &startPTR){
	if(startPTR._length<pos){
		printf("Out of Range\n");
	}else{ //loop till the pos and change the value
		uint_fast32_t i=0;
		LL_Node* t = startPTR._headPtr;
		while (i<pos){ 
			t= t->_nptr ;
			++i;
		}
		t->_val=val;
		if(startPTR._maxval<val)
			startPTR._maxval=val;
	}
}
void fn_PushBack(int_fast32_t val, LL_InitNode &startPTR){
	LL_Node * NewNode =new LL_Node;
	NewNode->_nptr=NULL;
	NewNode->_val = val;
	if(startPTR._maxval<val){
		startPTR._maxval=val;
	}
	if(!startPTR._length){				//if Length = 0 means list is empty means tail pointer points to NULL
		NewNode->_nptr=startPTR._headPtr;  
		startPTR._headPtr=NewNode;

	}else{
		startPTR._tailPtr->_nptr=NewNode;
	}
	startPTR._tailPtr=NewNode;
	startPTR._length++;
}
void fn_Display(LL_InitNode & startPTR){  //display all  items in the list
	LL_Node *t=startPTR._headPtr;
	while(t!=NULL){
		printf("%d ",t->_val);
		t=t->_nptr;
	}
	printf("\n");
}