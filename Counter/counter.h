/*counter.h*/

//
// << Hassan Murtaza >>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
// 
// Example:  suppose C is a Counter, and you insert the elements 3, 11, 
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's 
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will 
// consume at most 4N space.
// 

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;


template<typename T>
class Counter
{
private:
  class Node {
    private:
      T ele;
      int count;
    public:
      Node() {
        count = 0;
      }

      void setValue(const T& e) {
          ele = e;
      }
      T& getValue()  {
        return ele;
      }

      int getCount() {
        return count;
      }
      void setCount(int x) {
        count = x;
      }
      void incCount() {
        count++;
      }
  };
  Node *cArr;
  int n;
  int capacity;
  class iterator{  
    private:
      Node* iter;
      int index;
    public:
      iterator(Node* c,int l) {
        iter = c;
        index = l;
      }
      iterator& operator++() {              //When I call operator* index needs to be updated
        this->index++;
        return *this;
      }
      const T& operator*() {                    //Dereferencing and returning the current element I am at 
          return this->iter[index].getValue();
      }
      bool operator!=(const iterator& rhs ) {
        if (this->iter != rhs.iter) {
            return true;
        }
				else if (this->index != rhs.index) {
            return true;
        }

        return false;
      }
      
  };

public:

  Counter()
  {
    this->capacity = 8;
    this->cArr = new Node[this->capacity];
    this->n = 0;
    
  }
  
  
  //
  // copy constructor:
  //
  Counter(const Counter& other)
  {
   this->n = other.size();
   this->capacity = other.capacity;
   this->cArr = new Node[this->capacity];
   for (int i = 0; i < n; i++) {
     cArr[i] = other.cArr[i];
   }
  }
  
  
  ~Counter()
  { 
    delete []cArr;
    capacity = 0;
    n = 0;
  }


  int size() const
  {
    return this->n;
  }
  
  int getCapacity() {
      return this->capacity;
  }


  bool empty() const
  {
    if (this->n == 0) {
        return true;
    }
    return false;
  }
  
  
  //
  // clear()
  //
  // Empties the set, deleting all elements and counts.
  //
  void clear()
  {
    delete []cArr;
    n = 0;
    cArr = new Node[capacity];
  }
  
  int binSearch(const T& e) const {
    int low = 0;
    int high = n-1;
    int index = -1;
    while(low <= high) {
      int middle = (low+high)/2;
      if ( !(this->cArr[middle].getValue() < e) && !(e < this->cArr[middle].getValue() )  ) {
            index=middle;
            break;
      }
      else if (e < this->cArr[middle].getValue() ) {
          high = middle - 1;
      }
      else {
          low = middle + 1;
      }
    }
    return index;
  }
  
  //
  // [e]
  //
  // Returns true if set contains e, false if not.
  //
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  //
  bool operator[](const T& e)
  {
    return this->operator()(e) > 0;
    
  }


  //
  // (e)
  // 
  // Returns a count of how many times e has been inserted into the set;
  // the count will be 0 if e has never been inserted.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: average-case O(lgN).
  // 
  int operator()(const T& e) const
  {
      int pos = binSearch(e);
      if (pos == -1) {
          return 0;
      }
      return cArr[pos].getCount();
  }
  
  
  //
  // insert(e)
  // 
  // If e is not a member of the set, e is inserted and e's count set to 0.
  // If e is already in the set, it is *not* inserted again; instead, e's
  // count is increased by 1.  Sets are unbounded in size, and elements are
  // inserted in order as defined by T's < operator; this enables in-order 
  // iteration.
  // 
  // NOTE: since the type of e is unknown, elements are compared using <. 
  // This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
  // 
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  //
  void insert(const T& e)
  {
    int pos = binSearch(e);
    if (pos == -1) {
      if (n >= capacity) {
          this->resize();
      }
      this->cArr[this->n].setValue(e);
      this->cArr[this->n].incCount();
      int index = this->n;
      for (int i = n-1; i >= 0; i--) {           // Putting the value in the right place
        if (e < cArr[i].getValue()) {
          Node temp = cArr[i];
          cArr[i] = cArr[index];
          cArr[index] = temp;
          index = i;
        }
      }
      this->n++;
    }
    else {
     cArr[pos].incCount();
    }
  }
  
  void resize() {
    this->capacity = this->capacity*2;
    Node *arr = new Node[this->capacity];
    for (int i = 0; i < n; i++) {
        arr[i] = cArr[i];
    }
    delete[] cArr;
    this->cArr = arr;
  }
  // 
  // += e
  //
  // Inserts e into the set; see insert.
  //
  // Time complexity: worst-case O(N).
  // Space complexity: 4N.
  // 
  Counter& operator+=(const T& e)
  {
    //
    // insert e into "this" set:
    //
    this->insert(e);

    // return "this" updated set:
    return *this;
  }
  
  
  //
  // lhs = rhs;
  //
  // Makes a deep copy of rhs (right-hand-side) and assigns into
  // lhs (left-hand-side).  Any existing elements in the lhs
  // are destroyed *before* the deep copy is made.
  // 
  // NOTE: the lhs is "this" object.
  //
  Counter& operator=(const Counter& rhs)
  {
    //
    // NOTE: where is the lhs in the function call?  The lhs operand is 
    // hidden --- it's "this" object.  So think this->operator=(rhs).  
    //

    // check for self-assignment:
    if (this == &rhs)  // S = S;
      return *this;
    
     delete [] this->cArr;
     this->capacity = rhs.capacity;
     this->n = rhs.n;
     this->cArr = new Node[this->capacity];
     for (int i = 0; i < n; i++) {
       this->cArr[i] = rhs.cArr[i];
     }


    //
    // return "this" updated set:
    //
    return *this;
  }
  

  //
  // begin()
  // 
  // Returns an iterator denoting the first element of the set.  If the 
  // set is empty, begin() == end().  The iterator will advance through
  // the elements in order, as defined by T's < operator.
  //
  iterator begin()
  {
    return iterator(cArr,0);
  }
  
  
  //
  // end()
  // 
  // Returns an iterator denoting the end of the iteration space --- i.e.
  // one past the last element of the set.  If the set is empty, then
  // begin() == end().
  // 
  iterator end()
  {
    return iterator(cArr,n);
  }

};
