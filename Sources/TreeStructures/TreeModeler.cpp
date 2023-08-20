//
// Created by fangl on 2023/8/20.
//

#include "TreeModeler.h"


void TreeModeler::pushBackPos(QVector<float> &vertices, Point pos) {
    vertices.push_back(pos.x());
    vertices.push_back(pos.y());
    vertices.push_back(pos.z());
}


// TODO: 将所有recursive改成用栈实现，防止stack overflow
void TreeModeler::updateSkeletonVertexData(const std::unique_ptr<Metamer> &metamer, QVector<float> &vertices) {
    if(!metamer)
        return;
    TreeModeler::pushBackPos(vertices, metamer->begin);
    TreeModeler::pushBackPos(vertices, metamer->end);

    updateSkeletonVertexData(metamer->axillary, vertices);
    updateSkeletonVertexData(metamer->terminal, vertices);
}

/* TODO: 实现Mesh构造函数
 * 思路：分为两个部分
 *  1. 主干部分，使用一体化的mesh生成
 *  2. 分支部分，每个主分支上的axillary分支，都视作一个一体化的树进行处理
 */
void TreeModeler::updateMeshVertexData(int resolution, std::unique_ptr<Metamer> &metamer, QVector<float> &vertices) {
    if(!metamer)
        return;

    std::unique_ptr<Metamer> *current = &metamer;
    std::unique_ptr<Metamer> *next = &(metamer->terminal);

}
