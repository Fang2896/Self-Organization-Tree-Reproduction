//
// Created by fangl on 2023/8/19.
//

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <limits>

#include <QVector3D>


using U32 = uint32_t;
using U64 = uint64_t;

using F32 = float;
using F64 = double;

static_assert(sizeof(F32) == 4, "uint32_t must be 4 bytes.");
static_assert(std::numeric_limits<F32>::is_iec559, "float must be iec559 standard.");
static_assert(sizeof(F64) == 8, "double must be 8 bytes.");
static_assert(std::numeric_limits<F64>::is_iec559, "double must be iec559 standard.");

using BudId = U32;
using Point     = QVector3D;    // marker points
using Vertex    = QVector3D;    // tree structure vertex


#endif //TYPES_H
