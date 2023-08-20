//
// Created by fangl on 2023/8/19.
//

#include "Metamer.h"


Metamer::Metamer(Environment &environment, const Point &begin, const Point &end)
    : begin(begin), end(end), axillaryDirection(BaseAlgorithms::randomPerturbation(environment.randomGenerator,Vector(begin, end),
                                                                           Environment::AxillaryPerturbationAngle)),
      axillaryId(environment.getNextBudId()), terminalId(environment.getNextBudId()) {}

Point Metamer::getCenter() const {
    const auto centerX = begin.x() + 0.5f * (end.x() - begin.x());
    const auto centerY = begin.y() + 0.5f * (end.y() - begin.y());
    const auto centerZ = begin.z() + 0.5f * (end.z() - begin.z());
    return {centerX, centerY, centerZ};
}

float Metamer::getLength() const {
    return begin.distanceToPoint(end);
}

U64 Metamer::countMetamers() {
    axillaryCount = 0;
    terminalCount = 0;

    if (axillary) {
        axillaryCount += axillary->countMetamers();
    }

    if (terminal) {
        terminalCount += terminal->countMetamers();
    }

    return axillaryCount + terminalCount + 1;
}

BoundingBox Metamer::getBoundingBox() const {
    BoundingBox boundingBox;
    boundingBox.include(begin);
    boundingBox.include(end);
    if (axillary)
        boundingBox = boundingBox.merge(axillary->getBoundingBox());
    if (terminal)
        boundingBox = boundingBox.merge(terminal->getBoundingBox());

    return boundingBox;
}
