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

U64 Metamer::countMetamers() const {
    U64 count = 1;
    if (axillary)
        count += axillary->countMetamers();
    if (terminal)
        count += terminal->countMetamers();

    return count;
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
