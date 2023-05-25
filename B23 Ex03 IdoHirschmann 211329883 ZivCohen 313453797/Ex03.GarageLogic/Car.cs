using System;
namespace Ex03.GarageLogic
{
	internal class Car : Vehicle
	{
		private eCarColors? m_CarColor = null;
		private short? m_NumOfDoors = null;

        private const int k_MinNumOfDoors = 2;
        private const int k_MaxNumOfDoors = 5;
        private const int k_NumOfUniqueField = 3;
        private const int k_NumOfWheels = 5;
		private const float k_MaxTyrePressuere = 33f;
		private const float k_MaxFuelLitersCapcity = 46f;
        private const float k_MaxElectricityHoursCapacity = 5.2f;
        private const eFuelTypes k_FuelType = eFuelTypes.Octan95;

		internal Car(eEngineTypes i_EngineType)
		{
			Wheels = ObjectFactory.CreateWheels(k_NumOfWheels, k_MaxTyrePressuere);
			Engine = ObjectFactory.CreateEngine(i_EngineType);

			switch(i_EngineType)
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
		protected eCarColors? CarColor
		{
			get
			{
				return m_CarColor;
			}
			set
			{
				m_CarColor = value;
			}
		}
        protected short? NumOfDoors
        {
            get
            {
                return m_NumOfDoors;
            }
            set
            {
                if(value >=2 && value <=5)
                {
                    m_NumOfDoors = value;
                }
                else
                {
                    throw new ValueOutOfRangeException(2, 5);
                }
				
            }
        }
        internal override string[] GetUniqueVehicleFields()
        {
            string[] v_CarColors = Enum.GetNames(typeof(eCarColors));
            string v_CarColorsCombain = string.Join(", ", v_CarColors);
			string[] v_CarFields = new string[k_NumOfUniqueField];

            v_CarFields[0] = "Cars model name";
			v_CarFields[1] = string.Format("Cars color ({0})", v_CarColorsCombain);
			v_CarFields[2] = string.Format("Number of doors ({0}-{1})", k_MinNumOfDoors, k_MaxNumOfDoors);

			return v_CarFields;
        }
        internal override void SetUniqueVehicleFields(string[] i_UniqueFields)
        {
            bool v_IsColorValid = Enum.TryParse<eCarColors>(i_UniqueFields[1], out eCarColors v_Color);
            bool v_IsNumOfDoorsValid = short.TryParse(i_UniqueFields[2], out short v_NumOfDoors);

            if(!v_IsColorValid)
            {
                throw new FormatException("Invalid car color.");
            }
            else if (!v_IsNumOfDoorsValid)
            {
                throw new FormatException("Invalid input for number of doors.");
            }
            else
            {
                this.ModelName = i_UniqueFields[0];
                this.NumOfDoors = v_NumOfDoors;
                m_CarColor = v_Color;
            }
        }
        internal override eFuelTypes GetFuelType()
        {
            return k_FuelType;
        }
    }
}

