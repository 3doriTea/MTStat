#pragma once

namespace mtstat
{
	template<typename StatEnumT>
	class MTStat
	{
	public:
		On(const StatEnumT)

	private:
		StatEnumT stat_;
	};
}
