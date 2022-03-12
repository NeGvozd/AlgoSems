#include <iostream>

class Node {
    Node* _left;
    Node* _right;
    int _value = NULL;
    unsigned int _height;

    int BalanceStatus(Node* node)
    {
        return (int)getHeight(node->getRight()) - (int)getHeight(node->getLeft());
    }

    void FixHeight(Node* node)
    {
        unsigned int h1 = getHeight(node->getLeft());
        unsigned int h2 = getHeight(node->getRight());

        node->_height = (h1>h2 ? h1:h2) + 1;
    }

    Node* RotateLeft(Node* node)
    {
        Node* rotated = node->getRight();

        node->_right = rotated->getLeft();
        rotated->_left = node;

        FixHeight(node);
        FixHeight(rotated);

        return rotated;
    }

    Node* RotateRight(Node* node)
    {
        Node* rotated = node->getLeft();

        node->_left = rotated->getRight();
        rotated->_right = node;

        FixHeight(node);
        FixHeight(rotated);

        return rotated;
    }

    Node* Balance(Node* node)
    {
        FixHeight(node);

        if (BalanceStatus(node) >= 2)
        {
            if (BalanceStatus(node->getRight()) < 0)
                node->_right = RotateRight(node->getRight());
        }

        if (BalanceStatus(node) <= -2)
        {
            if (BalanceStatus(node->getLeft()) > 0)
                node->_left = RotateLeft(node->getLeft());
        }

        return node;
    }

    Node* MoveMin(Node* node)
    {
        Node* l = node->getLeft();
        Node* r = node->getRight();

        if (!l) return r;

        l = MoveMin(l);

        return Balance(node);
    }

public:
    Node* getLeft() { return _left; }
    Node* getRight() { return _right; }
    int getValue() { return _value; }

    unsigned int getHeight(Node* node)
    {
        return node ? node->_height : 0;
    }

    Node* getMin(Node* node)
    {
        return node->getLeft() ? getMin(node->getLeft()) : node;
    }

    Node* Insert(Node* node, const int v)
    {
        if (!node) return new Node(v);

        if (v < node->getValue())
            _left = node->getLeft()->Insert(node->getLeft(), v);
        else
            _right = node->getRight()->Insert(node->getRight(), v);

        return Balance(node);
    }

    Node* Remove(Node* node, const int& v)
    {
        if (!node) return 0;

        if (v < node->getValue())
            node->_left = node->getLeft()->Remove(node->getLeft(), v);

        else if (v > node->getValue())
            node->_right = node->getRight()->Remove(node->getRight(), v);

        else
        {
            Node* l = node->getLeft();
            Node* r = node->getRight();

            delete node;

            if (!r) return l;

            Node* min = getMin(r);
            min->_right = MoveMin(r);
            min->_left = l;

            return Balance(min);
        }
        return Balance(node);
    }


    void Display(Node* node)
    {
        if (node == 0) return;

        Display(node->getLeft());

        std::cout << node->getValue() << " ";

        Display(node->getRight());
    }

    Node(int v) { _value = v; _left = _right = NULL; _height = 1; }
};


int main()
{
    Node* node = new Node(10);

    for (int i=0; i<5; ++i)
        node = node->Insert(node, rand());

    node->Display(node);
    std::cout << std::endl;

    node = node->Remove(node, 10);

    node->Display(node);

    return 0;
}
