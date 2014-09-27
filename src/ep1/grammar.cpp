
// ep1/grammar.cpp* 
#include "stdafx.h"
#include "ep1/grammar.h"
#include "core/paramset.h"
#include "core/api.h"

void Grammar::AddInstance(char token, const string &instanceName) {
    printf("Adding instance '%c'\n", token);
    instances[token] = instanceName;
}

void Grammar::AddRule(char token, const string &result) {
    printf("Adding rule '%c' -> '%s'\n", token, result.c_str()),
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
    printf("Final description: %s\n", description.c_str());
    for (char token : description) {
        ParamSet params;
        switch(token) {
            case 'F': {
                pbrtTranslate(0.0f, 0.0f, forward);
                break;
            }
            default: {
                const auto &check = instances.find(token);
                if (check != instances.end())
                    pbrtObjectInstance(check->second);
            }
        }
    }
}

