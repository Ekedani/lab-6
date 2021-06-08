#include "r_tree.h"

void rTree::findObjectsUsingRay(Line curRay, Node *curNode, vector<Triangle *> &result) {
    if (curNode->isLeaf()) {
        for (auto &object : curNode->objects) {
            if (curRay.triangle_intersection(*object->triangle) != 0) {
                result.push_back(object->triangle);
            }
        }
    } else {
        for (auto &node : curNode->nodes) {
            if (curRay.doesIntersectParallelepiped(node->MBP)) {
                findObjectsUsingRay(curRay, node, result);
            }
        }
    }
}

std::vector<Triangle *> rTree::findObjectsUsingRay(Line curRay) {
    std::vector<Triangle *> result;
    if (root->isLeaf()) {
        for (auto &object : root->objects) {
            if (curRay.triangle_intersection(*object->triangle) != 0) {
                result.push_back(object->triangle);
            }
        }
    } else {
        for (auto &node : root->nodes) {
            if (curRay.doesIntersectParallelepiped(node->MBP)) {
                findObjectsUsingRay(curRay, node, result);
            }
        }
    }
    return result;
}

void rTree::splitNotLeafNode(Node *curNode, Node *insertedNode) {
    Node *nodeParent;
    //В случае если является корнем дерева
    if (curNode == root) {
        nodeParent = new Node;
        curNode->parentNode = nodeParent;
        nodeParent->nodes.push_back(curNode);
        root = nodeParent;
        root->parentNode = nullptr;
    }
        //В случае если он им не является
    else {
        nodeParent = curNode->parentNode;
    }

    //Копирование узлов
    Node **newNodes = new Node *[maxCount + 1];
    for (int i = 0; i < maxCount; ++i) {
        newNodes[i] = curNode->nodes[i];
    }
    newNodes[maxCount] = insertedNode;

    //Указатели для хранения лучшего распределения
    Node *firstNode;
    Node *secondNode;
    Node *minimalFirstNode = new Node;
    Node *minimalSecondNode = new Node;

    //Параметры сравнения
    auto minimalOverlap = DBL_MAX;
    auto minimalVolume = DBL_MAX;
    double curOverlap;
    double curVolume;

    //Сортировка нод
    qsort(newNodes, maxCount + 1, sizeof(Node *), sortNodesByAxis);

    //Выбор лучшего распределения
    for (int j = minCount - 1; j < maxCount - minCount; ++j) {
        firstNode = new Node;
        secondNode = new Node;

        int curNode;
        for (curNode = 0; curNode <= j; curNode++) {
            firstNode->nodes.push_back(newNodes[curNode]);
        }

        for (curNode = j + 1; curNode <= maxCount; curNode++) {
            secondNode->nodes.push_back(newNodes[curNode]);
        }

        firstNode->updateMBP();
        secondNode->updateMBP();

        curOverlap = firstNode->MBP.overlapVolume(secondNode->MBP);

        if (curOverlap < minimalOverlap) {
            *minimalFirstNode = *firstNode;
            *minimalSecondNode = *secondNode;
            minimalOverlap = curOverlap;
        } else {
            if (curOverlap == minimalOverlap) {
                curVolume = firstNode->MBP.volume() + secondNode->MBP.volume() - curOverlap;
                if (curVolume < minimalVolume) {
                    *minimalFirstNode = *firstNode;
                    *minimalSecondNode = *secondNode;
                    minimalVolume = curVolume;
                }
            }
        }
        delete firstNode;
        delete secondNode;
    }

    minimalFirstNode->parentNode = curNode->parentNode;
    minimalSecondNode->parentNode = curNode->parentNode;

    *curNode = *minimalFirstNode;
    delete minimalFirstNode;

    if (curNode->parentNode->nodes.size() < maxCount) {
        curNode->parentNode->nodes.push_back(minimalSecondNode);
        while (nullptr != nodeParent) {
            nodeParent->updateMBP();
            nodeParent = nodeParent->parentNode;
        }
    } else {
        splitNotLeafNode(curNode->parentNode, minimalSecondNode);
    }
}

void rTree::splitLeafNode(Node *curNode, TriangleLeaf *curObj) {
    Node *nodeParent;
    //В случае если является корнем дерева
    if (curNode == root) {
        nodeParent = new Node;
        curNode->parentNode = nodeParent;
        nodeParent->nodes.push_back(curNode);
        root = nodeParent;
        root->parentNode = nullptr;
    }
        //В случае если он им не является
    else {
        nodeParent = curNode->parentNode;
    }

    auto **newObjects = new TriangleLeaf *[maxCount + 1];
    for (int i = 0; i < maxCount; ++i) {
        newObjects[i] = curNode->objects[i];
    }
    newObjects[maxCount] = curObj;

    Node *firstNode;
    Node *secondNode;
    Node *minimalFirstNode = new Node;
    Node *minimalSecondNode = new Node;

    auto minimalOverlap = DBL_MAX;
    auto minimalVolume = DBL_MAX;
    double curOverlap;
    double curVolume;

    qsort(newObjects, maxCount + 1, sizeof(TriangleLeaf *), sortObjectsByAxis);
    for (int j = minCount - 1; j <= maxCount - minCount; ++j) {

        firstNode = new Node;
        secondNode = new Node;

        int curPlace = 0;
        for (curPlace; curPlace <= j; curPlace++) {
            firstNode->objects.push_back(newObjects[curPlace]);
        }
        for (curPlace = j + 1; curPlace <= maxCount; curPlace++) {
            secondNode->objects.push_back(newObjects[curPlace]);
        }

        firstNode->updateMBP();
        secondNode->updateMBP();

        curOverlap = firstNode->MBP.overlapVolume(secondNode->MBP);

        if (curOverlap < minimalOverlap) {
            *minimalFirstNode = *firstNode;
            *minimalSecondNode = *secondNode;
            minimalVolume = curVolume;
        } else {
            if (curOverlap == minimalOverlap) {
                curVolume = firstNode->MBP.volume() + secondNode->MBP.volume() - curOverlap;
                if (curVolume < minimalVolume) {
                    *minimalFirstNode = *firstNode;
                    *minimalSecondNode = *secondNode;
                    minimalVolume = curVolume;
                }
            }
        }
        delete firstNode;
        delete secondNode;
    }

    minimalFirstNode->parentNode = curNode->parentNode;
    minimalSecondNode->parentNode = curNode->parentNode;

    *curNode = *minimalFirstNode;
    delete minimalFirstNode;

    if (curNode->parentNode->nodes.size() < maxCount) {
        curNode->parentNode->nodes.push_back(minimalSecondNode);
        while (nullptr != nodeParent) {
            nodeParent->updateMBP();
            nodeParent = nodeParent->parentNode;
        }
    } else {
        splitNotLeafNode(curNode->parentNode, minimalSecondNode);
    }
}

int rTree::sortObjectsByAxis(const void *a, const void *b) {
    const TriangleLeaf *arg1 = *(const TriangleLeaf **) a;
    const TriangleLeaf *arg2 = *(const TriangleLeaf **) b;
    if (arg1->MBP.getFirstPoint()->xCoord == arg2->MBP.getFirstPoint()->xCoord) {
        return 0;
    } else {
        if (arg1->MBP.getFirstPoint()->xCoord < arg2->MBP.getFirstPoint()->xCoord) {
            return -1;
        }
        return 1;
    }
}

int rTree::sortNodesByAxis(const void *a, const void *b) {
    const Node *arg1 = *(const Node **) a;
    const Node *arg2 = *(const Node **) b;
    if (arg1->MBP.getFirstPoint()->xCoord == arg2->MBP.getFirstPoint()->xCoord) {
        return 0;
    } else {
        if (arg1->MBP.getFirstPoint()->xCoord < arg2->MBP.getFirstPoint()->xCoord) {
            return -1;
        }
        return 1;
    }
}

Node *rTree::chooseSubtree(Node *start, const TriangleLeaf &newTriangle) {
    Node *chosen = nullptr;
    if (start->isLeaf()) {
        return start;
    } else {
        int index;
        auto minimalMBPIncreasingVolume = DBL_MAX;
        for (auto &node : start->nodes) {
            if (node->MBP.volumeIncreasing(newTriangle.MBP) < minimalMBPIncreasingVolume) {
                minimalMBPIncreasingVolume = node->MBP.volumeIncreasing(newTriangle.MBP);
            }
        }
        auto minimalVolume = DBL_MAX;
        for (int i = 0; i < start->nodes.size(); ++i) {
            if (start->nodes[i]->MBP.volumeIncreasing(newTriangle.MBP) == minimalMBPIncreasingVolume) {
                if (start->nodes[i]->MBP.volume() < minimalVolume) {
                    minimalVolume = start->nodes[i]->MBP.volume();
                    index = i;
                }
            }
        }
        chosen = start->nodes[index];
    }
    return chooseSubtree(chosen, newTriangle);
}

void rTree::insertTriangle(Triangle *curTriangle) {
    auto *newObj = new TriangleLeaf(curTriangle);
    Node *chosenNode = chooseSubtree(root, *newObj);



    //Если узел не переполнен
    if (chosenNode->objects.size() < maxCount) {
        chosenNode->objects.push_back(newObj);
        while (chosenNode != nullptr) {
            chosenNode->updateMBP();
            chosenNode = chosenNode->parentNode;
        }
    } else {
        splitLeafNode(chosenNode, newObj);
    }
    numOfInserted++;
    debugTreeParse();
    cout << "Inserted triangles: " << numOfInserted << '\n';
}

Node *rTree::chooseSubtree(const TriangleLeaf &newTriangle) {
    return chooseSubtree(root, newTriangle);
}

rTree::rTree() {
    root = new Node;
    root->parentNode = nullptr;
    root->updateMBP();
    numOfInserted = 0;
}

void Node::updateMBP() {
    for (auto &object : objects) {
        MBP = MBP.extend(*object->MBP.getFirstPoint());
        MBP = MBP.extend(*object->MBP.getSecondPoint());
    }
    for (auto &node : nodes) {
        MBP = MBP.extend(*node->MBP.getFirstPoint());
        MBP = MBP.extend(*node->MBP.getSecondPoint());
    }
}

bool Node::isLeaf() const {
    return nodes.empty();
}

Node::Node() {
    parentNode = nullptr;
}

TriangleLeaf::TriangleLeaf(Triangle *t) {
    triangle = t;
    MBP = Prism();
    MBP = MBP.extend(*t->firstVertex);
    MBP = MBP.extend(*t->secondVertex);
    MBP = MBP.extend(*t->thirdVertex);
}
