using System;
namespace Ex03.GarageLogic
{
	public class Wheel
	{
		const int k_NumOfFeildsToSet = 2;
		private string? m_Manufacturer = null;
		private float m_CurrentTyrePressure = 0;
		private float? m_MaxTyrePressureCapacity = null;

		internal string? Manufacturer
		{
			get 
			{
				return m_Manufacturer;
			}	
			set
			{
				m_Manufacturer = value; 
			}
		}
		internal float CurrentAirPressure
		{
			get
			{
				return m_CurrentTyrePressure; 
			}
			set
			{
				if(value > 0 && value <= m_MaxTyrePressureCapacity)
				{
					m_CurrentTyrePressure = value;
				}
				else
				{
					throw new ValueOutOfRangeException(0, (float)m_MaxTyrePressureCapacity);
				}
			}
		}
		internal float? MaxAirPressureCapacity
		{
			get
			{
				return  m_MaxTyrePressureCapacity;
			}
			set
			{
				m_MaxTyrePressureCapacity = value;	
			}
		}
		internal void FillAirPressure (float i_Amount)
		{
			if(m_CurrentTyrePressure + i_Amount > m_MaxTyrePressureCapacity)
			{
				throw new ValueOutOfRangeException(0, (float)m_MaxTyrePressureCapacity - m_CurrentTyrePressure);
			}
			else
			{
				m_CurrentTyrePressure += i_Amount;
			}
		}
		internal string[] GetWheelsFileds()
		{
			string[] v_WheelsData = new string[k_NumOfFeildsToSet];

			v_WheelsData[0] = "Wheel's manufacturer name";
			v_WheelsData[1] = string.Format("Wheel's air pressure (max {0})", m_MaxTyrePressureCapacity);

			return v_WheelsData;
        }
		internal void SetWheelsFields(string[] i_WheelsFields)
		{
			bool v_IsTyrePressureValid = float.TryParse(i_WheelsFields[1], out float v_TyrePressure);

			if(v_IsTyrePressureValid)
			{
				m_Manufacturer = i_WheelsFields[0];
				this.CurrentAirPressure = v_TyrePressure;
			}
			else
			{
				throw new FormatException("Invalid tyre pressure input.");
			}
		}
        public override string ToString()
        {
			string v_WheelData;

			v_WheelData = string.Format("manufacturer is {0} , current tyre pressure is {1}",
				m_Manufacturer, m_CurrentTyrePressure);
			return v_WheelData;
        }
		internal int GetNumberOfFeildsToSet()
		{
			return k_NumOfFeildsToSet;
		}
		internal void ResetWheel()
		{
			m_CurrentTyrePressure = 0;
			m_Manufacturer = null;
		}
    }
}

