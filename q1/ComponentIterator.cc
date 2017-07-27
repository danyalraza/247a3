#include "ComponentIterator.h"
#include "MenuComponent.h"
using namespace std;

#include <stack>
#include <iterator>
#include "ComponentIterator.h"
#include "MenuComponent.h"

using namespace std;


ComponentIterator::ComponentIterator(MenuComponent *m) : istack_(stack<IterNode*>()), components_{m} {
    if (m != nullptr) {
        IterNode* a = new IterNode(m);
        a->cursor_ = 0;
        istack_.push(a);
    }
}

ComponentIterator::IterNode::IterNode(MenuComponent *m) : cursor_{-1}, node_{m} {}

bool ComponentIterator::hasNext() {
  while ( !istack_.empty() ) {
    IterNode *top = istack_.top();
    if ( top->cursor_ < top->node_->size() ) {
      return true;
    }
    istack_.pop();
    delete top;
  }
  return false;
}

void ComponentIterator::begin() {
  while ( !istack_.empty() ) {
    delete istack_.top();
    istack_.pop();
  }
  IterNode* a = new IterNode(components_);
  a->cursor_ = 0;
  istack_.push(a);
}

void operator++(ComponentIterator &iter) {
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
    if (istack_.size() == 0) {  return nullptr; }
    else { return istack_.top()->node_; }
}

MenuComponent* ComponentIterator::operator*() const {
  return istack_.top()->node_;
}

bool operator==(const ComponentIterator &iter1, const ComponentIterator &iter2) {
    if (iter1.istack_.size() == 0 && iter1.istack_.size() == 0) {
        return true;
    } else if (iter1.istack_.top() == iter2.istack_.top() && iter1.istack_.size() != 0 && iter2.istack_.size() != 0) {
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
