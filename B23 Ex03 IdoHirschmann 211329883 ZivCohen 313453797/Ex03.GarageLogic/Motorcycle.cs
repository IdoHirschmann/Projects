using System;
namespace Ex03.GarageLogic
{
	internal class Motorcycle : Vehicle
	{
		private eMotorcycleLicenseType? m_LicenseType = null;
		private int? m_EngineVolume = null;

        private const int k_NumOfUniqueField = 3;
        private const int k_NumOfWheels = 2;
        private const float k_MaxTyrePressuere = 31f;
        private const float k_MaxFuelLitersCapcity = 6.4f;
        private const float k_MaxElectricityHoursCapacity = 2.6f;
        private const eFuelTypes k_FuelType = eFuelTypes.Octan98;

        internal Motorcycle(eEngineTypes i_EngineType)
        {
            Wheels = ObjectFactory.CreateWheels(k_NumOfWheels, k_MaxTyrePressuere);
            Engine = ObjectFactory.CreateEngine(i_EngineType);

            switch (i_EngineType)
            {
                case eEngineTypes.Electric:
                    {
                        ElectricEngine v_ElectricEngine = Engine as ElectricEngine;

                        v_ElectricEngine.MaxHoursCapacity = k_MaxElectricityHoursCapacity;

                        break;
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
        internal eMotorcycleLicenseType? LicenseType
		{
			get
			{
				return m_LicenseType;
			}
			set
			{
				m_LicenseType = value;
			}
		}
        internal int? EngineVolum
        {
            get
            {
                return m_EngineVolume;
            }
            set
            {
                m_EngineVolume = value;
            }
        }
        internal override string[] GetUniqueVehicleFields()
        {
            string[] v_LicenseTypes = Enum.GetNames(typeof(eMotorcycleLicenseType));
            string v_LicenseTypeCombain = string.Join(", ", v_LicenseTypes);
            string[] v_MotorcycleFields = new string[k_NumOfUniqueField];

            v_MotorcycleFields[0] = "Motorcycle model name";
            v_MotorcycleFields[1] = string.Format("License type ({0})", v_LicenseTypeCombain);
            v_MotorcycleFields[2] = "Engine capacity";

            return v_MotorcycleFields;
        }
        internal override void SetUniqueVehicleFields(string[] i_UniqueFields)
        {
            bool v_IsLicenseTypeValid = Enum.TryParse<eMotorcycleLicenseType>(i_UniqueFields[1], out eMotorcycleLicenseType v_LicenseType);
            bool v_IsEngineVolumeValid= int.TryParse(i_UniqueFields[2], out int v_EngineVolume);

            if (!v_IsLicenseTypeValid)
            {
                throw new FormatException("Invalid license type.");
            }
            else if(!v_IsEngineVolumeValid || v_EngineVolume <= 0)
            {
                throw new FormatException("Invalid engine volume.");
            }
            else
            {
                this.ModelName = i_UniqueFields[0];
                m_LicenseType = v_LicenseType;
                m_EngineVolume = v_EngineVolume;
            }
        }
        internal override eFuelTypes GetFuelType()
        {
            return k_FuelType;
        }
    }
}

