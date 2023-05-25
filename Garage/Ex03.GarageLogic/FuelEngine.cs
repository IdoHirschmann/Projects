using System;
namespace Ex03.GarageLogic
{
	public class FuelEngine : Engine
	{
		const int k_NumOfParamsNeedsToFill = 1;
		private eFuelTypes m_FuelType;
		private float m_CurrentFuelLitersAmount = 0;
		private float? m_MaxFuelLitersCapacity = null;

		internal float CurrentFuelLitersAmount
		{
			get
			{
				return m_CurrentFuelLitersAmount;
			}
			set
			{
				m_CurrentFuelLitersAmount = value;	
			}
		}
        internal float? MaxFuelLitersCapacity
        {
            get
            {
                return m_MaxFuelLitersCapacity;
            }
            set
            {
                m_MaxFuelLitersCapacity = value;
            }
        }
        internal eFuelTypes FuelType
		{
			get 
			{
				return m_FuelType;
			}
			set 
			{
				m_FuelType = value;
			}
		}
        internal override void FillVehicle(float i_Amount)
        {
			if(m_CurrentFuelLitersAmount + i_Amount  <= m_MaxFuelLitersCapacity)
			{
				m_CurrentFuelLitersAmount += i_Amount;
			}
			else
			{
                throw new ValueOutOfRangeException(0, (float)m_MaxFuelLitersCapacity - m_CurrentFuelLitersAmount);
            }
        }
        internal override float CalcEnergyPercentage()
        {
            return (m_CurrentFuelLitersAmount / (float)m_MaxFuelLitersCapacity) * 100;
        }
        public override string ToString()
        {
			string v_FuelEngineData;

			v_FuelEngineData = string.Format("litters of fuel left - {0}, fuel type is {1}",
				m_CurrentFuelLitersAmount, m_FuelType.ToString());

			return v_FuelEngineData;
		}
        internal override string[] GetFillParams()
        {
            string[] v_ParamsToFill = new string[k_NumOfParamsNeedsToFill];

			v_ParamsToFill[0] = string.Format("Amount of liters to fill (max {0} liters)", (m_MaxFuelLitersCapacity-m_CurrentFuelLitersAmount));

            return v_ParamsToFill;
        }
        internal override void ResetEngine()
        {
            m_CurrentFuelLitersAmount = 0;
        }
    }
}

