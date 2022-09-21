#include"ExoEngine/EntryPoint.h"

class EXOMATA : public EM::Application
{
public:
	EXOMATA() 
	{

	}
	~EXOMATA() 
	{

	}
};

EM::Application* EM::CreateApplication()
{
	return new EXOMATA();
}
