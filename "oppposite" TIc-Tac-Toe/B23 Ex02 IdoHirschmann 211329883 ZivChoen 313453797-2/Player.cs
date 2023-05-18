using System;
namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
	internal struct Player
	{
		private SquereType m_playerType = new SquereType();
		private bool m_isComputer;
		private int m_score;

		internal Player(bool i_IsComputer, SquereType.eSquereType i_PlayerType)
		{
			m_playerType.Type = i_PlayerType;
			m_isComputer = i_IsComputer;
			m_score = 0;
		}

		internal SquereType playerType
		{
			get
			{
				return m_playerType;
			}
		}
		internal bool isComputer
		{
			get
			{
				return m_isComputer;
			}
		}
		internal int Score
		{
			get
			{
				return m_score;
			}
			set
			{
				m_score = value;
			}
		}

	}
}
