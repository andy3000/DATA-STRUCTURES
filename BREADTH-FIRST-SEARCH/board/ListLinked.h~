#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>

using namespace std;

template <typename DataType>
class List 
{
	public:
	
		List( int ignore = 0 );
		List( const List& );
		List& operator=( const List& );
		~List();
		
		void gotoBeginning();
		void gotoEnd();
		bool gotoNext();
		bool gotoPrior();		

		void insertAfter( const DataType& );
		void insertBefore( const DataType& );
		
		void replace( const DataType& );
		void remove();
		
		void clear();

		bool getCursor( DataType & ) const;
		bool isEmpty() const;
		bool isFull() const;

  private:
  
		class ListNode 
		{
			public:
			
				ListNode( const DataType&, ListNode* );

				DataType dataItem;
				ListNode* next;
		};

    ListNode* head;
    ListNode* cursor;

};

#endif
