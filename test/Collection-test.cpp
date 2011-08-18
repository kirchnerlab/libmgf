/*$Id$*/

/*
 * Collection-test.cpp
 *
 * Copyright (c) 2009 Bernhard Kausler <bernhard.kausler@iwr.uni-heidelberg.de>
 *
 * This file is part of ms++.
 *
 * ms++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ms++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ms++. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>
#include <vector>

#include <mgfp/Collection.h>

#include "unittest.hxx"

using namespace mgf;

struct CollectionTestSuite : vigra::test_suite {
    CollectionTestSuite() : vigra::test_suite("Collection") {
        add( testCase(&CollectionTestSuite::testConstructors));
        add( testCase(&CollectionTestSuite::testOperators));
        add( testCase(&CollectionTestSuite::testAssignment));
        add( testCase(&CollectionTestSuite::testStackOperations));
        add( testCase(&CollectionTestSuite::testListOperations));
        add( testCase(&CollectionTestSuite::testIterators));
        add( testCase(&CollectionTestSuite::testElementAccess));
        add( testCase(&CollectionTestSuite::testSizeAndCapacity));
        add( testCase(&CollectionTestSuite::testOther));
    }

    void testConstructors() {
        // default construction
        Collection<int> c;
        
        // construction from vector
        std::vector<int, std::allocator<int> > vector;
        Collection<int, std::allocator<int> > cFromVector = Collection<int, std::allocator<int> >(vector);
        should(vector == cFromVector.c_);

        // construction with preinit
        Collection<int> cPreinit(5);
        should(cPreinit.c_.size() == 5);

        // construction from sequence
        int myints[] = {1,2,3,4};
        Collection<int> cFromSeq (myints, myints + sizeof(myints) / sizeof(int) );

        should(cFromSeq.c_.size() == 4);
        int i = 1;
        for(Collection<int>::iterator it = cFromSeq.begin(); it < cFromSeq.end(); ++it) {           
            should(*it == i);
            ++i;         
        }

        // copy constructor        
        Collection<int> c_copy = c; // This wouldn't compile in case of an explicit copy constructor (which we don't want!)       
        should(c == c_copy);
    }

    
    void testOperators() {
        // operator=
        Collection<int> c1(2);
        Collection<int> c2(3);
        should(!(c1 == c2));
        c1 = c2;
        should(c1 == c2);

        // operator==
        Collection<int> c3(2);
        Collection<int> c4(3);
        should(!(c3 == c4));
        c3.c_ = c4.c_;
        should(c3 == c4);

        // operator<
        Collection<int> c5;
        Collection<int> c6;
        should((c5.c_ < c6.c_) == (c5 < c6));

        // swap operator
        Collection<int> c7(2);
        Collection<int> c7_copy = c7;        
        Collection<int> c8(3);
        Collection<int> c8_copy = c8;

        should(!((c7_copy == c8) && (c8_copy == c7)));        
        swap(c7, c8);
        should((c7_copy == c8) && (c8_copy == c7));
    }

    
    void testAssignment() {
        // assign sequence
        Collection<int> c(10);
        should(c.size() == 10);

        int myints[] = {1,2,3,4};
        c.assign(myints, myints + sizeof(myints) / sizeof(int) );

        should(c.size() == 4);
        int i = 1;
        for(Collection<int>::iterator it = c.begin(); it < c.end(); ++it) {           
            should(*it == i);
            ++i;       
        }

        // assign values
        Collection<int> c2(10);
        should(c2.size() == 10);

        // cast to size_type to prevent confusion with the other insert signature
        c2.assign((Collection<int>::size_type)4, 2317);
        should(c2.size() == 4);

        for(Collection<int>::iterator it = c2.begin(); it < c2.end(); ++it) {
            should(*it == 2317);
        }
    }

    
    void testStackOperations() {
        // push_back
        Collection<int> c;
        should(c.size() == 0);
        
        c.push_back(17);
        should(c.size() == 1);
        should(c[0] == 17);
    
        // pop_back
        int myints[] = {1,2,3,4};
        c.assign(myints, myints + sizeof(myints) / sizeof(int) );
        should(c[3] == 4);
        
        c.pop_back();
        should(c.size() == 3);
        should(c[2] == 3);
    }


    void testListOperations() {
        Collection<int> c;
        int myints[] = {46,243,45};
        c.assign(myints, myints + sizeof(myints) / sizeof(int) );

        // insert
        should(!(c[1] == 23)); 
        Collection<int>::iterator it_insert = c.insert(c.begin()+1, 23);
        should(c.size() == 4);
        should(c[1] == 23);
        should(*it_insert == 23);
        should((c.begin() + 1) == it_insert);

        // multiple insert
        // c is now {46,23,243,45}
        should(c.size() == 4);
        // avoid confusion with the templated insert signature by explicitly casting to size_type
        c.insert(c.begin()+1, (Collection<int>::size_type)2, 123); // 2x 123 at position
        should(c.size() == 6);
        should(c[1] == 123 && c[2] == 123);

        // c is now {46,123,123,23,243,45}
        // templated insert
        int toBeInserted[] = {823, 329, 198};
        c.insert(c.begin()+1, toBeInserted, toBeInserted + 3);
        should(c.size() == 9);
        should(c[1] == 823 && c[2] == 329 && c[3] == 198);

        // c is now {46,823,329,198,123,123,23,243,45}
        // erase
        Collection<int>::iterator it_erase = c.erase(c.begin()+1);
        should(c.size() == 8);
        should(*it_erase == 329);
        should(c.begin()+1 == it_erase);        

        // c is now {46,329,198,123,123,23,243,45}
        // erase sequence
        Collection<int>::iterator it_erase_seq = c.erase(c.begin()+1,c.begin()+4);
        should(c.size() == 5);
        should(*it_erase_seq == 123);
        should(c.begin()+1 == it_erase_seq);

        // clear
        should(c.size() == 5);
        should(!(c.empty()));
        c.clear();
        should(c.size() == 0);
        should(c.empty());
    }

    
    void testIterators() {
        Collection<int> c(5);

        // begin, rbegin, end and rend
        should(c.begin() == c.c_.begin());
        should(c.rbegin() == c.c_.rbegin());
        should(c.end() == c.c_.end());
        should(c.rend() == c.c_.rend());
        should(c.begin() == c.c_.begin());

        // const begin and end
        const Collection<int> c_const(5);
        should(c_const.begin() == c_const.c_.begin());
        should(c_const.end() == c_const.c_.end());
    }


    void testElementAccess() {
        Collection<int> c;
        int myints[] = {46,243,45};
        c.assign(myints, myints + sizeof(myints) / sizeof(int) );

        // operator[]
        should(c[0] == 46 && c[1] == 243 && c[2] == 45);
        c[1] = 127;
        should(*(c.begin() + 1) ==  127);
        
        // at
        should(c.at(0) == 46 && c.at(1) == 127 && c.at(2) == 45);
        c.at(1) = 259;
        should(*(c.begin() + 1) ==  259);

        
        int myints_for_const[] = {46,243,45};
        const Collection<int> c_const(myints_for_const, myints_for_const + sizeof(myints_for_const) / sizeof(int) );

        // const operator[]
        should(c_const[0] == 46 && c_const[1] == 243 && c_const[2] == 45);

        // const at
        should(c_const.at(0) == 46 && c_const.at(1) == 243 && c_const.at(2) == 45);
    }

    
    void testSizeAndCapacity() {
        // size
        int myints[] = {26,45,12};
        Collection<int> c(myints, myints + sizeof(myints) / sizeof(int));
        should(c.size() == 3);
        c.push_back(32);
        should(c.size() == 4);
        c.pop_back();
        should(c.size() == 3);
        c.pop_back();
        should(c.size() == 2);
        c.clear();
        should(c.size() == 0);
        should(c.empty());
        
        // maxSize
        Collection<int> c_maxSize(4);
        should(c_maxSize.max_size() == c_maxSize.c_.max_size());

        // empty
        Collection<int> c_empty(4);
        should(!(c_empty.empty()));
        c_empty.clear();
        should(c_empty.empty());

        // resize
        Collection<int> c_resize(5);
        should(c_resize.size() == 5);
        c_resize.resize(10, 13);
        should(c_resize.size() == 10);
        should(c_resize.at(9) == 13);
        c_resize.resize(2);
        should(c_resize.size() == 2);
        should(c_resize.at(1) == 0);

        // capacity
        Collection<int> c_capacity(5);
        should(c_capacity.capacity() == c_capacity.c_.capacity());

        // reserve
        Collection<int> c_reserve;
        c_reserve.reserve((Collection<int>::size_type)1000000);
        should(c_reserve.capacity() >= 1000000);
    }

    
    void testOther() {
        // swap
        Collection<int> c1(2);
        Collection<int> c1_copy = c1;        
        Collection<int> c2(3);
        Collection<int> c2_copy = c2;

        should(!((c1_copy == c2) && (c2_copy == c1)));        
        c1.swap(c2);
        should((c1_copy == c2) && (c2_copy == c1));


        // get_allocator
        Collection<int> c_alloc;
        should(c_alloc.get_allocator() == c_alloc.c_.get_allocator());
    }
};

int main()
{
    CollectionTestSuite test;
    int failed = test.run();
    std::cout << test.report() << std::endl;
    return failed;
}


