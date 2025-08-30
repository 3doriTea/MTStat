#pragma once
#include <functional>
#include <map>
#include <concepts>

namespace mtstat
{
	template<typename T>
	concept EnumT = std::is_enum_v<T>;
	
	/// <summary>
	/// �|�������t�B�Y���𔲂��ɂ����X�e�[�g�N���X
	/// </summary>
	/// <typeparam name="StatEnumT">�X�e�[�g�Ɏg�p����񋓌^</typeparam>
	template<EnumT StatEnumT>
	class MTStat
	{
	public:
		MTStat() : stat_{} {}
		~MTStat() {}

		MTStat& OnStart(const StatEnumT _statEnum, const std::function<void()>& _callback);
		MTStat& OnUpdate(const StatEnumT _statEnum, const std::function<void()>& _callback);
		MTStat& OnEnd(const StatEnumT _statEnum, const std::function<void()>& _callback);

		void Update();
		void Change(const StatEnumT _nextStat);

	private:
		StatEnumT stat_;  // ���݂̃X�e�[�g
		std::map<StatEnumT, std::function<void()>> updateFuncs_;  // �o�^����Ă���X�V�֐�
		std::map<StatEnumT, std::function<void()>> startFuncs_;   // �o�^����Ă���J�n�֐�
		std::map<StatEnumT, std::function<void()>> endFuncs_;     // �o�^����Ă���I���֐�
	};

	template<EnumT StatEnumT>
	inline MTStat<StatEnumT>& MTStat<StatEnumT>::OnStart(const StatEnumT _statEnum, const std::function<void()>& _callback)
	{
		startFuncs_.insert({ _statEnum, _callback });
		return *this;
	}

	template<EnumT StatEnumT>
	inline MTStat<StatEnumT>& MTStat<StatEnumT>::OnUpdate(const StatEnumT _statEnum, const std::function<void()>& _callback)
	{
		updateFuncs_.insert({ _statEnum, _callback });
		return *this;
	}

	template<EnumT StatEnumT>
	inline MTStat<StatEnumT>& MTStat<StatEnumT>::OnEnd(const StatEnumT _statEnum, const std::function<void()>& _callback)
	{
		endFuncs_.insert({ _statEnum, _callback });
		return *this;
	}

	template<EnumT StatEnumT>
	inline void MTStat<StatEnumT>::Update()
	{
		if (updateFuncs_.count(stat_))
		{
			updateFuncs_[stat_]();
		}
	}
	
	template<EnumT StatEnumT>
	inline void MTStat<StatEnumT>::Change(const StatEnumT _nextStat)
	{
		if (endFuncs_.count(stat_))
		{
			endFuncs_[stat_]();
		}

		stat_ = _nextStat;

		if (startFuncs_.count(_nextStat))
		{
			startFuncs_[_nextStat]();
		}
	}
}
