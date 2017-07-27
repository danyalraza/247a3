#include <string>
#include "MenuComponent.h"

MenuComponent::MenuComponent( const std::string & name ) : name_{name}, menuDepth_{ "" } {}
MenuComponent::~MenuComponent() {}

void           MenuComponent::menuDepthInc ()       { menuDepth_ = "\t" + menuDepth(); }
bool           MenuComponent::isVeggie() const      { return false; } 
float          MenuComponent::price() const         { return 0; } 
void           MenuComponent::priceIs( float )      {} 
int            MenuComponent::calories() const      { return 0; } 
void           MenuComponent::caloriesIs( int )     {} 
void           MenuComponent::add( MenuComponent* ) { throw InvalidOp(); } 
void           MenuComponent::remove( std::string ) { throw InvalidOp(); } 
MenuComponent* MenuComponent::getChild(int) const   { return nullptr; }
int            MenuComponent::size() const          { return 1; }
int            MenuComponent::numChildren() const   { return 0; } 
std::string    MenuComponent::name() const          { return name_; } 
std::string    MenuComponent::menuDepth() const     { return menuDepth_; }  

std::ostream & operator<<( std::ostream & sout, const MenuComponent* mc ) {
    mc->print( sout );
    return sout;
} // operator<<
