//
// Created by fangl on 2023/8/19.
//

#ifndef TREESKELETON_H
#define TREESKELETON_H

#include "Tree.h"
#include "Types.h"
#include "Metamer.h"
#include "BasicGeometry.h"
#include "TreeModeler.h"


class TreeSkeleton : public BasicGeometry
{
public:
    TreeSkeleton() : BasicGeometry() {}
    ~TreeSkeleton() = default;

    void updateVertexData(const std::unique_ptr<Tree> &tree);

private:
    QVector<float> vertices;

};


#endif //TREESKELETON_H
