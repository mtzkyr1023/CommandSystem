#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <list>

//�R�}���h���N���X
class CCommand {
public:
	enum State {
		ACTIVE = 0,
		SLEEP = 1,
	};

protected:
	int m_enableTime;	//�R�}���h�L����
	State m_status;		//�R�}���h���
	bool m_enable;		//�R�}���h�L��/����

protected:
	CCommand() : m_enableTime(1), m_status(State::ACTIVE), m_enable(false) {}

	//�R�}���h�̒��g
	virtual bool Internal() = 0;

	virtual void StateControll() {}

public:
	virtual ~CCommand() {}

	virtual int Run() {
		StateControll();

		if (m_status == ACTIVE)
			m_enable = true;
		else
			m_enable = false;

		if (m_enable) {
			if (!Internal())
				return -1;
		}

		return m_enableTime;
	}
	
	//�R�}���h������
	void SetDisable() { m_enableTime = 0; m_enable = false; m_status = SLEEP; }

	bool IsEnable() { return m_enable; }

	void Active() { m_status = ACTIVE; }
};


//�R�}���h�}�l�[�W�����N���X
class CCommandManager {
protected:
	//�R�}���h���X�g
	std::list<CCommand*> m_commandList;

public:
	CCommandManager() {}

	virtual ~CCommandManager() {
		for (auto ite = m_commandList.begin(); ite != m_commandList.end(); ite++) {
			delete (*ite);
			(*ite) = nullptr;
		}
	}

	//�R�}���h�̓o�^
	void RegistFront(CCommand* command) { m_commandList.push_front(command); }
	void RegistBack(CCommand* command) { m_commandList.push_back(command); }

	//�R�}���h���s
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