
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_SHAPES_LSYSTEM_H
#define PBRT_SHAPES_LSYSTEM_H

// shapes/lsystem.h*
#include "shape.h"

#include <memory>

// LSystem Declarations
class LSystem : public Shape {
public:
    // LSystem Public Methods
    LSystem(const Transform *o2w, const Transform *w2o, bool ro,
            const string &description);
    BBox ObjectBound() const override;
    bool CanIntersect() const override { return false; }
    void Refine(vector<Reference<Shape>> &refined) const override;
private:
    // LSystem Private Data
    vector<Reference<Shape>> terminals;
    vector<std::unique_ptr<Transform>> transformations;
};

LSystem *CreateLSystemShape(const Transform *o2w, const Transform *w2o,
                            bool reverseOrientation, const ParamSet &params);

#endif // PBRT_SHAPES_LSYSTEM_H

