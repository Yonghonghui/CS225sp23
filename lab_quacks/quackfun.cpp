/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include <queue>
#include <stack>
namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.size() == 0) {
        return 0; 
    }
    T value_ = s.top();
    s.pop();
    T sum_=value_+ sum(s);;
    s.push(value_);
    return sum_;

    // Your code here
     // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    unsigned count=1;
    while(q.size()!=0){
        unsigned count_=0;
        if(count%2!=0){
            for(unsigned i=0;i<count;i++){
                q2.push(q.front());
                q.pop();
                if(q.size()==0){break;}
            }
            count++;
        }
        else{
            for(unsigned i=0;i<count;i++){
                s.push(q.front());
                q.pop();
                count_++;
                if(q.size()==0){break;}
            }
            for(unsigned i=0;i<count_;i++){
                q2.push(s.top());
                s.pop();
            }
             count++;
        }
     }
     while(q2.size()!=0){
         q.push(q2.front());
         q2.pop();
     }
    
    

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = 1;//initialize the retval
    if (s.size()==0) { return 1; }//when s has all popped out,stop
    T value1=s.top(); // current value in the stack
    s.pop();//pop the value on the top of the stack until the stack is empty
    retval = verifySame(s, q);//recurse the function 
    T value2=q.front(); // current value in the queue
    q.pop();//pop the front value in the queue
    q.push(value2);//push the value back to the end of the queue
    s.push(value1);//push the value back to the top of the stack
    retval=(value1 == value2) && retval;//mutiply the judgement with the current retval
    return retval;//return the boolean value
}
}