#include "Model.h"
#include <QFile>


Model::Model() {
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
}

bool Model::init(const QString &path) {
    // clear
    this->clearModel();

    // init
    bool res = loadOBJ(path);
    if (res) {
        qDebug() << "Load success";
        this->bindBufferData();
    }

    return res;
}

void Model::draw(GLboolean isOpenLighting) {
    for (auto &object: objects) {
        ResourceManager::getShader("my_model").use().setVector3f("material.Ka", map_materials[object.matName].Ka);
        ResourceManager::getShader("my_model").use().setBool("isOpenLighting", isOpenLighting);

        if (!map_materials.empty()) {
            core->glActiveTexture(GL_TEXTURE0);
            // ambient texture
            ResourceManager::getTexture(map_materials[object.matName].name_map_Ka).bind();

            if (isOpenLighting) {
                core->glActiveTexture(GL_TEXTURE1);
                ResourceManager::getTexture(map_materials[object.matName].name_map_Kd).bind();
                ResourceManager::getShader("my_model").use().setVector3f("material.Kd", map_materials[object.matName].Kd);
                ResourceManager::getShader("my_model").use().setVector3f("material.Ks", map_materials[object.matName].Ks);
                ResourceManager::getShader("my_model").use().setFloat("material.shininess",
                                                                   map_materials[object.matName].shininess);
            }
        }


        if(newModel) {
            core->glGenVertexArrays(1, &object.VAO);
            core->glBindVertexArray(object.VAO);
            enableBufferData(object);
        } else {
            core->glBindVertexArray(object.VAO);
        }

        core->glDrawArrays(GL_TRIANGLES, 0, object.positions.size());
        core->glBindVertexArray(0);
    }

    newModel = false;
}

bool Model::loadOBJ(const QString &path) {
    qDebug() << "Loading Object, path: " + path;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "OBJLOADER ERROR::FILE CAN NOT OPEN!";
        file.close();
        return false;
    }

    QTextStream in(&file);
    QString line;

    QVector<int> positionIndices, uvIndices, normalIndices;
    QVector<QVector3D> temp_positions;
    QVector<QVector2D> temp_uvs;
    QVector<QVector3D> temp_normals;
    QString temp_matName;//材质的名称

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList list = line.split(" ", Qt::SkipEmptyParts);
        if (list.empty())
            continue;

        if (list[0] == "mtllib") {
            // file path
            // ":Resources/Models/nanosuit/nanosuit.obj"
            QString mtl_path = path;
            int tempIndex = path.lastIndexOf("/") + 1;
            mtl_path.remove(tempIndex, path.size() - tempIndex);  // ":Resources/Models/nanosuit/"

            // Read material to Material class
            qDebug() << "Loading mtl file, path:  " + mtl_path + list[1];
            QFile mtl_file(mtl_path + list[1]);//正确的材质文件路径

            if (!mtl_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "OBJLOADER ERROR::MTL_FILE CAN NOT OPEN!";
                mtl_file.close();
                file.close();
                return false;
            }

            QTextStream mtl_in(&mtl_file);
            QString mtl_line;

            Material material;
            QString matName;

            while (!mtl_in.atEnd()) {
                mtl_line = mtl_in.readLine();
                QStringList mtl_list = mtl_line.split(QRegExp("\\s+"), Qt::SkipEmptyParts);

                if (mtl_list.empty())
                    continue;

                /*
                 * illum 0：颜色由环境光+漫反射光给出。忽略镜面反射。
                 * illum 1：颜色由环境光+漫反射+高光给出。忽略镜面反射。
                 * illum 2：颜色由环境光+漫反射+Phong高光模型给出。考虑镜面反射。
                 * illum 3：颜色由环境光+漫反射+高光给出。考虑反射，但不考虑折射（透明度）。
                 * illum 4：颜色由环境光+漫反射+反射+折射给出。
                 * illum 5-7：包含光源的反射。
                 * illum 8-10：包含光源和半透明的反射。
                 */

                if (mtl_list[0] == "newmtl") {
                    matName = mtl_list[1];
                    map_materials[matName] = material;
                } else if (mtl_list[0] == "Ns") {
                    double shininess = mtl_list[1].toDouble();
                    map_materials[matName].shininess = shininess;
                } else if (mtl_list[0] == "Ka") {
                    float x = mtl_list[1].toFloat();
                    float y = mtl_list[2].toFloat();
                    float z = mtl_list[3].toFloat();
                    QVector3D Ka(x, y, z);
                    map_materials[matName].Ka = Ka;
                } else if (mtl_list[0] == "Kd") {
                    float x = mtl_list[1].toFloat();
                    float y = mtl_list[2].toFloat();
                    float z = mtl_list[3].toFloat();
                    QVector3D Kd(x, y, z);
                    map_materials[matName].Kd = Kd;
                } else if (mtl_list[0] == "Ks") {
                    float x = mtl_list[1].toFloat();
                    float y = mtl_list[2].toFloat();
                    float z = mtl_list[3].toFloat();
                    QVector3D Ks(x, y, z);
                    map_materials[matName].Ks = Ks;
                } else if (mtl_list[0] == "map_Ka") {
                    ResourceManager::loadTexture(mtl_list[1], mtl_path + mtl_list[1]);
                    map_materials[matName].name_map_Ka = mtl_list[1];
                } else if (mtl_list[0] == "map_Kd") {
                    ResourceManager::loadTexture(mtl_list[1], mtl_path + mtl_list[1]);
                    map_materials[matName].name_map_Kd = mtl_list[1];
                }
            }
        } else if (list.size() > 1 && (list[1] == "object" || list[0] == "o")) {
            // finish one object, deal with the inedx
            if (!objects.empty()) {
                for (int i = 0; i < positionIndices.size(); i++) {
                    //得到索引
                    int posIndex = positionIndices[i];
                    int uvIndex = uvIndices[i];
                    int norIndex = normalIndices[i];

                    QVector3D pos = temp_positions[posIndex - 1];
                    objects.last().positions.push_back(pos);

                    QVector3D nor = temp_normals[norIndex - 1];
                    objects.last().normals.push_back(nor);

                    if (uvIndex != 0) {
                        QVector2D uv = temp_uvs[uvIndex - 1];
                        objects.last().uvs.push_back(uv);
                    }

                }
                objects.last().matName = temp_matName;
                positionIndices.clear();
                uvIndices.clear();
                normalIndices.clear();
            }

            Object object;
            objects.push_back(object);
        } else if (list[0] == "v") {
            float x = list[1].toFloat();
            float y = list[2].toFloat();
            float z = list[3].toFloat();

            QVector3D pos;
            pos.setX(x); pos.setY(y); pos.setZ(z);
            temp_positions.push_back(pos);
        } else if (list[0] == "vt") {
            float x = list[1].toFloat();
            float y = list[2].toFloat();

            QVector2D uv;
            uv.setX(x); uv.setY(y);
            temp_uvs.push_back(uv);
        } else if (list[0] == "vn") {
            float x = list[1].toFloat();
            float y = list[2].toFloat();
            float z = list[3].toFloat();

            QVector3D nor;
            nor.setX(x); nor.setY(y); nor.setZ(z);
            temp_normals.push_back(nor);
        } else if (list[0] == "usemtl") {
            temp_matName = list[1];
        } else if (list[0] == "f") {
            if (list.size() > 4) {
                qDebug() << "OBJLOADER ERROR::THE LOADER ONLY SUPPORT THE TRIANGLES MESH!" << Qt::endl;
                file.close();
                return false;
            }
            for (int i = 1; i < 4; ++i) {   // “f 2396/2442/2376 101/107/111 100/106/110”
                QStringList sList = list[i].split("/");
                int posIndex = sList[0].toInt();
                int uvIndex = sList[1].toInt();
                int norIndex = sList[2].toInt();

                positionIndices.push_back(posIndex);
                uvIndices.push_back(uvIndex);
                normalIndices.push_back(norIndex);
            }
        }
    }

    // last object
    for (int i = 0; i < positionIndices.size(); i++) {
        int posIndex = positionIndices[i];
        int uvIndex = uvIndices[i];
        int norIndex = normalIndices[i];

        QVector3D pos = temp_positions[posIndex - 1];
        objects.last().positions.push_back(pos);

        QVector3D nor = temp_normals[norIndex - 1];
        objects.last().normals.push_back(nor);

        if (uvIndex != 0) {
            QVector2D uv = temp_uvs[uvIndex - 1];
            objects.last().uvs.push_back(uv);
        }
    }
    objects.last().matName = temp_matName;

    file.close();
    return true;
}

void Model::bindBufferData() {
    for (auto &object: objects) {
        // upload data to GPU
        core->glGenBuffers(1, &object.positionVBO);
        core->glBindBuffer(GL_ARRAY_BUFFER, object.positionVBO);
        core->glBufferData(GL_ARRAY_BUFFER, object.positions.size() * sizeof(QVector3D), &object.positions[0],
                           GL_STATIC_DRAW);

        core->glGenBuffers(1, &object.uvVBO);
        core->glBindBuffer(GL_ARRAY_BUFFER, object.uvVBO);
        core->glBufferData(GL_ARRAY_BUFFER, object.uvs.size() * sizeof(QVector2D), &object.uvs[0], GL_STATIC_DRAW);

        core->glGenBuffers(1, &object.normalVBO);
        core->glBindBuffer(GL_ARRAY_BUFFER, object.normalVBO);
        core->glBufferData(GL_ARRAY_BUFFER, object.normals.size() * sizeof(QVector3D), &object.normals[0],
                           GL_STATIC_DRAW);

        // bind VAO
        /*core->glGenVertexArrays(1, &object.VAO);
        core->glBindVertexArray(object.VAO);
        enableBufferData(object);
        core->glBindVertexArray(0);*/
    }
}

void Model::enableBufferData(Object &object) {
    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, object.positionVBO);
    core->glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *) nullptr);

    core->glEnableVertexAttribArray(1);
    core->glBindBuffer(GL_ARRAY_BUFFER, object.uvVBO);
    core->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    core->glEnableVertexAttribArray(2);
    core->glBindBuffer(GL_ARRAY_BUFFER, object.normalVBO);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
}


void Model::clearModel() {
    for (auto &object: objects) {
        core->glDeleteBuffers(1, &object.positionVBO);
        core->glDeleteBuffers(1, &object.uvVBO);
        core->glDeleteBuffers(1, &object.normalVBO);
        core->glDeleteVertexArrays(1, &object.VAO);

        object.positions.clear();
        object.normals.clear();
        object.uvs.clear();
    }
    objects.clear();
    map_materials.clear();
    ResourceManager::clearTextures();
}