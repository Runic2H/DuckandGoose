#pragma once

#include "ECS.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "Platform/System/SystemManager.h"
#include "Types.h"
#include "empch.h"
#include "Serialization/JSONserialization.h"
#include "Platform/Graphics/Graphics.h"

namespace EM
{
	extern ECS ecs;

	template <typename T>
	class SceneViewer : JSONSerializer
	{
	public:
		virtual ~SceneViewer() {};
		void Init()
		{
			for (std::vector<T>::const_iterator it = mComponents.begin(); it != mComponents.end(); it++)
			{
				ecs.RegisterComponent<*it>();
			}
		}
		virtual bool Deserialize(const std::string& s) {

			rapidjson::Document doc;
			if (!InitDocument(s, doc))
				return false;

			if (!doc.IsArray())
				return false;

			for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
			{
				Product p;
				p.Deserialize(*itr);
				_products.push_back(p);
			}
		}

		virtual bool Deserialize(const rapidjson::Value& obj) { return false };
		virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
		{
			writer->StartArray();

			for (std::vector<T>::const_iterator it = mComponents.begin(); it != mComponents.end(); it++)
			{
				(*it).Serialize(writer);
			}

			writer->EndArray();
		}

		std::vector<T>& ComponentList() { return mComponents; }

	private:
		std::vector<T> mComponents;
	};
}