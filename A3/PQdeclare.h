#ifndef PQ_H
#define PQ_H

// PQ class
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, priorities ) --> constructs a new queue with a given set of task IDs and priorities 
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p 
// ID findMin( )  --> Return a task ID with smallest priority, without removing it 
// ID deleteMin( )   --> Remove and return a task ID with smallest priority 
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue 
// void makeEmpty( )  --> Remove all task IDs (and their priorities)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
// ID is the type of task IDs to be used; the type must be Comparable (i.e., have < defined), so IDs can be AVL Tree keys.
class PQ
{

  public:

    // Constructor
    // Initializes a new empty PQ
    PQ() 

    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and priorities  
    //      priority[i] is the priority for ID task[i] 
    PQ( const std::vector<ID> & tasks, const std::vector<int> & priorities ) 
						     
    // Emptiness check 
    bool isEmpty( ) const

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin() 

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() const

    // Insert ID x with priority p.
    void insert( const ID & x, int p )

    // Update the priority of ID x to p
    //    Inserts x with p if s not already in the queue
    void updatePriority( const ID & x, int p ) 

    // Return the number of task IDs in the queue
    int size() const 

    // Delete all IDs from the PQ
    void makeEmpty( )

};
#endif
