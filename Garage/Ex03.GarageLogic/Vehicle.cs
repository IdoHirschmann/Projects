using System;
namespace Ex03.GarageLogic
{
	internal abstract class Vehicle
	{
		private string? m_ModelName = null;
		private string? m_LicenseNumber = null;
		private Wheel[]? m_Wheels = null;
		private Engine? m_Engine = null;
        private float m_EnergyPercentageLeft = 0;

        internal float EnergyPercentageLeft
        {
            get
            {
                return m_EnergyPercentageLeft;
            }
            set
            {
                m_EnergyPercentageLeft = value;
            }
        }
        protected string? ModelName
		{
			get
			{
				return m_ModelName;
			}
			set
			{
				m_ModelName = value;
			}
        }
        internal string? LicenseNumber
        {
            get
            {
				return m_LicenseNumber;
            }
            set
            {
                m_LicenseNumber = value;
            }
        }
        internal Wheel[]? Wheels
        {
            get
            {
                return m_Wheels;
            }
            set
            {
                m_Wheels = value;
            }
        }
        internal Engine? Engine
        {
            get
            {
                return m_Engine;
            }
            set
            {
                m_Engine = value;
            }
        }
        internal void FillVehicle(float i_Amount)
        {
                m_Engine.FillVehicle(i_Amount);
                m_EnergyPercentageLeft = m_Engine.CalcEnergyPercentage();
        }
        internal void FillWheels(float i_Amount)
        {
            if(m_Wheels != null)
            {
                foreach(Wheel wheel in m_Wheels)
                {                                      
                    wheel.FillAirPressure(i_Amount);                  
                }
            }  
        }
        internal abstract string[] GetUniqueVehicleFields();
        internal abstract void SetUniqueVehicleFields(string[] i_UniqueFields);
        internal abstract eFuelTypes GetFuelType();
        public override string ToString()
        {
            string v_VehicleData =
                string.Format(@"models name is {0},
license number is {1},
energy percentage of energy left {2},
{3},
{4}.",
                m_ModelName, m_LicenseNumber, m_EnergyPercentageLeft, m_Wheels[0].ToString(), m_Engine.ToString());
            return v_VehicleData;
        }
        internal string[] GetVehicleFields()
        {
            string[] v_VehicleUniqueFields = GetUniqueVehicleFields();
            string[] v_WheelsFeilds = m_Wheels[0].GetWheelsFileds();
            string[] v_FillEngineFields = m_Engine.GetFillParams();
            string[] v_CombainVehicleFields = new string[v_VehicleUniqueFields.Length + v_WheelsFeilds.Length + v_FillEngineFields.Length];

            v_VehicleUniqueFields.CopyTo(v_CombainVehicleFields, 0);
            v_WheelsFeilds.CopyTo(v_CombainVehicleFields, v_VehicleUniqueFields.Length);
            v_FillEngineFields.CopyTo(v_CombainVehicleFields,v_VehicleUniqueFields.Length + v_WheelsFeilds.Length);

            return v_CombainVehicleFields;
        }
        internal void SetVehicleFields(string[] i_VehicleFields)
        {
            string[] v_WheelsFields = new string[m_Wheels[0].GetNumberOfFeildsToSet()];
            int v_StartIndexToCopy = i_VehicleFields.Length - m_Wheels[0].GetNumberOfFeildsToSet() - 1;
            bool v_IsAmountValid = float.TryParse(i_VehicleFields[i_VehicleFields.Length - 1], out float v_AmountToFill);

            SetUniqueVehicleFields(i_VehicleFields);
            Array.Copy(i_VehicleFields, v_StartIndexToCopy, v_WheelsFields, 0, m_Wheels[0].GetNumberOfFeildsToSet());
            SetWheelsFields(v_WheelsFields);
            if (!v_IsAmountValid)
            {
                throw new FormatException("Invalid input for amount");
            }
            else
            {
                FillVehicle(v_AmountToFill);
            }
        }
        public void SetWheelsFields(string[] i_WheelsFields)
        {
            foreach (Wheel v_Wheel in m_Wheels)
            {
                v_Wheel.SetWheelsFields(i_WheelsFields);
            }
        }
        internal string[] GetFillEngineParams()
        {
            return m_Engine.GetFillParams();
        }
        internal void ResetVehicle()
        {
            m_ModelName = null;
            foreach (Wheel v_Wheel in m_Wheels)
            {
                v_Wheel.ResetWheel();
            }
            m_Engine.ResetEngine();
            m_EnergyPercentageLeft = 0;

        }
    }
}

