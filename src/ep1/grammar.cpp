
// ep1/grammar.cpp* 
#include "stdafx.h"
#include "ep1/grammar.h"
#include "core/paramset.h"
#include "core/api.h"

using std::to_string;

void Grammar::AddInstance(char token, const string &instanceName) {
    Info("Adding instance '%c'\n", token);
    instances[token] = instanceName;
}

void Grammar::AddRule(char token, const string &result) {
    Info("Adding rule '%c' -> '%s'\n", token, result.c_str()),
    rules[token] = result;
}

void Grammar::SetForward(float f) {
    forward = f;
}

void Grammar::SetDelta(float d) {
    delta = d;
}

void Grammar::Expand(const string &axiom, size_t steps) const {
    string description = axiom;
    for (size_t i = 0; i < steps; ++i) {
        string derivate = "";
        for (char token : description) {
            const auto &check = rules.find(token);
            if (check != rules.end())
                derivate += check->second;
            else
                derivate += token;
        }
        description = derivate;
    }
    Info("Final description: %s\n", description.c_str());
    pbrtTransformBegin();
    size_t transforms = 0;
    for (char token : description) {
        ParamSet params;
        switch(token) {
            case 'F': {
                pbrtTranslate(0.0f, 0.0f, forward);
                break;
            }
            case '+': {
                pbrtRotate(delta, 0.0f, 1.0f, 0.0f);
                break;
            }
            case '-': {
                pbrtRotate(-delta, 0.0f, 1.0f, 0.0f);
                break;
            }
            case '[': {
                pbrtTransformBegin();
                ++transforms;
                break;
            }
            case ']': {
                if (transforms > 0) {
                  pbrtTransformEnd();
                  --transforms;
                } else Warning("Finishing inexistant transform");
                break;
            }
            default: {
                const auto &check = instances.find(token);
                if (check != instances.end())
                    pbrtObjectInstance(check->second);
            }
        }
    }
    if (transforms > 0)
        Warning("%d unclosed transformations left", transforms);
    for (size_t i = 0; i < transforms; ++i)
        pbrtTransformEnd();
    pbrtTransformEnd();
}

