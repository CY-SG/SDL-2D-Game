#pragma once
#include<string>
enum class ParamType {
    Bool,
    Trigger,
    Float,
};

struct AnimatorParam {
    ParamType type;
    bool boolValue = false;
    float floatValue = 0.0f;
    bool triggerValue = false;
    AnimatorParam(ParamType _type) {
        type = _type;
    }
    AnimatorParam() = default;
};

enum class CompareOp {
    True,
    False,
    Greater,
    Less,
    Trigger,
    NotSame,
    Same,
    ExitTime
};

struct TransitionCondition {
public:
    std::string name;
    CompareOp compareOp;
    float value;
    TransitionCondition(const std::string& name, CompareOp _compareOp, float _value = 0.0f) {
        this->name = name;
        compareOp = _compareOp;
        value = _value;
    }
};