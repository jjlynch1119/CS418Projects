//CS418 Jeremy Lynch P01DF

#include "PuzzleMove.h"
#include <list>
#include <iostream>

bool isMember(PuzzleState& state, list<PuzzleMove>& visited)
{
	bool isMember = false;

	for (auto it = visited.begin(); it != visited.end(); it++)
	{
		if (it->getState() == state)
			isMember = true;
	}

	return isMember;
}

void expandState(PuzzleState& state, list<PuzzleMove>& closed, list<PuzzleMove>& open)
{
	if (state.canMoveDown())
	{
		PuzzleState down = state.moveBlankDown();

		if (!isMember(down, closed) && !isMember(down, open))	//Check if visited already
			open.push_front(PuzzleMove(down, state, MoveType::down));	//Push to stack
	}

	if (state.canMoveLeft())
	{
		PuzzleState left = state.moveBlankLeft();

		if (!isMember(left, closed) && !isMember(left, open))
			open.push_front(PuzzleMove(left, state, MoveType::left));
	}

	if (state.canMoveUp())
	{
		PuzzleState up = state.moveBlankUp();

		if (!isMember(up, closed) && !isMember(up, open))
			open.push_front(PuzzleMove(up, state, MoveType::up));
	}

	if (state.canMoveRight())
	{
		PuzzleState right = state.moveBlankRight();

		if (!isMember(right, closed) && !isMember(right, open))
			open.push_front(PuzzleMove(right, state, MoveType::right));
	}
}

list<PuzzleMove> buildSolutionList(list<PuzzleMove>& closed)
{
	list<PuzzleMove> solutionList;	//List to build

	solutionList.push_front(closed.back());	//Push goal node to front of solution list

	auto currMove = closed.rbegin();	//Set move were comparing on to the goal node

	for (auto it = currMove; it != closed.rend(); it++)
	{
		if (currMove->getParent() == it->getState())	//Compare the parent state of the PuzzleMove were on to the state of the PuzzleMove we are iterating on
		{
			solutionList.push_front(*it);	//Push to the front of the solution list
			currMove = it;	//Set the node to start the loop on as the node we just pushed to the solution list so we don't go over nodes we already looked at
		}
	}

	return solutionList;
}

void printSolution(list<PuzzleMove>& closed)
{
	list<PuzzleMove> solution;
	int nodesExpanded = closed.size() - 1;

	solution = buildSolutionList(closed);
	int pathLength = solution.size() - 1;

	cout << "*** Solution Found ***";

	for (auto it = solution.begin(); it != solution.end(); it++)
	{
		switch (it->getMoveName())
		{
		case 0:
			cout << "\ndown\n";
			break;
		case 1:
			cout << "\nleft\n";
			break;
		case 2:
			cout << "\nright\n";
			break;
		case 3:
			cout << "\nup\n";
			break;
		}

		it->getState().print(cout);
		cout << "\n";

	}

	cout << "\nNumber of nodes expanded: " << nodesExpanded;
	cout << "\nPath length to Goal: " << pathLength;
	cout << "\n\n";
}

void findSolution(PuzzleState& start, PuzzleState& goal)
{
	list<PuzzleMove> closed;	//Visited
	list<PuzzleMove> open;		//Frontier
	PuzzleMove initial{ start, PuzzleState::NullState, MoveType::nullMove };

	open.push_back(initial);

	while (!open.empty())
	{
		PuzzleState current = open.front().getState();

		closed.push_back(open.front());	//Push current node to closed list
		open.pop_front();

		if (current == goal)
		{
			printSolution(closed);	//Goal is at back of closed list
			return;
		}
		else
		{
			expandState(current, closed, open);	//Goal not found keep expanding
		}
	}

	cout << "No Solution found!\n";
}

int main()
{
	cout << " *** P01 Puzzle Uninformed Search - DFS ***\n";
	while (true)
	{
		list<PuzzleMove> closed;
		int n;

		cout << "<======================================================>\n";
		cout << "Enter number of rows and columns: ";
		cin >> n;
		PuzzleState start{ n, n };
		PuzzleState goal{ n, n };

		cout << "\nEnter Start State row by row:\n";
		start.read(cin);
		cout << "\n";

		cout << "Enter Goal State row by row:\n";
		goal.read(cin);
		cout << "\n";

		if (start == goal)
		{
			cout << "*** Solution found immediately: start state is the goal state. ***\n\n";
		}
		else
		{
			findSolution(start, goal);
		}
	}
}