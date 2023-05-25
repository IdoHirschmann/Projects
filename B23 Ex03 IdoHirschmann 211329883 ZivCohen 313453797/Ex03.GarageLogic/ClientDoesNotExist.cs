using System;
namespace Ex03.GarageLogic
{
	public class ClientDoesNotExist : FormatException
	{
		public ClientDoesNotExist() :base("Invalid input, client does not exist")
		{
			
		}
	}
}

