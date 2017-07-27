#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Menu.h"

using namespace std;

//****************************************************************************
// MENU
//****************************************************************************
Menu::Menu ( const string & name ) : MenuComponent{name} {}

Menu::~Menu() {
    for ( auto it = entries_.begin(); it != entries_.end(); ++it ) {
        if ( *it ) {
            delete *it;
            *it = nullptr;
        } // if
    } // for
} // Menu::~Menu

void Menu::add( MenuComponent* newEntry ) {
    newEntry->menuDepthInc();
    entries_.push_back( newEntry );
} // Menu::add

void Menu::remove( string name ) {
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        if ( (*it)->name() == name ) {
            delete *it;
            entries_.erase( it );
            return;
        } // if
    } // for
} // Menu::remove

int Menu::numChildren() const { return entries_.size(); }

int Menu::size() const {
    int size = 1;
    
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        size += (*it)->size();
    } // for
    
    return size;
} // Menu::size


MenuComponent* Menu::getChild( int i ) const { return entries_.at(i); }

void Menu::menuDepthInc() {
    MenuComponent::menuDepthInc();
    for ( auto it = entries_.begin(); it != entries_.end(); it++ ) {
        (*it)->menuDepthInc();
    } // for
} // Menu::menuDepthInc

ComponentIterator Menu::begin() { return iterator(this); }
ComponentIterator Menu::end()   { return iterator(); }

void Menu::print( ostream& sout ) const {
    sout << "\n" << menuDepth() << name() << ":";
} // Menu::print


// **********************************************************************
// Iterator
// **********************************************************************
Menu::iterator::iterator( Menu* menu ) : ComponentIterator{menu} {}
