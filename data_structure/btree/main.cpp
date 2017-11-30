// deepaknettem@gmail.com,
// code released in public domain 
// a simple b-tree implementation for learning purposes (only insertion is implemented). 
// this uses the double pass insertion, ie find for the leaf, insert and then propagate splits upwards.

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>

int MAXKEYS = 5; // we split at max keys. 
struct Node : std::enable_shared_from_this<Node>
{
    Node(bool isLeaf = false)
    : _isLeaf(isLeaf),
      _parent(nullptr)
    {   
    }
    
    void splitNode(std::shared_ptr<Node>& siblingNode /*outParam*/, int& median /*outParam*/)
    {
        size_t medianOffset = MAXKEYS / 2;
        median = _keys[medianOffset];
        
        std::cout << "Splitting Node, New Median: " << median << " medianOffset: " << medianOffset << " isLeaf: " << (_isLeaf == true ? "true" : "false") << std::endl;
        siblingNode.reset(new Node(_isLeaf));
        
        // set sibling node's parent pointer
        siblingNode->_parent = _parent;
        
        if (!_isLeaf)
        {
            siblingNode->_children.assign(_children.begin() + medianOffset + 1, _children.end());
            _children.erase(_children.begin() + medianOffset + 1, _children.end());
        }
        
        // assign the keys after median to sibling.
        (siblingNode->_keys).assign(_keys.begin() + medianOffset + 1, _keys.end());
        // erase the keys median onwards
        _keys.erase(_keys.begin() + medianOffset, _keys.end());
    }
    
    // called when the node is full.
    Node* propagateUp(int median, std::shared_ptr<Node>& siblingNode, bool& isHeightIncreased)
    {
        // check if tree height to be increased.
        if (_parent == nullptr)
        {    
            // this is the root, and height of tree needs to increase by 1.
            Node* newRoot = new Node(false);
              
            // set children for new root
            (newRoot->_children).push_back(shared_from_this());
            (newRoot->_children).push_back(siblingNode);   
            (newRoot->_keys).push_back(median);
            
            // set parent pointers
            _parent = newRoot;
            siblingNode->_parent = newRoot;
            
            isHeightIncreased = true;
            return newRoot;
        }
        else
        {
            return _parent->insert(median, this, siblingNode, isHeightIncreased);
        }     
    }
    
    // invoked by a child of this node.
    Node* insert(int median, Node* oldChild, std::shared_ptr<Node> rightSiblingOfChildAfterSplit, bool& isHeightIncreased)
    {
        assert(!_isLeaf);
        assert(_keys.size() > 0);
       
        auto iter = std::upper_bound(_keys.begin(), _keys.end(), median); 
        auto position = std::distance(_keys.begin(), iter);
        
        _keys.insert(iter, median);
        
        _children.insert(_children.begin() + position + 1, rightSiblingOfChildAfterSplit);
        assert(_children[position].get() == oldChild);  
        // the +1 is important because the original child node is already present, and the new child will come after the existing child.     
        
        // Now check if the node size was max, then split, and insert recursively.
        // check if node is full
        if (_keys.size() == MAXKEYS)
        {
            std::shared_ptr<Node> siblingNode;
            int median;
            splitNode(siblingNode, median);
            return propagateUp(median, siblingNode, isHeightIncreased);         
        }
        else
        {
            return this;
        }
    }
    
    Node* find(int val)
    {
        if (_isLeaf)
        {
            return this;
        }
        else
        {
            // call find on a correct child.
            auto position = std::distance(_keys.begin(), std::upper_bound(_keys.begin(), _keys.end(), val));
            return _children[position]->find(val);
        }
    }
    
    // this function is called only on the leaf node.
    // returns the highest node into which an element was inserted in the tree.
    Node* insert(int val, bool& isHeightIncreased)
    {
        std::cout << "Inserting element " << val << std::endl;
        assert(_isLeaf);
        if (_keys.size() == 0)
        {
            _keys.push_back(val);
            return this;        
        }
        
        assert(_keys.size() < MAXKEYS);
        
        // insert at proper position.
        auto iter = std::upper_bound(_keys.begin(), _keys.end(), val);
        _keys.insert(iter, val);
     
        // check if node is full
        if (_keys.size() == MAXKEYS)
        {
            std::shared_ptr<Node> siblingNode;
            int median;
            splitNode(siblingNode, median);
            return propagateUp(median, siblingNode, isHeightIncreased); 
        }
        else
        {
            return this;
        }
    }

    void printNode(bool recursive = false)
    {
        std::cout << "--------Printing Node:------" << std::endl;
        std::cout << "Number of Keys: " << _keys.size() << "    " << "Number of Children " << _children.size() << std::endl;
        
        std::cout << "Node Keys: ";
        
        if (_isLeaf)
        {
            std::cout << "LEAF NODE" << std::endl;            
            for (const auto& key : _keys) { std::cout << key << "   " << std::endl; }
            std::cout << "---------End Printing Node ----------" << std::endl;
            return;
        }
        else
        {
            std::cout << "INTERNAL NODE" << std::endl;
            for (const auto& key : _keys) { std::cout << key << "   " << std::endl; }
            std::cout << "---------End Printing Node ----------" << std::endl;
        }
        
        if (recursive)
        {        
            for(const auto& child : _children)
            {
                child->printNode();
            }
        }
    }    

    bool _isLeaf;
    Node* _parent;
    std::vector<int> _keys;
    std::vector<std::shared_ptr<Node>> _children;
};

struct Tree
{
    Tree()
    {
        _root.reset(new Node(true));
    }
    
    void print()
    {
        _root->printNode();
        // print in depth first order
        for(const auto& child : _root->_children)
        {
            child->printNode(true /*printRecursive*/);
        }
    }
    
    void insert(int val)
    {
        Node* leafNode = _root->find(val);
        bool isHeightIncreased = false;
        Node* insertNode = leafNode->insert(val, isHeightIncreased);
               
        if (isHeightIncreased)
        {
            _root.reset(insertNode);
        }
                
        std::cout << std::endl;
        std::cout << "--------------printing tree--------------" << std::endl;
        print();
        std::cout << "---------------end print tree-----------" << std::endl;
        std::cout << std::endl;
    }
    
    std::shared_ptr<Node> _root;
};

int main()
{

    std::shared_ptr<Tree> tree(new Tree());
    tree->insert(20);
    tree->insert(30);
    tree->insert(40);
    tree->insert(50);
    tree->insert(60);
    
    tree->insert(10);
    tree->insert(12);
    tree->insert(14);
    tree->insert(16);
    
    tree->insert(22);
    tree->insert(24);
    tree->insert(26);
    tree->insert(28);
    tree->insert(29);
    tree->insert(4);
    tree->insert(6);
    tree->insert(8);
    std::cout << "Hello, world!\n";
}
