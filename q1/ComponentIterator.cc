#include "ComponentIterator.h"
#include "MenuComponent.h"
#include <iostream>
using namespace std;

ComponentIterator::ComponentIterator(MenuComponent *m) : istack_(stack<IterNode*>()), components_{m} {
    if (m != nullptr) {
        IterNode* a = new IterNode(m);
        a->cursor_ = 0;
        istack_.push(a);
        cout << "creating iterator worked" << endl;
    }

}

ComponentIterator::IterNode::IterNode(MenuComponent *m) : cursor_{-1}, node_{m} {}

bool ComponentIterator::hasNext() {
  while ( !istack_.empty() ) {
    IterNode *top = istack_.top();
    if ( top->cursor_ < top->node_->numChildren() ) {
      return true;
    }
    istack_.pop();
    delete top;
  }
  return false;
}

void ComponentIterator::begin() {
  cout << "starting to call begin" << endl;
  while ( !istack_.empty() ) {
    delete istack_.top();
    istack_.pop();
  }
  IterNode* a = new IterNode(components_);
  a->cursor_ = 0;
  istack_.push(a);
  cout << "calling begin worked" << endl;
}

void operator++(ComponentIterator &iter) {
    cout << "calling ++ iterator" << endl;
    if (!iter.hasNext()) {
        return;
    }
    ComponentIterator::IterNode *top = iter.istack_.top();
    iter.istack_.pop();
    if (top->cursor_ == -1) {
        top->cursor_ += 1;
        iter.istack_.push(top);
        return;
    }
    MenuComponent *elem = top->node_->getChild(top->cursor_);
    top->cursor_ += 1;
    iter.istack_.push(top);
    iter.istack_.push(new ComponentIterator::IterNode(elem));
    ++iter;
}

ComponentIterator::~ComponentIterator() {}

MenuComponent* ComponentIterator::operator->() const {
    cout << "calling -> operator" << endl;
    if (istack_.size() == 0) {  return nullptr; }
    else { return istack_.top()->node_; }
}

MenuComponent* ComponentIterator::operator*() const {
  cout << "calling * operator" << endl;
  return istack_.top()->node_;
}

bool operator==(const ComponentIterator &iter1, const ComponentIterator &iter2) {
  cout << "calling == operator" << endl;
    if (iter1.istack_.size() == 0 && iter1.istack_.size() == 0) {
        return true;
    } else if (iter1.istack_.size() != 0 && iter2.istack_.size() != 0 && iter1.istack_.top() == iter2.istack_.top() ) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const ComponentIterator &iter1, const ComponentIterator &iter2) {
    return !(iter1 == iter2);
}

void operator++( ComponentIterator& iter, int num) {
  ++iter;
}
