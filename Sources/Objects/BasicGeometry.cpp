//
// Created by fangl on 2023/7/31.
//

#include "BasicGeometry.h"


BasicGeometry::BasicGeometry(): numVertex(0), drawMode(Draw_Mode::TRIANGLES) ,VAO(0), VBO(0) {
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
}

BasicGeometry::~BasicGeometry(){
    if(VBO != 0)
        core->glDeleteBuffers(1, &VBO);
    if(VAO != 0)
        core->glDeleteVertexArrays(1, &VAO);
}

// 2 type:
// lineLength == 8 ---> position, texture, normal
// lineLength == 3 ---> position
void BasicGeometry::init(const QVector<float>& data, Data_Type dataType, Draw_Mode mode){
    changeDrawMode(mode);

    int lineLength = dataType == Data_Type::POS_TEX_NOR ? 8 : 3;

    if(data.size() % lineLength != 0) {
        throw std::invalid_argument("PLS make sure data correct!");
    }
    numVertex = data.size() / lineLength;

    core->glGenBuffers(1, &VBO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    core->glGenVertexArrays(1, &VAO);
    core->glBindVertexArray(VAO);

    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLsizei)lineLength * sizeof(float), (void*)nullptr);

    if(dataType == Data_Type::POS_TEX_NOR) {
        // textures
        core->glEnableVertexAttribArray(1);
        core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        // normals
        core->glEnableVertexAttribArray(2);
        core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    }

    core->glBindVertexArray(0);
}

void BasicGeometry::updateVertexData(const QVector<float>& data, Data_Type dataType) {
    core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
    core->glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    int lineLength = dataType == Data_Type::POS_TEX_NOR ? 8 : 3;
    this->numVertex = data.size() / lineLength;
}

void BasicGeometry::draw() {
    core->glBindVertexArray(VAO);

    if(drawMode == Draw_Mode::POINTS)
        core->glDrawArrays(GL_POINTS, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::LINES)
        core->glDrawArrays(GL_LINES, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::LINE_STRIP)
        core->glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::LINE_LOOP)
        core->glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::TRIANGLES)
        core->glDrawArrays(GL_TRIANGLES, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::TRIANGLE_STRIP)
        core->glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)numVertex);
    else if(drawMode == Draw_Mode::TRIANGLE_FAN)
        core->glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)numVertex);

    core->glBindVertexArray(0);
}
