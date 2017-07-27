/*
 * Represents the container portion of the Composite design pattern.
 *
 *
 *  Created by Jo Atlee
 *  Last updated: 2017-05-18
 *  Copyright 2017 UW. All rights reserved.
 *
 */

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include "MenuComponent.h"
#include "ComponentIterator.h"

class Menu : public MenuComponent {
  public:

    class iterator : public ComponentIterator { // iterator
      public:
        iterator( Menu* m = nullptr );
    };

    Menu ( const std::string & );
    virtual ~Menu();

    // Implement composite operations.
    virtual void add( MenuComponent* newEntry ) override;
    virtual void remove( std::string name ) override;
    virtual int numChildren() const override;
    virtual MenuComponent* getChild(int i) const override;

    // Implement shared operations.
    virtual void menuDepthInc() override;
    virtual int size() const override;
    virtual ComponentIterator begin() override;
    virtual ComponentIterator end() override;

  protected:
    virtual void print( std::ostream& ) const override;

  private:
    std::vector<MenuComponent*> entries_;
};

#endif
