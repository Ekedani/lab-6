#include "r_tree.h"

void rTree::findObjectsUsingRay(Line curRay, Node *curNode, vector<Triangle *> &result) {
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

std::vector<Triangle *> rTree::findObjectsUsingRay(Line curRay) {
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

void rTree::splitNotLeafNode(Node *curNode, Node *insertedNode) {

    Node *nodeParent;
    //В случае если является корнем дерева
    if(curNode == root){
        nodeParent = new Node;
        curNode->parentNode = nodeParent;
        nodeParent->nodes.push_back(curNode);
        root = nodeParent;
        root->parentNode = nullptr;
    }
    //В случае если он им не является
    else{
        nodeParent = curNode->parentNode;
    }

    //Копирование узлов
    Node **newNodes = new Node*[maxCount + 1];
    for (int i = 0; i < maxCount; ++i){
        newNodes[i] = curNode->nodes[i];
    }
    newNodes[maxCount] = insertedNode;

    //bool axisIsX = !splitNotLeafAxis(curNode, insertedNode);

    Node* firstNode;
    Node* secondNode;
    Node* minimalFirstNode = new Node;
    Node* minimalSecondNode = new Node;

    /*double minimalOverlap = DBL_MAX;
    double minimalArea = DBL_MAX;
    double curOverlap;
    double curArea;

    for (int i = 0; i < 1; ++i) {
        sortForNotLeaf(newNodes, axisIsX, i);
        for (int j = minCount - 1; j < maxCount - minCount; ++j) {
            firstNode = new Node;
            secondNode = new Node;

            int curNode;
            for (curNode = 0; curNode <= j ; curNode++) {
                firstNode->nodes.push_back(newNodes[curNode]);
            }

            for (curNode = j;  curNode < maxCount - 1; curNode++) {
                secondNode->nodes.push_back(newNodes[curNode]);
            }

            firstNode->updateMBR();
            secondNode->updateMBR();

            curOverlap = firstNode->MBR.overlap(&secondNode->MBR);

            if(curOverlap < minimalOverlap){
                *(minimalFirstNode) = *(firstNode);
                *(minimalSecondNode) = *(secondNode);
                minimalOverlap = curOverlap;
            }
            else{
                if (curOverlap == minimalOverlap){
                    curArea = firstNode->MBR.area() + secondNode->MBR.area() - curOverlap;
                    if(curArea < minimalArea){
                        *(minimalFirstNode) = *(firstNode);
                        *(minimalSecondNode) = *(secondNode);
                        minimalArea = curArea;
                    }
                }
            }
            delete firstNode;
            delete secondNode;
        }
    }*/

    minimalFirstNode->parentNode = curNode->parentNode;
    minimalSecondNode->parentNode = curNode->parentNode;

    *curNode = *minimalFirstNode;
    delete minimalFirstNode;

    if(curNode->parentNode->nodes.size() < maxCount){
        curNode->parentNode->nodes.push_back(minimalSecondNode);
        while(nullptr != nodeParent){
            nodeParent->updateMBP();
            nodeParent = nodeParent->parentNode;
        }
    }
    else{
        splitNotLeafNode(curNode->parentNode, minimalSecondNode);
    }
}

void rTree::splitLeafNode(Node *curNode, TriangleLeaf *curObj) {
    Node *nodeParent;
    //В случае если является корнем дерева
    if(curNode == root){
        nodeParent = new Node;
        curNode->parentNode = nodeParent;
        nodeParent->nodes.push_back(curNode);
        root = nodeParent;
        root->parentNode = nullptr;
    }
    //В случае если он им не является
    else{
        nodeParent = curNode->parentNode;
    }

    auto **newObjects = new TriangleLeaf*[maxCount + 1];
    for (int i = 0; i < maxCount; ++i){
        newObjects[i] = curNode->objects[i];
    }
    newObjects[maxCount] = curObj;

    Node* firstNode;
    Node* secondNode;
    Node* minimalFirstNode = new Node;
    Node* minimalSecondNode = new Node;

    auto minimalOverlap = DBL_MAX;
    auto minimalArea = DBL_MAX;
    double curOverlap;
    double curArea;

    qsort(newObjects, maxCount + 1, sizeof(TriangleLeaf*), sortObjectsByAxis);

    //for (int j = minCount - 1; j <= maxCount - minCount; ++j) {

    //    firstNode = new Node;
    //    secondNode = new Node;

    //    int curPlace = 0;
    //    for (curPlace; curPlace <= j; curPlace++) {
    //        firstNode->objects.push_back(newObjects[curPlace]);
    //    }
    //    for (curPlace; curPlace <= maxCount; curPlace++) {
    //        secondNode->objects.push_back(newObjects[curPlace]);
    //    }

    //    firstNode->updateMBP();
    //    secondNode->updateMBP();

    //    curOverlap = firstNode->MBR.overlap(&secondNode->MBR);

    //    if(curOverlap < minimalOverlap){
    //        *minimalFirstNode = *firstNode;
    //        *minimalSecondNode = *secondNode;
    //        minimalArea = curArea;
    //    }
    //    else{
    //        if(curOverlap == minimalOverlap){
    //            curArea = firstNode->MBP.volume() + secondNode->MBP.volume() - curOverlap;
    //            if(curArea < minimalArea){
    //                *minimalFirstNode = *firstNode;
    //                *minimalSecondNode = *secondNode;
    //                minimalArea = curArea;
    //            }
    //        }
    //    }
    //    delete firstNode;
    //    delete secondNode;
    //}

    minimalFirstNode->parentNode = curNode->parentNode;
    minimalSecondNode->parentNode = curNode->parentNode;

    *curNode = *minimalFirstNode;
    delete minimalFirstNode;

    if(curNode->parentNode->nodes.size() < maxCount){
        curNode->parentNode->nodes.push_back(minimalSecondNode);
        while(nullptr != nodeParent){
            nodeParent->updateMBP();
            nodeParent = nodeParent->parentNode;
        }
    }
    else{
        splitNotLeafNode(curNode->parentNode, minimalSecondNode);
    }
}

int rTree::sortObjectsByAxis(const void *a, const void *b) {
    const TriangleLeaf *arg1 = *(const TriangleLeaf **)a;
    const TriangleLeaf *arg2 = *(const TriangleLeaf **)b;
    /*if(arg1->MBP == arg2->MBP){
        return 0;
    }
    else{
        if(arg1->MBP < arg2->MBP){
            return -1;
        }
        return 1;
    }*/
}

int rTree::sortNodesByAxis(const void *a, const void *b) {
    const Node *arg1 = *(const Node **)a;
    const Node *arg2 = *(const Node **)b;
    /*if(arg1->MBP == arg2->MBP){
        return 0;
    }
    else{
        if(arg1->MBP < arg2->MBP){
            return -1;
        }
        return 1;
    }*/
}
