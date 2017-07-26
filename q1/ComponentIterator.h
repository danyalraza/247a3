/*
 * Iterator used to traverse a MenuComponent.
 *
 *
 *  Created by Jo Atlee
 *  Last updated: 2017-05-19
 *  Copyright 2017 UW. All rights reserved.
 *
 */

#ifndef MC_ITERATOR_H
#define MC_ITERATOR_H

#include <stack>
#include <iterator>
#include "MenuComponent.h"


class ComponentIterator : public std::iterator< std::forward_iterator_tag, MenuComponent* > {
    friend bool operator== ( const ComponentIterator&, const ComponentIterator& );
    friend void operator++( ComponentIterator& );
    friend void operator++( ComponentIterator&, int );

  public:
    ComponentIterator( MenuComponent * = nullptr );
    ~ComponentIterator();
    bool hasNext();
    ComponentIterator( const ComponentIterator& );
    MenuComponent* operator->() const;          // Returns the current MenuComponent the iterator is on
    MenuComponent* operator* () const;          // Returns the current MenuComponent the iterator is on
    void begin();                   // Resets the iterator to the beginning

  private:
    MenuComponent* components_;
    struct IterNode {
      MenuComponent* node_;
      int cursor_;
      IterNode(MenuComponent* m);
    }
    stack<IterNode*> istack_;
};

bool operator==( const ComponentIterator&, const ComponentIterator& );
bool operator!=( const ComponentIterator&, const ComponentIterator& );
void operator++( ComponentIterator& );
void operator++( ComponentIterator&, int );


#endif
