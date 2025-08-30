#include <iostream>
#include "MTStat/MTStat.h"

int main()
{
	using std::cout;
	using std::endl;

	enum STATE
	{
		A,
		B,
		C,
	};

	mtstat::MTStat<STATE> testState{};

	testState
		.OnStart(STATE::A, [&]()
		{
			cout << "Start A." << endl;
		})
		.OnUpdate(STATE::A, [&]()
		{
			cout << "Update A." << endl;
		})
		.OnEnd(STATE::A, [&]()
		{
			cout << "End A." << endl;
		})
		
		.OnStart(STATE::B, [&]()
		{
			cout << "Start B." << endl;
		})
		.OnUpdate(STATE::B, [&]()
		{
			cout << "Update B." << endl;
		})
		.OnEnd(STATE::B, [&]()
		{
			cout << "End B." << endl;
		})

		.OnStart(STATE::C, [&]()
		{
			cout << "Start C." << endl;
		})
		.OnUpdate(STATE::C, [&]()
		{
			cout << "Update C." << endl;
		})
		.OnEnd(STATE::C, [&]()
		{
			cout << "End C." << endl;
		});

	for (int i = 0; i < 10; i++)
	{
		if (i == 3)
		{
			testState.Change(STATE::B);
		}
		else if (i == 6)
		{
			testState.Change(STATE::C);
		}
		testState.Update();
	}

	system("pause");

	return 0;
}
