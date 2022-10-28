#include "SceneManager.h"

namespace EM
{
	// Get Component Name Via Type - Done
	// Check for null component Array - Done
	// Shorten EntityToIndexMap
	// Serialize IndexToEntityMap (use mSize)
	// Clean EntityToIndex, IndexToEntity, ComponentArrays

	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		ecs.ResetEntities();
		ecs.SetTotalEntitiesForWorldBuild(obj["Number of Entities"]["Entities"].GetUint());
		for (ComponentType i = 0; i < ecs.GetTotalRegisteredComponents(); ++i)
		{
			ecs.ClearArrayForWorldBuild(i);
			for (Entity j = 1; j <= ecs.GetTotalEntities(); ++j)
			{
				Signature signature(obj["EntitySignatures"][(j-1)].GetString());
				if (signature.test(i))
				{
					//ADD COMPONENTS HERE FOR DESERIALIZE
					if (ecs.GetComponentTypeName(i) == "Transform")
					{
						Transform transform;
						if (transform.Deserialize(obj["Components"][ecs.GetComponentTypeName(i).c_str()][j - 1].GetObj()))
						{
							ecs.AddComponent<Transform>(j, transform);
						}
					}
					if (ecs.GetComponentTypeName(i) == "RigidBody")
					{
						RigidBody rigidbody;
						if (rigidbody.Deserialize(obj["Components"][ecs.GetComponentTypeName(i).c_str()][j - 1].GetObj()))
						{
							ecs.AddComponent<RigidBody>(j, rigidbody);
						}
					}
				}
			}
			for (Entity j = 1; j < MAX_ENTITIES; ++j)
			{
				ecs.GetEntityToIndexMapECS(i)[j] = obj["EntityToIndexMap"][ecs.GetComponentTypeName(i).c_str()][j].GetUint();
				ecs.GetIndexToEntityMapECS(i)[j] = obj["IndexToEntityMap"][ecs.GetComponentTypeName(i).c_str()][j].GetUint();
			}
		}
		return true;
	}

	bool SceneManager::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		writer->Key("Number of Entities");
		writer->StartObject();
		writer->Key("Entities");
		writer->Uint(ecs.GetTotalEntities());
		writer->EndObject();

		writer->Key("EntityToIndexMap");
		writer->StartObject();
		for (ComponentType i = 0; i < ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			for (auto j = ecs.GetEntityToIndexMapECS(i).begin(); j != ecs.GetEntityToIndexMapECS(i).end(); ++j)
			{
				writer->Uint(*j);
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->Key("IndexToEntityMap");
		writer->StartObject();
		for (ComponentType i = 0; i < ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			for (auto j = ecs.GetIndexToEntityMapECS(i).begin(); j != ecs.GetIndexToEntityMapECS(i).end(); ++j)
			{
				writer->Uint(*j);
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->Key("EntitySignatures");
		writer->StartArray();
		for (Entity i = 1; i <= ecs.GetTotalEntities(); ++i)
		{
			writer->String(ecs.GetEntitySignature(i).to_string().c_str());
		}
		writer->EndArray();

		writer->Key("Components");
		writer->StartObject();
		for (ComponentType i = 0; i < ecs.GetTotalRegisteredComponents(); ++i)
		{
			writer->Key(ecs.GetComponentTypeName(i).c_str());
			writer->StartArray();
			for (Entity j = 1; j <= ecs.GetTotalEntities(); ++j)
			{
				if (ecs.GetEntitySignature(j).test(i))
				{
					//ADD COMPONENTS HERE FOR SERIALIZE
					std::cout << "Component Serialized" << std::endl;
					if (ecs.GetComponentTypeName(i) == "Transform")
					{
						ecs.GetComponent<Transform>(j).Serialize(writer);
					}

					if (ecs.GetComponentTypeName(i) == "RigidBody")
					{
						ecs.GetComponent<RigidBody>(j).Serialize(writer);
					}
				}
			}
			writer->EndArray();
		}
		writer->EndObject();

		writer->EndObject();
		return true;
	}
}