#include <vector>
#include "prism.h"
#include <cfloat>

struct TriangleLeaf {
    Triangle *triangle;
    Prism MBP;
    TriangleLeaf(Triangle *t){
        MBP = Prism();
        MBP = MBP.extend(*t->firstVertex);
        MBP = MBP.extend(*t->secondVertex);
        MBP = MBP.extend(*t->thirdVertex);
    }
};

struct Node {
    Node *parentNode;
    Prism MBP;
    std::vector<TriangleLeaf *> objects;
    std::vector<Node *> nodes;

    Node() {
        parentNode = nullptr;
    }

    bool isLeaf() const {
        return nodes.empty();
    }

    void updateMBP() {
        for (int i = 0; i < objects.size(); ++i) {
            MBP = MBP.extend(*objects[i]->MBP.getFirstPoint());
            MBP = MBP.extend(*objects[i]->MBP.getSecondPoint());
        }
        for (int i = 0; i < nodes.size(); ++i) {
            MBP = MBP.extend(*nodes[i]->MBP.getFirstPoint());
            MBP = MBP.extend(*nodes[i]->MBP.getSecondPoint());
        }
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

    rTree() {
        root = new Node;
        root->parentNode = nullptr;
        root->updateMBP();
    }

    //TODO: Переписать методы из старого R дерева
    Node *chooseSubtree(Triangle newTriangle) {
        return chooseSubtree(root, newTriangle);
    }

    Node *chooseSubtree(Node *start, Triangle newTriangle) {
        Node *chosen = nullptr;
        if (start->isLeaf()) {
            return start;
        } else {
            int index;
            //TODO: выбор по объему
            //Point point (new_place.longitude,new_place.latitude);
            double minimalMBPIncreasingVolume = DBL_MAX;
            //for (int i = 0; i < start->nodes.size(); ++i) {
            //    if (start->nodes[i]->MBP.HowMuchIncreasesTheVolume(point) < minimalMBPIncreasingVolume){
            //        minimalMBPIncreasingVolume = start->nodes[i]->MBP.HowMuchIncreasesTheVolume(point);
            //    }
            //}
            //double minimalVolume = DBL_MAX;
            //for (int i = 0; i < start->nodes.size(); ++i) {
            //    if (start->nodes[i]->MBP.HowMuchIncreasesTheVolume(point) == minimal_mbr_increasing_area){
            //        if (start->nodes[i]->MBP.volume() < minimalVolume) {
            //            minimalVolume = start->nodes[i]->MBP.volume();
            //            index = i;
            //        }
            //    }
            //}
            //chosen = start->nodes[index];
        }
        //return chooseSubtree(chosen, new_place);
    }

    void insertTriangle(Triangle &curTriangle) {
        Node *chosenNode = chooseSubtree(root, curTriangle);
        Triangle *ptrToTriangle = &curTriangle;

        //TODO: Создать ограничивающий параллелепипед и объект листка

        ////Если узел не переполнен
        //if(chosenNode->objects.size() < maxCount){
        //    chosenNode->objects.push_back(ptrToPlace);
        //    while(chosenNode != nullptr){
        //        chosenNode->updateMBR();
        //        chosenNode = chosenNode->parentNode;
        //    }
        //}
        //else{
        //    splitLeafNode(chosenNode, ptrToPlace);
        //}
    }

    //Методы поиска (Нижний, желательно, перенести в приватные)
    std::vector<Triangle *> findObjectsUsingRay(Line curRay);

    static void findObjectsUsingRay(Line curRay, Node *curNode, std::vector<Triangle *> &result);

    //Разделение узлов, тоже надо перенести в приватные
    void splitLeafNode(Node *curNode, TriangleLeaf *curObj);

    void splitNotLeafNode(Node *curNode, Node *insertedNode);

    //Сортировки по оси OX
    static int sortObjectsByAxis(const void *a, const void *b);

    static int sortNodesByAxis(const void *a, const void *b);


};



