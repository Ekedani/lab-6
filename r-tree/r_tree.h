#include <vector>
#include "../data-struct/triangle.h"
#include <cfloat>

struct TriangleLeaf {
    Triangle *triangle;
    Prism MBP;

    explicit TriangleLeaf(Triangle *t);
    void print(){
        triangle->print();
    }
    void printMBR(){
        MBP.toConsole();
    }
};

struct Node {
    Node *parentNode;
    Prism *MBP;
    std::vector<TriangleLeaf *> objects;
    std::vector<Node *> nodes;

    bool isInsideParentNode(){
        bool result = false;
        if(this->parentNode == nullptr){
            return true;
        }
        else{
            for (auto node: this->parentNode->nodes) {
                if(node == this){
                    return true;
                }
            }
        }
        return result;
    }

    Node();

    bool isLeaf() const;

    void updateMBP();
};


class rTree {
private:
    //Корень дерева
    Node *root;
    int numOfInserted;

    //Минимальное и максимальное количество элементов в узле
    const static int minCount = 6;
    const static int maxCount = 16;

    //Сортировки по оси OX
    static int sortObjectsByAxis(const void *a, const void *b);

    static int sortNodesByAxis(const void *a, const void *b);

    //Разделение узлов
    void splitLeafNode(Node *curNode, TriangleLeaf *curObj);

    void splitNotLeafNode(Node *curNode, Node *insertedNode);

    //Вспомогательный метод поиска
    static void findObjectsUsingRay(Line curRay, Node *curNode, std::vector<Triangle *> &result);

    //Выбор поддерева
    Node *chooseSubtree(const TriangleLeaf &newTriangle);

    Node *chooseSubtree(Node *start, const TriangleLeaf &newTriangle);

public:
    void debugTreeParse(){
        bool correct = true;
        int counter = 0;
        if(root->isLeaf()){
            for(auto obj : root->objects){
                correct = correct & root->MBP->isInside(*obj->triangle->firstVertex);
                correct = correct & root->MBP->isInside(*obj->triangle->secondVertex);
                correct = correct & root->MBP->isInside(*obj->triangle->thirdVertex);
            }
            counter += root->objects.size();
        }
        else{
            for (auto node : root->nodes) {
                correct = correct & root->MBP->isInside(*node->MBP->getFirstPoint());
                correct = correct & root->MBP->isInside(*node->MBP->getSecondPoint());
                recursiveTreeParse(counter, node, correct);
            }
        }
        cout << "Total num of objects: " << counter << '\n';
        cout << "correct: " << correct << endl;
    }

    void recursiveTreeParse(int &count, Node* curNode, bool &correct){
        if(curNode->isLeaf()){
            for(auto obj : curNode->objects){
                correct = correct & curNode->MBP->isInside(*obj->triangle->firstVertex);
                correct = correct & curNode->MBP->isInside(*obj->triangle->secondVertex);
                correct = correct & curNode->MBP->isInside(*obj->triangle->thirdVertex);
            }
            count += curNode->objects.size();
        }
        else{
            for (auto node : curNode->nodes) {
                correct = correct & curNode->MBP->isInside(*node->MBP->getFirstPoint());
                correct = correct & curNode->MBP->isInside(*node->MBP->getSecondPoint());
                correct = correct & curNode->isInsideParentNode();
                recursiveTreeParse(count, node, correct);
            }
        }
    }

    //Конструктор
    rTree();

    //Вставка треугольника в дерево
    void insertTriangle(Triangle *curTriangle);

    //Метод поиска по лучу
    std::vector<Triangle *> findObjectsUsingRay(Line curRay);
};



