/*
 * The Abstract Base Class for the Composite design pattern.
 *
 *
 *  Created by Jo Atlee
 *  Last updated: 2017-05-18
 *  Copyright 2017 UW. All rights reserved.
 *
 */
#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include <string>

class ComponentIterator;

class MenuComponent {
  public:
    friend std::ostream& operator<<( std::ostream&, const MenuComponent* );

    // Exception to throw if container operation is called on a leaf node.
    class InvalidOp {};

    // Constructor and destructor; destructor is useful in subclasses to clean up iterator.
    MenuComponent( const std::string & );
    virtual ~MenuComponent();
    
    // Leaf-only operations.
    virtual bool isVeggie() const;         // Is the menu item vegetarian?
    virtual float price() const;           // What is the price?
    virtual void priceIs( float );         // Set the price of the item.
    virtual int calories() const;          // How many calories?
    virtual void caloriesIs( int );        // Modify the number of calories.
    
    // Component-only operations.
    virtual void add( MenuComponent* );        // Add a MenuItem or subMenu to a Menu.
    virtual void remove( std::string );        // Removes a MenuItem or subMenu from a Menu; deletes it if found.
    virtual int numChildren() const;           // Returns the number of children in the Menu.
    virtual MenuComponent* getChild(int) const;// Returns the i-th child of the Menu.
    
    // Shared operations.
    std::string name() const;                  // Return name of Menu or MenuItem.
    std::string menuDepth() const;             // Depth of menu component in composite structure (used to indent the element when printing).
    virtual void menuDepthInc();               // Increments the depth of the MenuComponent.
    virtual int size() const;                  // Returns number of elements in MenuComponent, including all descendents and itself.
    virtual ComponentIterator begin() = 0;     // Return an iterator set to the beginning.
    virtual ComponentIterator end() = 0;       // Return an iterator set to point past the end.

  protected:
    virtual void print( std::ostream& ) const = 0;

  private:
    std::string name_;                         // Name of the MenuComponent.
    std::string menuDepth_;                    // Indentation string.
};

std::ostream& operator<< ( std::ostream&, const MenuComponent* );

#endif
