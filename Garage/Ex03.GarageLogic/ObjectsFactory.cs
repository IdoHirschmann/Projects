using System;
namespace Ex03.GarageLogic
{
	internal class ObjectFactory
	{

		internal static Vehicle? CreatVehicle(eVehiclesTypes i_VehicleType , eEngineTypes i_EngineType)
		{
			Vehicle v_Vehicle = null;

			switch(i_VehicleType)
			{
				case eVehiclesTypes.Car:
					{
						v_Vehicle = new Car(i_EngineType);
						break;
					}
                case eVehiclesTypes.Motorcycle:
                    {
                        v_Vehicle = new Motorcycle(i_EngineType);
                        break;
                    }
				case eVehiclesTypes.Truck:
					{
						v_Vehicle = new Truck(i_EngineType);
						break;
					}
            }

			return v_Vehicle;
        }
		internal static Engine? CreateEngine(eEngineTypes i_EngineType)
		{
			Engine? v_Engine = null;

			if(i_EngineType == eEngineTypes.Electric)
			{
				v_Engine = new ElectricEngine();
			}
			else
			{
				v_Engine = new FuelEngine();
			}

			return v_Engine;
		}
		internal static Wheel[] CreateWheels(int i_NumOfWheels, float i_MaxTyrePresure)
		{
			Wheel[] v_Wheels = new Wheel[i_NumOfWheels];

			for(int i = 0; i < i_NumOfWheels; i ++)
			{
				v_Wheels[i] = new Wheel();
                v_Wheels[i].MaxAirPressureCapacity = i_MaxTyrePresure;
			}

			return v_Wheels;
		}
		internal static Client CreateClient()
		{
			Client v_Client = new Client();

			return v_Client;
		}
    }
}

