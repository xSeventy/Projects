#pragma once
#include <memory>
#include <string>
#include "date.h"


enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
    virtual ~Node() = default;
    
};


class EmptyNode : public Node {
public:
    
    bool Evaluate(const Date& date, const std::string& event) const override;
    
};

class DateComparisonNode : public Node {
public:
    
    DateComparisonNode(const Comparison& cmp, const Date& d);
    
    bool Evaluate(const Date& date, const std::string& event) const override;
    
    
private:
    Comparison cmp_;
    Date d_;
    
};

class EventComparisonNode : public Node {
public:
    
    EventComparisonNode(const Comparison& cmp, const std::string& event);
    
    bool Evaluate(const Date& date, const std::string& event) const override;
    
private:
    Comparison cmp_;
    string event_;
};

class LogicalOperationNode : public Node {
public:
    
    LogicalOperationNode(const LogicalOperation& logical_oper,
                         std::shared_ptr<Node> left,
                         std::shared_ptr<Node> right);
    
    bool Evaluate(const Date& date, const std::string& event) const override;
    
private:
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
    LogicalOperation logical_oper_;
};
