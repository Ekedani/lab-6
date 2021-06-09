#include <vector>
#include "../data-struct/triangle.h"
#include <cfloat>

struct TriangleLeaf {
    Triangle *triangle;
    Prism MBP;

    explicit TriangleLeaf(Triangle *t);
};

struct Node {
    Node *parentNode;
    Prism *MBP;
    std::vector<TriangleLeaf *> objects;
    std::vector<Node *> nodes;

    Node();

    bool isLeaf() const;

    void updateMBP();
};


class rTree {
private:
    //Корень дерева
    Node *root;

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

    //Конструктор
    rTree();

    //Вставка треугольника в дерево
    void insertTriangle(Triangle *curTriangle);

    //Метод поиска по лучу
    std::vector<Triangle *> findObjectsUsingRay(Line curRay);
};



