/*
 * Represents the leaf item in the Composite design pattern.
 *
 *
 *  Created by Jo Atlee
 *  Last updated: 2017-05-18
 *  Copyright 2017 UW. All rights reserved.
 *
 */

#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <iostream>
#include <string>
#include "ComponentIterator.h"
#include "MenuComponent.h"

class MenuItem : public MenuComponent {
  public:
    
    // ITERATOR
    //
    // ABS FUNCTION:  iterator::cursor_ == iterator:: entry_ iff iteration has not visited MenuItem node yet

    class iterator;
    friend class iterator;

    class iterator : public ComponentIterator {
      public:
        iterator( MenuItem* mi = 0 );
    };
    
    // constructor
    MenuItem( const std::string &, float, int, bool );
    virtual ~MenuItem() {}
    
    // Implement leaf operations.
    virtual bool isVeggie() const override;
    virtual float price() const override;
    virtual void priceIs( float p ) override;
    virtual int calories() const override;
    virtual void caloriesIs( int c ) override;
    
    // Implement shared operations.
    virtual ComponentIterator begin() override;
    virtual ComponentIterator end() override;
    
protected:
    virtual void print ( std::ostream& ) const override;

private:
    float price_;                      // Price of the MenuItem
    int calories_;                     // Calories of the MenuItem
    bool isVeggie_;                    // Is it vegetarian?
};

#endif
