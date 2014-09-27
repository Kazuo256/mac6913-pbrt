
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
    void AddTerminal(char token, const string &instanceName);
    void SetForwad(float f);
    void Expand(const string &axiom, size_t steps) const;
private:
    RuleSet terminals;
    float   forward;
};

#endif // PBRT_EP1_GRAMMAR_H

