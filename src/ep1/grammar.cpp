
// ep1/grammar.cpp* 
#include "stdafx.h"
#include "ep1/grammar.h"
#include "core/paramset.h"
#include "core/api.h"

void Grammar::AddTerminal(char token, const string &instanceName) {
    terminals[token] = instanceName;
}

void Grammar::SetForwad(float f) {
    forward = f;
}

void Grammar::Expand(const string &axiom, size_t steps) const {
    for (char c : axiom) {
        ParamSet params;
        switch(c) {
            case '.': {
                float radius = 50.0f;
                params.AddFloat("radius", &radius);
                pbrtShape("sphere", params);
                break;
            }
            case 'F': {
                pbrtTranslate(0.0f, 0.0f, forward);
                break;
            }
            default: {
                const auto &check = terminals.find(c);
                if (check != terminals.end()) {
                    pbrtObjectInstance(check->second);
                } else {
                    Warning("Unknown token");
                }
            }
        }
    }
}

