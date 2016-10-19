#pragma once

//#include "Identifier.h"
#include "Type.h"
#include "Action.h"
#include "ElementData.h"
//#include "OperatorElement.h"
//#include "StackFrame.h"

#include <list>

using std::list;

class StackFrame;

class ActionTable
{
public:
	//should only be called within this class except for creating the root
	ActionTable(ActionTable * parentIn) {parent=parentIn; stackFrame=parent->getStackFrame();}
	ActionTable(StackFrame * stackFrameIn) {parent=nullptr; stackFrame=stackFrameIn;}
	
	~ActionTable() {clear();}
	
	ActionPtr getBestAction(ElementData data, Type leftIn, Type rightIn);
	ActionPtr getBestAction(OperatorType opType, Type leftIn, Type rightIn);
	
	void addAction(ActionPtr in) {actions.push_back(in);}
	void addAction(ActionPtr in, OperatorType opType);
	
	StackFrame* getStackFrame() {return stackFrame;}
	
	string toString();
	
	//Identifier * getOrMakeIdentifier(string nameIn);
	
	void clear();
	
private:
	void addActionsToList(list<ActionPtr>& in, string& text);
	void addActionsToList(list<ActionPtr>& in, OperatorType opType);
	ActionPtr resolveOverload(list<ActionPtr>& in, Type leftIn, Type rightIn);
	
	ActionTable * parent=nullptr;
	list<ActionPtr> actions;
	list<ActionPtr> operators[OP_TYPE_OVERRIDEABLE_LAST];
	
	StackFrame* stackFrame;
};

typedef shared_ptr<ActionTable> ActionTablePtr;