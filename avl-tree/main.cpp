#include <iostream>


class Node{
public:
    Node* left;
    Node* right;
    int key = NULL;
    unsigned int height;

    unsigned int GetHeight(const Node* node)
    {
        return node ? node->height : 0;
    }    


    Node* Insert(Node* node, const int k)
    {
        if (!node) return new Node(k);

        if (k < node->key) 
        {
            left = Insert(node->left, k);
        }
        else 
        {
            node->right = Insert(node->right, k);
        }

        return BringBalance(node);
    }


    Node* GetMin(Node* node)
    {
        return node->left ? GetMin(node->left) : node;
    }


    Node* Remove(Node* node, const int k)
    {
        if (!node) return 0;

        if (k < node->key) 
        {
            node->left = Remove(node->left, k);
        }
        else if (k > node->key) 
        {
            node->right = Remove(node->right, k);	
        }
        else
        {
            Node* l = node->left;
            Node* r = node->right;
            
            delete node;
            
            if (!r) return l;

            Node* min = GetMin(r);
            min->right = MoveMin(r);
            min->left = l;

            return BringBalance(min);
        }
        return BringBalance(node);
    }


    void Display(const Node* node)
    {
        if (node == 0) return;

        Display(node->left);

        std::cout << node->key << " ";

        Display(node->right);
    }

    Node(int k) {key = k; left = right = 0; height = 1;}

private:

    int BalanceStatus(const Node* node)
    {
        return (int)GetHeight(node->right) - (int)GetHeight(node->left);
    }


    void FixHeight(Node* node)
    {
        unsigned int h1 = GetHeight(node->left);
        unsigned int h2 = GetHeight(node->right);

        node->height = (h1 > h2 ? h1 : h2) + 1;
    }


    Node* RotateLeft(Node* node)
    {
        Node* rotated = node->right;

        node->right = rotated->left;
        rotated->left = node;

        FixHeight(node);
        FixHeight(rotated);
        return rotated;
    }


    Node* RotateRight(Node* node)
    {
        Node* rotated = node->left;

        node->left = rotated->right;
        rotated->right = node;

        FixHeight(node);
        FixHeight(rotated);
        return rotated;
    }


    Node* BringBalance(Node* node)
    {
        FixHeight(node);

        if (BalanceStatus(node) >= 2)
        {
            if (BalanceStatus(node->right) < 0)
                node->right = RotateRight(node->right);
            return RotateLeft(node);
        }

        if (BalanceStatus(node) <= -2)
        {
            if (BalanceStatus(node->left) > 0)
                node->left = RotateLeft(node->left);
            return RotateRight(node);
        }
        return node;
    }


    Node* MoveMin(Node* node)
    {
        Node* l = node->left;
        Node* r = node->right;

        if (!l)
            return r;

        l = MoveMin(l);

        return BringBalance(node);
    }
};


int main()
{
    Node* node = new Node(10);

    for (int i = 0; i < 5; ++i)
        node = node->Insert(node, rand());

    node = node->Remove(node, 10);

    node->Display(node);

    return 0;
}
