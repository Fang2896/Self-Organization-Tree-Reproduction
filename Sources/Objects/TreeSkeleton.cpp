//
// Created by fangl on 2023/8/19.
//

#include "TreeSkeleton.h"


void TreeSkeleton::init(const std::unique_ptr<Tree> &tree) {
    vertices.clear();
    TreeModeler::updateSkeletonVertexData(tree->root, vertices);

    BasicGeometry::init(vertices, Data_Type::ONLY_POSITION, Draw_Mode::LINES);
}



void TreeSkeleton::updateVertexData(const std::unique_ptr<Tree> &tree) {
    vertices.clear();

    TreeModeler::updateSkeletonVertexData(tree->root, vertices);
    BasicGeometry::updateVertexData(vertices, Data_Type::ONLY_POSITION);
}


