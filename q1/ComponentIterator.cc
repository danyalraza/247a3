#include "ComponentIterator.h"
#include "MenuComponent.h"
using namespace std;

#include <stack>
#include <iterator>
#include "ComponentIterator.h"
#include "MenuComponent.h"

using namespace std;

ComponentIterator::ComponentIterator(MenuComponent *menuComponent /* = 0 */) :
        istack_(stack<IterNode*>()) {
    if (menuComponent != NULL) {
        istack_.push(new IterNode(menuComponent, 0));
    }
}

ComponentIterator::~ComponentIterator() {}

ComponentIterator::IterNode::IterNode(MenuComponent *menuComponent, int cursor) :
        node_(menuComponent), cursor_(cursor) {}

/**
 * Check if stack contains an iterator that has not retrieved all children
 * of its respective node.
 */
bool ComponentIterator::hasNext() {
    while (!istack_.empty()) {
        ComponentIterator::IterNode *top = istack_.top();
        if (top->cursor_ < top->node_->numChildren()) {
            return true;
        }
        istack_.pop();
        delete top;
    }

    return false;
}

MenuComponent* ComponentIterator::operator->() const {
    if (istack_.size() == 0) {
        return NULL;
    } else {
        return istack_.top()->node_;
    }
}

MenuComponent* ComponentIterator::operator*() const {
    return istack_.top()->node_;
}

/**
 * Stacks are equal if:
 *  1) Size = 0
 *  2) Size != 0 but same top component
 */
bool operator==(const ComponentIterator &it1, const ComponentIterator &it2) {
    if (it1.istack_.size() == 0 && it1.istack_.size() == 0) {
        return true;
    } else if (it1.istack_.size() != 0 && it2.istack_.size() != 0 && it1.istack_.top() == it2.istack_.top()) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const ComponentIterator &it1, const ComponentIterator &it2) {
    return !(it1 == it2);
}

/**
 * Preorder iteration
 */
void operator++(ComponentIterator &it) {
    if (!it.hasNext()) { // have cursors reached their limit?
        return;
    }

    ComponentIterator::IterNode *top = it.istack_.top();
    it.istack_.pop();

    // if cursor == -1, advance cursor and return node
    if (top->cursor_ == -1) {
        top->cursor_ += 1;
        it.istack_.push(top); // advance cursor to first child
        return;
    }

    // else, advance cursor AND create new cursor for child
    MenuComponent *elem = top->node_->getChild(top->cursor_);
    top->cursor_ += 1;
    it.istack_.push(top); // advance cursor to next child
    it.istack_.push(new ComponentIterator::IterNode(elem, -1)); // push new cursor
    ++it; // recurse
}

/**
 * Post
 */
void operator++(ComponentIterator &it, int i) {
    ++it;
}


//
// ComponentIterator::ComponentIterator(MenuComponent *m /* = 0 */) :
//         istack_(stack<IterNode*>()), components_{m} {
//     if (m != nullptr) {
//         istack_.push(new IterNode(m, 0));
//     }
// }
//
// ComponentIterator::IterNode::IterNode(MenuComponent *m, int i) : cursor_{i}, node_{m} {}
//
// bool ComponentIterator::hasNext() {
//   while ( !istack_.empty() ) {
//     IterNode *top = istack_.top();
//     if ( top->cursor_ < top->node_->size() ) {
//       return true;
//     }
//     istack_.pop();
//     delete top;
//   }
//   return false;
// }
//
// void ComponentIterator::begin() {
//   while ( !istack_.empty() ) {
//     delete istack_.top();
//     istack_.pop();
//   }
//   istack_.push( new IterNode( components_, 0 ) );
// }
//
// void operator++(ComponentIterator &iter) {
//     if (!iter.hasNext()) {
//         return;
//     }
//     ComponentIterator::IterNode *top = iter.istack_.top();
//     iter.istack_.pop();
//     if (top->cursor_ == -1) {
//         top->cursor_ += 1;
//         iter.istack_.push(top);
//         return;
//     }
//     MenuComponent *elem = top->node_->getChild(top->cursor_);
//     top->cursor_ += 1;
//     iter.istack_.push(top);
//     iter.istack_.push(new ComponentIterator::IterNode(elem, -1));
//     ++iter;
// }
//
// ComponentIterator::~ComponentIterator() {}
//
// MenuComponent* ComponentIterator::operator->() const {
//     if (istack_.size() == 0) {  return nullptr; }
//     else { return istack_.top()->node_; }
// }
//
// MenuComponent* ComponentIterator::operator*() const {
//   return istack_.top()->node_;
// }
//
// bool operator==(const ComponentIterator &iter1, const ComponentIterator &iter2) {
//     if (iter1.istack_.size() == 0 && iter1.istack_.size() == 0) {
//         return true;
//     } else if (iter1.istack_.top() == iter2.istack_.top() && iter1.istack_.size() != 0 && iter2.istack_.size() != 0) {
//         return true;
//     } else {
//         return false;
//     }
// }
//
// bool operator!=(const ComponentIterator &iter1, const ComponentIterator &iter2) {
//     return !(iter1 == iter2);
// }
//
// void operator++( ComponentIterator& iter, int num) {
//   ++iter;
// }
