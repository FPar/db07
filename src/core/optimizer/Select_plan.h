#ifndef QUERY_PLAN_H
#define QUERY_PLAN_H

#include "control/Destination_receiver.h"
#include "Plan.h"
#include "plan/Plan_node.h"

namespace db07
{
	class Select_plan : public Plan
	{
	public:
		Select_plan(Destination_receiver* receiver, Plan_node* root) :
			_receiver(receiver), _root(root)
		{
		}

		void execute() override;

	private:
		Destination_receiver* _receiver;
		Plan_node* _root;
	};
}

#endif // !QUERY_PLAN_H
