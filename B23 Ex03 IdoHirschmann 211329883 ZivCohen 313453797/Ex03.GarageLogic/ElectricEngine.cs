using System;
namespace Ex03.GarageLogic
{
	public class ElectricEngine:Engine
	{
        const int k_NumOfParamsNeedsToCharge = 1; 
        private float m_HoursLeft = 0;
        private float? m_MaxHoursCapacity = null;

        internal float TimeLeft
        {
            get
            {
                return m_HoursLeft;
            }
            set
            {
                m_HoursLeft = value;
            }
        }
        internal float? MaxHoursCapacity
        {
            get 
            {
                return m_MaxHoursCapacity;
            }
            set 
            { 
                m_MaxHoursCapacity = value;
            }
        }
        internal override void FillVehicle(float i_Amount)
        {
            if(m_HoursLeft + i_Amount <= m_MaxHoursCapacity)
            {
                m_HoursLeft += i_Amount;
            }
            else
            {
                throw new ValueOutOfRangeException(0, (float)m_MaxHoursCapacity - m_HoursLeft);
            }
            
        }
        internal override float CalcEnergyPercentage()
        {
            return (m_HoursLeft / (float)m_MaxHoursCapacity) * 100; 
        }
        public override string ToString()
        {
            string v_ElectricEngineData;

            v_ElectricEngineData = string.Format("hours of energy left {0}", m_HoursLeft);

            return v_ElectricEngineData;
        }
        internal override string[] GetFillParams()
        {
            string[] v_ParamsToCharge = new string[k_NumOfParamsNeedsToCharge];

            v_ParamsToCharge[0] = string.Format("Hours to charge (max {0} hoars)", (m_MaxHoursCapacity-m_HoursLeft));

            return v_ParamsToCharge;
        }
        internal override void ResetEngine()
        {
            m_HoursLeft = 0;
        }
    }
}

