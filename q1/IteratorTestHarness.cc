/*
 * Iterator test harness.
 *
 *  Created by Jo Atlee.
 *  Last updated: 2017-05-19
 *  Copyright 2017 UW. All rights reserved.
 *
 */

#include "Menu.h"
#include "MenuItem.h"
#include "ComponentIterator.h"
#include <string>
#include <iostream>

//***********************************************************************************************
// Define includes and functions/functors for Q2 here! Note that the Makefile for each part
// defines the macro STL[a-f].
//***********************************************************************************************
#ifdef STLa
#include "main_a.h"
#endif
#ifdef STLb
#include "main_b.h"
#endif
#ifdef STLc
#include "main_c.h"
#endif
#ifdef STLd
#include "main_d.h"
#endif
#ifdef STLe
#include "main_e.h"
#endif
#ifdef STLf
#include "main_f.h"
#endif

using namespace std;

//************************************************************************
//  Helper variables and functions for test harness
//************************************************************************

// Exception classes for test harness
class SyntaxError {};
class BadIndex {};
class MenuNotFound {
  public:
    MenuNotFound( const string & name ) : name_{name} {}
    string name() const { return name_; }
  private:
    string name_;
};

class NoMenu {
  public:
    NoMenu( int index ) : index_{index} {}
    int index() const { return index_; }
  private:
    int index_;
};

//  Test harness commands.
enum Op {INVALID_COMMAND, MENU, ITEM, ADD_CHILD, REMOVE, PRINT, DONE};

// Returns: operation to be performed.
Op convertOp( const string & );

// Try to clean up the stream after fail().
void sinCleanup( istream & );

// Throws: BadIndex if index is < 0 or > 9
// Returns: 0 <= index <= 9
int readInIndex( istream & );

// Throws: SyntaxError if failed to obtain a name.
// Returns: the name without the double quotation marks. 
string readInName( istream & );


int main() {
    Op op; // Operation to 
    
    cout << "Test harness for Menu Composite and Iterator" << endl << endl;

    // Create a collection of menus to manipulate.
    MenuComponent* menus[10] = {nullptr};

    // Enable reading of boolean values "true" and "false".
    cin >> boolalpha;
    
    // Populate the Composite Menu
    for( ;; ) {
	int index = -1, index2 = -1;
	string command, name = "";
	
	cout << "Command: ";
	cin >> command;
	if ( cin.fail() ) break;
	op = convertOp( command );
	if ( op == DONE ) break;
    
	try {
	    switch( op ) {
	      case MENU: 
		  index = readInIndex( cin );
		  name = readInName( cin );
		  delete menus[index];
		  menus[index] = new Menu( name );
		  break;

	      case ADD_CHILD:
		  index = readInIndex( cin );
		  index2 = readInIndex( cin );
		  if ( !menus[index] ) throw NoMenu( index );
		  if ( !menus[index2] ) throw NoMenu( index2 );
		  menus[index]->add(menus[index2]);
		  menus[index2] = nullptr;
		  break;

	      case ITEM:
		  index = readInIndex( cin );
		  name = readInName( cin );
		  float price;
		  int calories;
		  bool veg;
		  cin >> price >> calories >> veg;
		  if ( cin.fail() ) {
		      sinCleanup( cin );
		      throw SyntaxError{};
		  } // if

		  delete menus[index];
		  menus[index] = new MenuItem ( name, price, calories, veg );
		  break;

	      case PRINT: 
		  index = readInIndex( cin );
		  if ( !menus[index] ) throw NoMenu( index );
		  for ( auto it = menus[index]->begin(); it != menus[index]->end(); it++ ) {
		      cout << *it << endl;
		  } // for
		  break;

	      case REMOVE:
		  index = readInIndex( cin );
		  if ( !menus[index] ) throw NoMenu( index );
		  name = readInName( cin );
		  menus[index]->remove( name );
		  break;

	      default:
		  cout << "Invalid command \"" << command << "\"." << endl;
		  break;
            } // switch

        } catch ( NoMenu& e ) {
            cout << "Menu Element " << e.index() << " does not exist." << endl;
        } catch ( BadIndex& ) {
            cout << "Invalid name of menu!" << endl;
        } catch ( SyntaxError& ) {
            cout << "Command has syntax errors. No change to menu." << endl;
        } catch ( MenuComponent::InvalidOp& ) {
            cout << "Command is invalid on Menu Items. No change to menus." << endl;
        } // catch
        
    }

    //***********************************************************************************************
    // Deploy STL algorithms code for Q2 here!
    //***********************************************************************************************
#ifdef STLa
#include "main_a.cc"
#endif
#ifdef STLb
#include "main_b.cc"
#endif
#ifdef STLc
#include "main_c.cc"
#endif
#ifdef STLd
#include "main_d.cc"
#endif
#ifdef STLe
#include "main_e.cc"
#endif
#ifdef STLf
#include "main_f.cc"
#endif
    
    for ( int i = 0; i < 10; i++ ) {
        if ( menus[i] ) delete menus[i];
    } // for
} // main

// Parse input command and return operation to perform.
Op convertOp( const string & opStr ) {
    switch (opStr[0]) {
      case 'm': return MENU;
      case 'a': return ADD_CHILD;
      case 'i': return ITEM;
      case 'r': return REMOVE;
      case 'p': return PRINT;
      case 'd': return DONE;
      default: return INVALID_COMMAND;
    } // switch
} // convertOp


// Try to clean up the stream after sin.fail().
void sinCleanup( istream & sin ) {
    sin.clear();
    string junk;
    getline( sin, junk );
} // sinCleanup


// Parse name of menu that is to be operated on and return its index.
int readInIndex( istream & sin ) {
    int index = -1;
    sin >> index;
    if ( index >= 0 && index <= 9 ) return index;
    sinCleanup( sin ); // try to fix sin   
    throw BadIndex{};
} // readInIndex

string readInName( istream & sin ) {
    char quotes;
    string name;
    
    sin >> quotes;
    getline( sin, name, '"');
    
    if ( sin.fail() ) {
        sinCleanup( sin );
        throw SyntaxError{};
    } // if

    return name;
} // readInName
