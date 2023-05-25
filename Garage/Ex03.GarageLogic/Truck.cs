using System;
namespace Ex03.GarageLogic
{
	internal class Truck : Vehicle
	{
        private bool? m_IsDangerousCargo = null;
        private float? m_CargoVolume = null;

        private const int k_NumOfUniqueField = 3;
        private const int k_NumOfWheels = 14;
        private const float k_MaxTyrePressuere = 26f;
        private const float k_MaxFuelLitersCapcity = 135f;
        private const eFuelTypes k_FuelType = eFuelTypes.Soler;

        internal Truck(eEngineTypes i_EngineType)
        {
            Wheels = ObjectFactory.CreateWheels(k_NumOfWheels, k_MaxTyrePressuere);
            Engine = ObjectFactory.CreateEngine(i_EngineType);

            //currently the only option is fuel truck 
            switch (i_EngineType)
            {
                case eEngineTypes.Electric:
                    {
                        throw new FormatException("Invalid input. We are currently not supporting electric truck");
                    }
                case eEngineTypes.Fuel:
                    {
                        FuelEngine v_FuelEngine = Engine as FuelEngine;

                        v_FuelEngine.FuelType = k_FuelType;
                        v_FuelEngine.MaxFuelLitersCapacity = k_MaxFuelLitersCapcity;

                        break;
                    }
            }
        }
        internal bool? IsDangerousCargo
        {
            get
            {
                return m_IsDangerousCargo;
            }
            set
            {
                m_IsDangerousCargo = value;
            }
        }
        internal float? CargoVolume
        {
            get
            {
                return m_CargoVolume;
            }
            set
            {
                m_CargoVolume = value;
            }
        }
        internal override string[] GetUniqueVehicleFields()
        {
            string[] v_TruckFields = new string[k_NumOfUniqueField];

            v_TruckFields[0] = "Truck model name";
            v_TruckFields[1] = "Is dangerous cargo onboard (true/false)";
            v_TruckFields[2] = "Cargo volume";

            return v_TruckFields;
        }
        internal override void SetUniqueVehicleFields(string[] i_UniqueFields)
        {
            bool v_IsCargoDangerousValid = bool.TryParse(i_UniqueFields[1], out bool v_IsCargoDangerous);
            bool v_IsCargoVolumeValid = float.TryParse(i_UniqueFields[2], out float v_CargoVolume);

            if (!v_IsCargoDangerousValid)
            {
                throw new FormatException("Invalid input for if cargo is dangerous or not.");
            }
            else if(!v_IsCargoVolumeValid)
            {
                throw new FormatException("Invalid cargo input.");
            }
            else
            {
                this.ModelName = i_UniqueFields[0];
                m_IsDangerousCargo = v_IsCargoDangerous;
                m_CargoVolume = v_CargoVolume;
            }
        }
        internal override eFuelTypes GetFuelType()
        {
            return k_FuelType;
        }
    }
}

