//
// Created by fangl on 2023/8/20.
//

#ifndef TREEMODELER_H
#define TREEMODELER_H

#include "Types.h"
#include "Tree.h"
#include "Metamer.h"

/*
 * 作用：管理树的建模（可以考虑把skeleton加进来）
 * 1. 生成skeleton数据
 * 2. 生成Mesh 数据
 */

class TreeModeler
{
public:
    static void pushBackPos(QVector<float> &vertices, Point pos);
    static void updateSkeletonVertexData(const std::unique_ptr<Metamer> &metamer, QVector<float> &vertices);
    static void updateMeshVertexData(int resolution, std::unique_ptr<Metamer> &metamer, QVector<float> &vertices);

private:
    TreeModeler() {}

};


#endif //TREEMODELER_H
