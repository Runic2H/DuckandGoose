#include "ExoEngine.h"
#include "ExoEngine/EntryPoint.h"

class Exomata : public EM::Application
{
	public:
	/*!*************************************************************************
	Constructor for Exomata
	****************************************************************************/
	Exomata() 
	{
		
	}

	/*!*************************************************************************
	Destructor for IBuffer
	****************************************************************************/
	~Exomata() 
	{
	
	}
		
};

/*!*************************************************************************
Exomata Create Application
****************************************************************************/
EM::Application* EM::CreateApplication()
{
		return new Exomata();
}


