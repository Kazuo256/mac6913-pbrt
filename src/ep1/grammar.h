
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_EP1_GRAMMAR_H
#define PBRT_EP1_GRAMMAR_H

// ep1/grammar.h*
#include "pbrt.h"
#include <map>

class Grammar final {
public:
    using RuleSet = std::map<char, string>;
    Grammar() : forward(10.0f) {}
    void AddInstance(char token, const string &instanceName);
    void AddRule(char token, const string &result);
    void SetForward(float f);
    void SetDelta(float d);
    void Expand(const string &axiom, size_t steps) const;
private:
    RuleSet instances;
    RuleSet rules;
    float   forward;
    float   delta;
};

#endif // PBRT_EP1_GRAMMAR_H

