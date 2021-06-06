#include <vector>
#include "prism.h"

struct TriangleLeaf{
    Triangle* triangle;
    Prism MBP;
};

struct Node{
    Node *parentNode;
    Prism MBP;
    std::vector<TriangleLeaf*> objects;
    std::vector<Node*> nodes;

    Node(){
        parentNode = nullptr;
    }

    bool isLeaf() const{
        return nodes.empty();
    }

    void updateMBP(){
        //если есть обьекты
        //если есть дочерние ноды
    }
};


class rTree {
private:
    //Корень дерева
    Node *root;

    //Минимальное и максимальное количество элементов в узле
    const static int minCount = 6;
    const static int maxCount = 16;
    
public:

    rTree(){
        root = new Node;
        root->parentNode = nullptr;
        root->updateMBP();
    }

    //TODO: Переписать методы из старого R дерева
    Node* chooseSubtree(Triangle newTriangle){

    }
    Node* chooseSubtree(Node* start, Triangle newTriangle){

    }

    void insertTriangle(Triangle& curTriangle){

    }
};



