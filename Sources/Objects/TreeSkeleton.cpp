//
// Created by fangl on 2023/8/19.
//

#include "TreeSkeleton.h"

static void pushBackValues(QVector<float> &vertices, Point pos) {
    vertices.push_back(pos.x());
    vertices.push_back(pos.y());
    vertices.push_back(pos.z());
}

// TODO: 将所有recursive改成用栈实现，防止stack overflow
static void updateVertices(std::unique_ptr<Metamer> &metamer, QVector<float> &vertices) {
    if(!metamer)
        return;
    pushBackValues(vertices, metamer->begin);
    pushBackValues(vertices, metamer->end);

    updateVertices(metamer->axillary, vertices);
    updateVertices(metamer->terminal, vertices);

}

void TreeSkeleton::init(std::unique_ptr<Tree> &tree) {
    vertices.clear();

    updateVertices(tree->root, vertices);
    BasicGeometry::init(vertices, Data_Type::ONLY_POSITION, Draw_Mode::LINES);
}


