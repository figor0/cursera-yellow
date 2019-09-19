#include "node.h"

// EmptyNode
bool EmptyNode::Evaluate(const Date& date, const std::string& event) const
{
	return true;
}

// DateComparisonNode
DateComparisonNode::DateComparisonNode(const Comparison& cmp,
					   const Date& date):
	_date(date), _cmp(cmp)
{	}

bool DateComparisonNode::Evaluate(const Date &date,
								  const std::string &event) const
{
	switch (_cmp) {
	case Comparison::Less:
		return date <	_date;
	case Comparison::LessOrEqual:
		return date <= 	_date;
	case Comparison::Greater:
		return date > 	_date;
	case Comparison::GreaterOrEqual:
		return date >= 	_date;
	case Comparison::Equal:
		return date == 	_date;
	case Comparison::NotEqual:
		return date!= 	_date;
	}
}

void DateComparisonNode::SetDate(const Date &date) { _date = date; }
void DateComparisonNode::SetComparison(const Comparison &cmp) { _cmp = cmp; }



// EventComparisonNode
EventComparisonNode::EventComparisonNode(const Comparison& cmp,
						const std::string& event):
	_event(event), _cmp(cmp)
{	}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const
{
	switch (_cmp) {
	case Comparison::Less:
		return event <	_event;
	case Comparison::LessOrEqual:
		return event <= _event;
	case Comparison::Greater:
		return event >	_event;
	case Comparison::GreaterOrEqual:
		return event >= _event;
	case Comparison::Equal:
		return event == _event;
	case Comparison::NotEqual:
		return event != _event;
	}
}

void EventComparisonNode::SetEvent(const std::string &event){ _event = event; }
void EventComparisonNode::SetComparison(const Comparison &cmp) { _cmp = cmp; }

// LogicalOperationNode

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& 	op,
					 pNode 						left,
					 pNode 						right):
	_left(left), _right(right), _op(op)
{	}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const
{
	switch (_op) {
	case LogicalOperation::And:
		return _left->Evaluate(date, event) && _right->Evaluate(date, event);
	case LogicalOperation::Or:
		return _left->Evaluate(date, event) || _right->Evaluate(date, event);
	}
}


































