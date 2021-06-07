#include <vector>
#include "prism.h"
#include <cfloat>

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
        return chooseSubtree(root, newTriangle);
    }

    Node* chooseSubtree(Node* start, Triangle newTriangle){
        Node* chosen = nullptr;
        if (start->isLeaf()){
            return start;
        }
        else {
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

    void insertTriangle(Triangle& curTriangle){
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

    std::vector<Triangle*> findObjectsUsingRay(Line curRay){
        std::vector<Triangle*> result;
        if(root->isLeaf()){
            for (auto & object : root->objects) {
                if(curRay.triangle_intersection(*object->triangle) != 0){
                    result.push_back(object->triangle);
                }
            }
        }
        else{
            for (auto & node : root->nodes) {
                //TODO:
                //if(curRay.doesIntersect(node->MBP)){
                //    findObjectsUsingRay(curRay, node, result);
                //}
            }
        }
        return result;
    }

    void findObjectsUsingRay(Line curRay, Node* curNode, std::vector<Triangle*> &result){
        if(curNode->isLeaf()){
            for (auto & object : curNode->objects) {
                if(curRay.triangle_intersection(*object->triangle) != 0){
                    result.push_back(object->triangle);
                }
            }
        }
        else{
            for (auto & node : curNode->nodes) {
                //TODO:
                //if(curRay.doesIntersect(node->MBP)){
                //    findObjectsUsingRay(curRay, node, result);
                //}
            }
        }
    }
};



