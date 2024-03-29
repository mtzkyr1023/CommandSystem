#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <list>

//コマンド基底クラス
class CCommand {
public:
	enum State {
		ACTIVE = 0,
		SLEEP = 1,
	};

protected:
	int m_enableTime;	//コマンド有効回数
	State m_status;		//コマンド状態

protected:
	CCommand() : m_enableTime(1), m_status(State::ACTIVE) {}

	//コマンドの中身
	virtual bool Internal() = 0;

	virtual void StateControll() {}

public:
	virtual ~CCommand() {}

	virtual int Run() {
		StateControll();

		if (m_status == ACTIVE) {
			if (!Internal())
				return -1;
		}

		return m_enableTime;
	}
	
	//コマンド無効化
	void SetDisable() { m_enableTime = 0; }
};


//コマンドマネージャ基底クラス
class CCommandManager {
protected:
	//コマンドリスト
	std::list<CCommand*> m_commandList;

public:
	CCommandManager() {}

	virtual ~CCommandManager() {
		for (auto ite = m_commandList.begin(); ite != m_commandList.end(); ite++) {
			delete (*ite);
			(*ite) = nullptr;
		}
	}

	//コマンドの登録
	void Regist(CCommand* command) { m_commandList.push_back(command); }

	//コマンド実行
	virtual bool RunCommand() {
		for (auto ite = m_commandList.begin(); ite != m_commandList.end();) {
			int res = (*ite)->Run();
			if (res == -1)
				return false;

			if (res == 0) {
				delete (*ite);
				(*ite) = nullptr;
				ite = m_commandList.erase(ite);
				continue;
			}

			ite++;
		}

		return true;
	}
};


#endif