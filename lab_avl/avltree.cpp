/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* R=t->right;
    t->right=R->left;   
    R->left=t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = R;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* L=t->left;
    t->left=L->right;
    L->right=t;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = L;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==NULL){return;}
    int balanceFactor = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if(balanceFactor == -2){
        int leftBalanceFactor = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(leftBalanceFactor <0){
            rotateRight(subtree);
            subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        }else{
            rotateLeftRight(subtree);
        }
    }
    else if(balanceFactor == 2){
        int rightBalanceFactor = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(rightBalanceFactor >0){
            rotateLeft(subtree);
        }else{
            rotateRightLeft(subtree);
        }
    }
    else if(balanceFactor == -1 || balanceFactor == 1 || balanceFactor == 0){
        subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        return;
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        Node* temp=new Node(key, value);
        subtree =temp;
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
        rebalance(subtree);
    }
    else if(key > subtree->key){
        insert(subtree->right, key, value);
        rebalance(subtree);
    }
    else{
        subtree->value = value;
        return;
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL){
        return;
    }
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, temp->key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree;
            if(subtree->left != NULL){
                *subtree = *subtree->left;
                delete temp->left;  
                temp->left = NULL;
            }
            else{
                *subtree = *subtree->right;
                delete temp->right;
                temp->right = NULL;
            }
        }
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    rebalance(subtree);
}
