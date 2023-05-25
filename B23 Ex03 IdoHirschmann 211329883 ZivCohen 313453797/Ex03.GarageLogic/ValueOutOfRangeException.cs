using System;
namespace Ex03.GarageLogic
{
	public class ValueOutOfRangeException : Exception
	{
		private float m_MaxValue;
		private float m_MinValue;

		public ValueOutOfRangeException(float i_MinValue, float i_MaxValue):base(string.Format("Value is out of range. Valid range is {0}-{1}", i_MinValue, i_MaxValue))
		{
			m_MinValue = i_MinValue;
			m_MaxValue = i_MaxValue;
		}
	}
}

