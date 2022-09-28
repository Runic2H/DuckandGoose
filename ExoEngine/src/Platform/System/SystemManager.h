#pragma once
#include "ExoEngine/Core.h"
#include "Platform/System/System.h"

namespace EM {

	class SystemManager
	{
	public:
		SystemManager() = default;
		~SystemManager();

		void SystemIncrement(System* system);
		void SystemIndex(unsigned int index, System* system);

		//Destroy Systems
		void DeleteSystem();

	public:
		//Iterating the gameloop
		std::vector<System*>::iterator start() { return m_Systems.begin(); };
		std::vector<System*>::iterator end() { return m_Systems.end(); }

	public:

		//Start of testing ECS : Not In Use
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

			mSignatures.insert({ typeName, signature });
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;
				system->mEntities.erase(entity);
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = mSignatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->mEntities.insert(entity);
				}
				else
				{
					system->mEntities.erase(entity);
				}
			}
		}
		//End of testing ECS : Not In Use

	private:
		std::vector<System*> m_Systems;

		//For Future ECS : Not In Use
		std::unordered_map<const char*, Signature> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
	};
}