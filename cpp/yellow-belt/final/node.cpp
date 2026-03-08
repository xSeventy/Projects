#include "node.h"


bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& d) : cmp_(cmp), d_(d) {}


bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
    if(cmp_ == Comparison::Less) {
        return date < d_;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return date <= d_;
    } else if (cmp_ == Comparison::Equal) {
        return date == d_;
    } else if (cmp_ == Comparison::NotEqual) {
        return date != d_;
    } else if (cmp_ == Comparison::Greater) {
        return date > d_;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return date >= d_;
    }
    return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {}




bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
    if(cmp_ == Comparison::Less) {
        return event < event_ ;
    } else if (cmp_ == Comparison::LessOrEqual) {
        return event <= event_;
    } else if (cmp_ == Comparison::Equal) {
        return event == event_;
    } else if (cmp_ == Comparison::NotEqual) {
        return event != event_;
    } else if (cmp_ == Comparison::Greater) {
        return event > event_;
    } else if (cmp_ == Comparison::GreaterOrEqual) {
        return event >= event_;
    }
    return false;
}



LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_oper, shared_ptr<Node> left, shared_ptr<Node> right)
                                            : logical_oper_(logical_oper), left_(left), right_(right) {}




bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    
    if(logical_oper_ == LogicalOperation::Or) {
        return left_->Evaluate(date, event)|| right_->Evaluate(date, event);
    } else if (logical_oper_ == LogicalOperation::And) {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
    
    return false;
}
