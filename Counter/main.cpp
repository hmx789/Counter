/*main.cpp*/

//
// << Hassan Murtaza >>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
// 
// Test cases for Counter container, which acts like a set but keeps a count
// of how many times each element was inserted.  
//
// References:
//   Unit testing based on Catch framework: https://github.com/catchorg/Catch2
//   Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
//   install:     sudo apt-get install catch
//   compilation: g++ -std=c++11 -Wall -o main.exe main.cpp
//   execution:   ./main.exe
//

// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include <catch.hpp>

// our Counter class:
#include "counter.h"

// *****************************************************************
//
// Test cases:
// 
// *****************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


TEST_CASE( "empty Counter<int>", "[Counter]" ) 
{
  Counter<int> C;

  REQUIRE(C.empty() == true);
  REQUIRE(C.size() == 0);
}//test

TEST_CASE( "Counter<int> Resizing array", "[Counter]" ) 
{
  Counter<int> C;
	for (int i = 1; i <= 50; i++) {
		C.insert(i);
	}
  REQUIRE(C.empty() == false);
  REQUIRE(C.size() == 50);
	REQUIRE(C(50) == 1);
	REQUIRE(C(1) == 1);
}//test

TEST_CASE( "Counter<int> with 1 element", "[Counter]" ) 
{
  Counter<int> C;

  REQUIRE(C.size() == 0);
  REQUIRE(C.empty() == true);
  
  SECTION("inserting element")
  {
    C.insert(512);
    C.insert(123);
    C.insert(1);
    C.insert(2);
    C.insert(1);
    C.insert(123);
    C.insert(96);
    C.insert(22);
    C.insert(19);
    C.insert(2019);
    C.insert(2018);
    C.insert(9900);


    REQUIRE(C.size() == 10);
    REQUIRE(!C.empty());
  
    
    SECTION("element contains")
    {
      REQUIRE(C[123] == true);
      REQUIRE(C(123) == 2);
      REQUIRE(C(1) == 2);
      REQUIRE(C[9900] == true);     
    }
  
    
  SECTION("element count")
  {
    REQUIRE(C(123) == 2);
  }

    
    SECTION("unknown elements not contained")
    {
      REQUIRE(!C[0]);
      REQUIRE(!C[122]);
      REQUIRE(!C[124]);
    }
    
    SECTION("unknown element counts")
    {
      REQUIRE(C(0) == 0);
      REQUIRE(C(122) == 0);
      REQUIRE(C(124) == 0);
    }
  }
}//test


TEST_CASE( "Counter<string> with 4 elements", "[Counter]" ) 
{
  Counter<string> C;

  REQUIRE(C.size() == 0);
  REQUIRE(C.empty() == true);
  
  SECTION("inserting 1st element")
  {
    C.insert("apple");
    
    REQUIRE(C.size() == 1);
    REQUIRE(!C.empty());
    
    REQUIRE(C["apple"] == true);
    REQUIRE(C("apple") == 1);
    
    SECTION("inserting 3 more elements")
    {
      C += "banana";
      C.insert("pear");
      C += "pizza";
      
      REQUIRE(C.size() == 4);
      REQUIRE(!C.empty());
      
      REQUIRE(C["apple"] == true);
      REQUIRE(C["banana"] == true);
      REQUIRE(C["pear"] == true);
      REQUIRE(C["pizza"] == true);
      
      SECTION("checking element counts")
      {
        REQUIRE(C("apple") == 1);
        REQUIRE(C("banana") == 1);
        REQUIRE(C("pear") == 1);
        REQUIRE(C("pizza") == 1);
      }
      
      SECTION("checking non-elements")
      {
        REQUIRE(!C["appl"]);
        REQUIRE(!C["applee"]);
        REQUIRE(!C["Pear"]);
        REQUIRE(!C["piazza"]);
        REQUIRE(!C["zizza"]);
      }

      SECTION("checking non-element counts")
      {
        REQUIRE(C("appl") == 0);
        REQUIRE(C("applee") == 0);
        REQUIRE(C("Pear") == 0);
        REQUIRE(C("piazza") == 0);
        REQUIRE(C("zizza") == 0);
      }
    }
  }
}//test





class Student
{
private:
  int UIN, Mid, Fnl;

public:
  Student()
    : UIN(-1), Mid(-1), Fnl(-1)
  { }

  Student(int uin, int mid, int fnl)
    : UIN(uin), Mid(mid), Fnl(fnl)
  { }

  int getUIN() const
  {
    return UIN;
  }

  double getExamAvg() const
  {
    return (Mid + Fnl) / 2.0;
  }

  //
  // lhs < rhs
  //
  // returns true if lhs < rhs, false otherwise.
  //
  bool operator<(const Student& other) const
  {
    //
    // NOTE: lhs is "this" object.
    // 
    if (this->UIN < other.UIN)
      return true;
    else
      return false;
  }
};

TEST_CASE("Counter<Student> with 1 element", "[Counter]")
{
  Counter<Student> C;

  REQUIRE(C.size() == 0);
  REQUIRE(C.empty() == true);

  SECTION("inserting 1 studnet")
  {
    Student S(123456, 100, 88);

    C.insert(S);

    REQUIRE(C.size() == 1);
    REQUIRE(!C.empty());

    SECTION("element contains")
    {
      Student S2(123456, 0, 0);  // create a student with matching UIN:

      REQUIRE(C[S2] == true);
    }

    SECTION("element count")
    {
      Student S2(123456, 0, 0);  // create a student with matching UIN:

      REQUIRE(C(S2) == 1);
    }

    SECTION("unknown elements not contained")
    {
      Student S3(010100, 0, 0);  // student #1 that doesn't match:
      Student S4(999999, 0, 0);  // student #2
      Student S5(1234567, 0, 0);  // student #3

      REQUIRE(!C[S3]);
      REQUIRE(!C[S4]);
      REQUIRE(!C[S5]);
    }

    SECTION("unknown element counts")
    {
      Student S3(010100, 0, 0);  // student #1 that doesn't match:
      Student S4(999999, 0, 0);  // student #2
      Student S5(1234567, 0, 0);  // student #3

      REQUIRE(C(S3) == 0);
      REQUIRE(C(S4) == 0);
      REQUIRE(C(S5) == 0);
    }
  }
}//test //passed






/*
	This tests the copy constructor of the counter class.
	It's almost identical to the test for the copy assignment 
	operator. The only difference is that C2 is copy constructed.
*/
TEST_CASE("Counter<int> copy constructor", "[Counter]")
{
	Counter<int> C1;
	// Insert 3 values into C1
	C1 += 5; C1 += 5;          // 2 copies
	C1 += 4;
	C1 += 6; C1 += 6; C1 += 6; // 3 copies
	// Test the copy constructor
	SECTION("copy construct C2 from C1")
	{	// Copy construct C2 from C1
		Counter<int> C2(C1);
		// Test that the sizes are correct
		REQUIRE(C1.size() == 3);
		REQUIRE(C2.size() == C1.size());
		// Test that C1 still has the correct values
		REQUIRE((C1[5] == true && C1(5) == 2));
		REQUIRE((C1[4] == true && C1(4) == 1));
		REQUIRE((C1[6] == true && C1(6) == 3));
		// Test that C2 copied the values from C1
		SECTION("check that C2 copied the values from C1")
		{
			REQUIRE(C2[5] == true);
			REQUIRE(C2[4] == true);
			REQUIRE(C2[6] == true);
		}
		// Test that C2 copied the counts from C1
		SECTION("check that C2 copied the counts from C1")
		{
			REQUIRE(C2(5) == C1(5));
			REQUIRE(C2(4) == C1(4));
			REQUIRE(C2(6) == C1(6));
		}
		// Test that C1 and C2 are independent (in memory)
		SECTION("check that C1 and C2 are independent")
		{	// Insert 1 new value into C1
			C1 += 7;
			// Insert 2 new values into C2
			C2 += 3;
			C2 += 2;
			// Test that C1 size has been updated
			// and new value was inserted
			REQUIRE(C1.size() == 4);
			REQUIRE((C1[7] == true && C1(7) == 1));
			// Test that C2 size has been updated
			// and new values were inserted
			REQUIRE(C2.size() == 5);
			REQUIRE((C2[3] == true && C2(3) == 1));
			REQUIRE((C2[2] == true && C2(2) == 1));
			// Test that C1 does not have values from C2
			SECTION("check that C1 does not have values from C2")
			{
				REQUIRE((C1[3] == false && C1(3) == 0));
				REQUIRE((C1[2] == false && C1(2) == 0));
			}
			// Test that C2 does not have values from C1
			SECTION("check that C2 does not have values from C1")
			{
				REQUIRE((C2[7] == false && C2(7) == 0));
			}
			// Test that C1 has correct order (unaffected by C2)
			SECTION("check that C1 ordering is correct")
			{	
				// Correct order: 4, 5, 6, 7
				auto iter = C1.begin();
				// Test order
				REQUIRE(*iter == 4);
				REQUIRE(*++iter == 5);
				REQUIRE(*++iter == 6);
				REQUIRE(*++iter == 7);
				// Test for end of sequence
				REQUIRE(!(++iter != C1.end()));
			}
			// Test that C2 has correct order (unaffected by C1)
			SECTION("check that C2 ordering is correct")
			{
				// Correct order: 2, 3, 4, 5, 6
				auto iter = C2.begin();
				// Test order
				REQUIRE(*iter == 2);
				REQUIRE(*++iter == 3);
				REQUIRE(*++iter == 4);
				REQUIRE(*++iter == 5);
				REQUIRE(*++iter == 6);
				// Test for end of sequence
				REQUIRE(!(++iter != C2.end()));
			}

		}
	}

}// test

TEST_CASE("Counter<int> insert stress test", "[Counter]"){
	Counter<int> counter; 
	set<int> randomNums;
	int count;
	
	SECTION("using 10^3 elements"){
		count = 1000;
		for (int i = 0; i < count; i++){
			randomNums.insert((rand() % 1000000) + 1);
		}
		//transfer the numbers from set to contained; 
		for (const auto& val : randomNums){
			counter.insert(val); 
		}
		REQUIRE(counter.size() == randomNums.size());
	}
}
TEST_CASE("Counter<int> clear", "[Counter]"){
	Counter<int> counter; 
	set<int> randomNums;
	int count = 100;
	for (int i = 0; i < count; i++){
		randomNums.insert((rand() % 1000000) + 1);
	}
	//transfer the numbers from set to contained; 
	for (const auto& val : randomNums){
		counter.insert(val); 
	}
	REQUIRE(counter.size() == randomNums.size());
	
	SECTION("Clearing 100 elements"){
		counter.clear(); 
		REQUIRE(counter.size() == 0); 
		for (const auto& val : randomNums){
			REQUIRE(counter[val] == false); 
		}
	}
}
TEST_CASE("Copy constructor test", "[Counter]"){
	SECTION("With ints"){
		Counter<int> counter; 
		set<int> randomNums;
		int count = 100;
		for (int i = 0; i < count; i++){
			randomNums.insert((rand() % 1000000) + 1);
		}
		//transfer the numbers from set to contained; 
		for (const auto& val : randomNums){
			counter.insert(val); 
		}
		Counter<int> copyCounter(counter); 
		REQUIRE(counter.size() == copyCounter.size()); 
		//clear the original one 
		counter.clear(); 
		REQUIRE(copyCounter.size() > counter.size()); 
		
		//make sure that a deep copy was made
		for (const auto& val : randomNums){
			REQUIRE(copyCounter[val] == true); 
		}
	}
}

TEST_CASE("Checking if for each loop is working correctly") 
{
	Counter<int> C;
	int count = 1;
	for (int i = 1; i < 11; i++) {
		C.insert(i);
		REQUIRE(C[i] == 1);
	}
	for ( auto x : C) {
			REQUIRE(x == count);
			count++;
	}
}
