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
	int_fast32_t _minval;
	LL_Node* _headPtr;
	LL_Node* _tailPtr;			// for add last O(1) Complexity
	LL_InitNode(){
		_length=0;
		_maxval=INT32_MIN;
		_minval=INT32_MAX;
		_headPtr=NULL;
		_tailPtr=NULL;
	}
};

LL_InitNode& fn_InitializeLL(); // initalize Linked List
void fn_InsertLinkedList(int_fast32_t val,uint_fast32_t pos,LL_InitNode &startPTR); //insert in linked list
void fn_InsertSortLinkedList(int_fast32_t val,LL_InitNode &startPTR);				//insert in sorted LinkedList
void fn_EditLinkedList(uint_fast32_t pos,int_fast32_t val,LL_InitNode &startPTR);	//edit
void fn_PushBack(int_fast32_t val, LL_InitNode &startPTR);							//add last
void fn_Display(LL_InitNode & startPTR);											//display all
void fn_SetMaxMinVal(int_fast32_t val , LL_InitNode &startPTR);						//setTheinitial node min/max values
void fn_DeleteLL(LL_InitNode &startPTR);											//delete all
void fn_RemoveAll(int_fast32_t val,LL_InitNode &startPTR);							//remove all values specified
void fn_Remove(uint_fast32_t pos,LL_InitNode &startPTR);							//remove specific index
void fn_RecheckMax_Min(LL_InitNode &startPTR);										//
int _tmain(int argc, _TCHAR* argv[]){

	LL_InitNode & startPtr = fn_InitializeLL();
	//All test Cases !
	fn_InsertLinkedList(9,startPtr._length,startPtr); // add last
	fn_InsertLinkedList(5,0,startPtr);				//add first
	fn_InsertLinkedList(4,1,startPtr);
	fn_InsertLinkedList(3,2,startPtr);				//add pos
	fn_InsertLinkedList(2,2,startPtr);
	fn_PushBack(10,startPtr);
	fn_PushBack(11,startPtr);
	fn_Display(startPtr);					// display			
	fn_EditLinkedList(4,10,startPtr);	   //edit at 4th pos 10
	fn_Display(startPtr);
	fn_PushBack(3,startPtr);
	fn_PushBack(3,startPtr);
	fn_Display(startPtr);
	fn_RemoveAll(3,startPtr);
	fn_Display(startPtr);
	fn_Remove(0,startPtr);
	fn_Display(startPtr);
	fn_Remove(startPtr._length,startPtr);
	fn_Display(startPtr);
	fn_Remove(1,startPtr);
	fn_Display(startPtr);
	fn_InsertSortLinkedList(50,startPtr);
	fn_InsertSortLinkedList(0,startPtr);
	fn_InsertSortLinkedList(5,startPtr);
	fn_Display(startPtr);
	fn_DeleteLL(startPtr);

	for(uint_fast8_t i(0);i<10;++i){
		fn_InsertSortLinkedList(1,startPtr);
	}
	fn_Display(startPtr);
	fn_RemoveAll(1,startPtr);

	fn_DeleteLL(startPtr);
	return 0;
}
LL_InitNode& fn_InitializeLL(){
	LL_InitNode *NewNode =new LL_InitNode;
	NewNode-> _length=0; // this val will indicate the length of all list
	NewNode-> _maxval=INT32_MIN;
	NewNode-> _minval=INT32_MAX;
	NewNode-> _headPtr=NULL;
	NewNode-> _tailPtr=NULL;
	return *NewNode;
}
void fn_SetMaxMinVal(int_fast32_t val,LL_InitNode &startPTR){
	if(startPTR._maxval<val)
		startPTR._maxval=val;
	else if(startPTR._minval > val)
		startPTR._minval=val;

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
		fn_SetMaxMinVal(val,startPTR);

	}else if(pos==startPTR._length){			//insert at last Pos
		NewNode->_nptr=NULL;
		startPTR._tailPtr->_nptr=NewNode;
		startPTR._tailPtr=NewNode;
		startPTR._length++;
		fn_SetMaxMinVal(val,startPTR);
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
			fn_SetMaxMinVal(val,startPTR);
		}
		startPTR._length++;
		t2=NULL;
	}
	t1=NULL;
}
void fn_InsertSortLinkedList(int_fast32_t val,LL_InitNode &startPTR){
	if(val>=startPTR._maxval){				// val > Max value in LL then add Last
		fn_PushBack(val,startPTR);
	}
	else if( val<=startPTR._minval){			// val < Min value in LL then add First 
		fn_InsertLinkedList(val,0,startPTR);  
	}
	else{									// Loop till <= of the current node then insert at index
		uint_fast32_t i(0);
		for(LL_Node * it = startPTR._headPtr;it!=startPTR._tailPtr; it=it->_nptr){
			if(it->_val >= val ){
				fn_InsertLinkedList(val,i,startPTR);
				break;
			}
			++i;
		}
	}
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
		fn_SetMaxMinVal(val,startPTR);
	}
}
void fn_PushBack(int_fast32_t val, LL_InitNode &startPTR){
	LL_Node * NewNode =new LL_Node;
	NewNode->_nptr=NULL;
	NewNode->_val = val;
	fn_SetMaxMinVal(val,startPTR);
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
void fn_DeleteLL(LL_InitNode &startPTR){ //Not tested
	if(startPTR._headPtr != NULL){
		LL_Node * temp= startPTR._headPtr;
		if(temp->_nptr != NULL){
			for(LL_Node * it = startPTR._headPtr->_nptr;it != startPTR._tailPtr; it=it->_nptr){
				delete temp;
				temp = it;
			}
			delete temp;
			delete startPTR._tailPtr;
		}else{
			delete temp;

		}
	}
	delete &startPTR; // remove all data
	startPTR = fn_InitializeLL(); // reintialize for variable scope reuse
}
void fn_RecheckMax_Min(LL_InitNode &startPTR){
	LL_Node *temp=startPTR._headPtr;
	while (temp != NULL){
		fn_SetMaxMinVal(temp->_val,startPTR);
		temp=temp->_nptr;
	}
}
void fn_RemoveAll(int_fast32_t val,LL_InitNode &startPTR){
	if(val>startPTR._length){
		printf_s("OutOfRange\n");
	}else{
		LL_Node * temp=startPTR._headPtr;
		while (startPTR._headPtr != NULL && startPTR._headPtr->_val == val){ //Numbers to remove are in the 1st of the linked list
			temp=startPTR._headPtr;
			startPTR._headPtr=startPTR._headPtr->_nptr;
			delete temp;
			temp=startPTR._headPtr;
			startPTR._length--;
		}
		if(startPTR._headPtr !=NULL){
			temp=startPTR._headPtr;
			LL_Node * temp2=startPTR._headPtr;
			while (temp->_nptr!=NULL){
				temp2=temp;
				temp=temp->_nptr;
				if(temp->_val==val){
					temp2->_nptr=temp->_nptr;
					delete temp;
					temp=temp2->_nptr;
				}
			}
			if(temp->_val==val){
				startPTR._tailPtr = temp2;
				startPTR._tailPtr->_nptr=NULL;
				delete temp;
			}
		}else{										// all list have same value and all have been deleted
			delete &startPTR;
			startPTR = fn_InitializeLL();
		}
		fn_RecheckMax_Min(startPTR);
	}

}
void fn_Remove(uint_fast32_t pos , LL_InitNode &startPTR){
	if(pos> startPTR._length){
		printf_s("OutOfRange");
		return;
	}
	LL_Node * temp =NULL;
	if( pos == startPTR._length){ // delete last
		temp = startPTR._headPtr;
		LL_Node* temp2 = temp;
		while (temp->_nptr !=NULL){
			temp2=temp;
			temp = temp->_nptr;
		}
		startPTR._tailPtr=temp2;
		startPTR._tailPtr->_nptr=NULL;
		delete temp;
	}else if(pos == 0){				//delete first
		temp=startPTR._headPtr;
		temp=temp->_nptr;
		delete startPTR._headPtr;
		startPTR._headPtr=temp;
	}else{
		temp=startPTR._headPtr;
		LL_Node* temp2 =startPTR._headPtr;
		for(uint_fast32_t i(0);i<pos;++i){
			temp2 = temp;
			temp=temp->_nptr;
			++i;
		}
		temp2->_nptr=temp->_nptr;
		delete temp;
	}
	startPTR._length--;
}