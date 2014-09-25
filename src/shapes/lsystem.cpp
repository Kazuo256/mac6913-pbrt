
// shapes/lsystem.cpp
#include "shapes/lsystem.h"
#include "paramset.h"

#include <numeric>

LSystem::LSystem(const Transform *o2w, const Transform *w2o, bool ro,
                 const string &description) : Shape(o2w, w2o, ro) {

}

BBox LSystem::ObjectBound() const {
    if (terminals.empty())
        return BBox(Point());
    return std::accumulate(terminals.begin()+1, terminals.end(),
                           terminals.front()->ObjectBound(),
                           [](const BBox &lhs, const Reference<Shape> &rhs)
                               -> BBox {
                               return Union(lhs, rhs->ObjectBound());
                           });
}

void LSystem::Refine(vector<Reference<Shape>> &refined) const {
    for (auto &shape : terminals)
        refined.push_back(shape);
}

LSystem *CreateLSystemShape(const Transform *o2w, const Transform *w2o,
                            bool reverseOrientation, const ParamSet &params) {
    return nullptr;
}

