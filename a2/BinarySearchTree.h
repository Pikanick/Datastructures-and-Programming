#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// void displayTree()     --> Print the tree structure
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const //inorder travesal 
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Print the tree structure in sorted order.
     */
    void displayTree( ostream & out = cout ) const //preorder travesal 
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            displayTree( root, 0, out );
    }

    /**
     * Print the tree structure in sorted order.
     */
    void displayLinks( ostream & out = cout ) const //preorder travesal  only does the root. otherwise calls private dislplay links
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            //displayLinks( root, "",false, out );
            displayLinks( root, 0, out );
    }
    int height() 
    {
         if (((root->left)==nullptr)&&((root->right)==nullptr))
        {
            return 0;
        }
        else if (((root->left)==nullptr)&&((root->right)!=nullptr))
        {
            return 1+height(root->right);
        }
        else if(((root->right)==nullptr)&&((root->left)!=nullptr))
        {
             return 1+height(root->left);
        }
        else
        {
            return max(height(root->left), height(root->right)) + 1;
        }
    }

    int depth( const Comparable & x ) const
        {
            depth( x, root );
        }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    

  private:
    struct BinaryNode
    {
        Comparable element; // int data i think 
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else // basically: (t->element == x)
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void displayTree( BinaryNode *t, int depth, ostream & out ) const
    {
        const int SHIFT = 4 ;
        if( t != nullptr )
        {
            for( int i = 0 ; i < SHIFT*depth ; i++ ){ out << " " ; }
            out << t->element << endl;
            displayTree( t->left, depth+1, out );
            displayTree( t->right, depth+1, out );
        }
    }

    /**
     * Print the subtree structure rooted at t in sorted order.
     */
    // void displayLinks( const BinaryNode *t, const string& branch, bool Left, ostream & out ) const //preorder travesal 
    // {
    //     if( t != nullptr )
    //     { 
    //         cout<<branch;
    //         cout<<(Left?"|---" : "|___");
    //         out << t->element << endl;
    //         displayLinks( t->left, branch+(Left?"|   " : "    "),true, out );
    //         displayLinks( t->right, branch+(Left?"|   " : "    "),false, out );
    //     }
    // }
    
    // Print the subtree structure rooted at t in sorted order with address of root, left and right children.
    void displayLinks( BinaryNode *t, int depth, ostream & out ) const
    {
        
        const int SHIFT = 4 ;
        if( t != nullptr )
        {
            for( int i = 0 ; i < SHIFT*depth ; i++ )
            { 
                out << " " ; 
            }
            
            out << t->element << ") @:" << t << "   " << "L:" << t->left << "   " << "R:" << t->right << endl;
            displayLinks( t->left, depth+1, out );
            displayLinks( t->right, depth+1, out );
            //cout<<"hello"<<endl;
            
        }
    }

    int height(BinaryNode *t) 
    {
        if (((t->left)==nullptr)&&((t->right)==nullptr))
        {
            return 0;
        }
        else if (((t->left)==nullptr)&&((t->right)!=nullptr))
        {
            return 1+height(t->right);
        }
        else if(((t->right)==nullptr)&&((t->left)!=nullptr))
        {
             return 1+height(t->left);
        }
        else
        {
            return max(height(t->left), height(t->right)) + 1;
        }
    }

    int depth( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
        {   
            return -1;
        }
        else if( x < t->element )
        {
            
            return depth( x, t->left )+1;
        }
        else if( t->element < x )
        {
            return depth( x, t->right )+1;
        }
        else // basically: (t->element == x)
        {
            return 0;    // Match
        }
    }


        // bool contains( const Comparable & x, BinaryNode *t ) const // Delete this
        // {
        //     if( t == nullptr )
        //         return false;
        //     else if( x < t->element )
        //         return contains( x, t->left );
        //     else if( t->element < x )
        //         return contains( x, t->right );
        //     else // basically: (t->element == x)
        //         return true;    // Match
        // }

     
       /* if(t != nullptr)
        {
            return max(findHeight(root->left), findHeight(root->right)) + 1;
            int lh = findHeight(t->left);
            int rh = findHeight(t->right);

            if (lh > rh) 
            {
                return lh + 1;
            } 
            
            else 
            {
                return rh + 1;
            }
        }
        else 
        {
            cout<<"leaf reached"<<endl;
            return 0;
        }
*/
    //}

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif