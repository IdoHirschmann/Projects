using System;
namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
	internal struct SquereType
	{
		internal enum eSquereType
		{
			Empty,
			X,
			O
		}

		private eSquereType m_Type;

		internal eSquereType Type
		{
			get
			{
				return m_Type;
			}

			set 
			{
				m_Type = value;
			}
		}
		internal bool IsX()
		{
			return m_Type == eSquereType.X;
		}
        internal bool IsO()
        {
            return m_Type == eSquereType.O;
        }
        internal bool IsEmpty()
		{
			return m_Type == eSquereType.Empty;
		}
		internal void resetSquere()
		{
			m_Type = eSquereType.Empty;
		}
    }
}

