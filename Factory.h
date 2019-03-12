#ifndef _FACTORY_H_
#define _FACTORY_H_


#define SECTOR_SIZE 16


#include <vector>
#include <list>
#include <memory>


class IFactory {
public:
	virtual void Destruction() = 0;
};

class CFactoryManager {
private:
	std::list<IFactory*> m_factoryList;

protected:
	CFactoryManager() {}

public:
	void RegistFactory(IFactory* ptr) {
		m_factoryList.push_back(ptr);
	}

	void DestructAll() {
		for (auto ite = m_factoryList.begin(); ite != m_factoryList.end(); ite++) {
			(*ite)->Destruction();
		}
	}

	static CFactoryManager& Instance() {
		static CFactoryManager inst;
		return inst;
	}
};

//汎用オブジェクト管理ファクトリクラス
template<class T>
class CFactory : public IFactory {
private:
	//オブジェクト配列
	std::vector<std::shared_ptr<T>> m_objArray;

protected:
	CFactory() {
		CFactoryManager::Instance().RegistFactory(this);
	}

public:
	static CFactory<T>& Instance() {
		static CFactory inst;
		return inst;
	}

	//オブジェクト作成
	uint32_t Create(uint32_t id, std::shared_ptr<T>& out) {
		if (m_objArray.size() <= id) {
			uint32_t sectorNum = (id >> 4) + 1;
			m_objArray.resize(16 * sectorNum);
		}
		if (!m_objArray[id]) {
			m_objArray[id] = std::make_shared<T>();
			out = m_objArray[id];
		}
		else {
			out = m_objArray[id];
		}

		return id;
	}

	void ClearAll() {
		m_objArray.clear();
	}

	void Destruction() {
		std::vector<std::shared_ptr<T>>().swap(m_objArray);
	}
};

#endif