using System;
using System.Runtime.CompilerServices;

namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
	internal class GameManager
	{
		private const int k_NumOfPlayers = 2;
		private GameBoard? m_GameBoard = null;
		private Player[] m_Players = new Player[k_NumOfPlayers];
		private int m_CurrentPlayer = 0;
		private Player? m_Winnner = null;

		internal GameBoard GameBoard
		{
			get
			{
				return m_GameBoard;
			}
			set
			{
				m_GameBoard = value;
			}
		}
		internal Player? Winner
		{
			get
			{
				return m_Winnner;
			}
		}
		internal Player[] Players
		{
			get
			{
				return m_Players;
			}
		}
		internal void SetOpponentType(bool i_IsComputer)
		{
			m_Players[m_CurrentPlayer] = new Player(false, SquereType.eSquereType.X);
			m_Players[k_NumOfPlayers - 1] = new Player(i_IsComputer, SquereType.eSquereType.O);
		}
		internal bool PlayNextMove(int i_Row, int i_Col)
		{
            bool v_validMove = m_GameBoard.AddNewSymbol(m_Players[m_CurrentPlayer % k_NumOfPlayers].playerType, i_Row, i_Col);
			
			if (v_validMove && !m_GameBoard.IsThereASequance) 
			{
                if (m_Players[++m_CurrentPlayer % k_NumOfPlayers].isComputer && !m_GameBoard.IsBoardFull())
				{
					ComputerPlayer.PlayNextMove(m_GameBoard);
					++m_CurrentPlayer;
				}        
			}

            if (m_GameBoard.IsThereASequance)
            {
                m_Players[++m_CurrentPlayer % k_NumOfPlayers].Score++;
                m_Winnner = m_Players[m_CurrentPlayer % k_NumOfPlayers];
            }

            return v_validMove;	
		}
		internal void PlayerRetired()
		{
			++m_CurrentPlayer;
			m_Winnner = m_Players[m_CurrentPlayer % k_NumOfPlayers];
			m_Players[m_CurrentPlayer % k_NumOfPlayers].Score++;
		}
		internal bool IsThereAWinner()
		{
			return GameBoard.IsThereASequance || m_Winnner != null;
		}
        internal bool IsGameOver()
        {
            return (IsThereAWinner() || m_GameBoard.IsBoardFull() );
        }
		internal void ResetGame()
		{
			m_GameBoard.ResetGameBoard();
			m_Winnner = null;
			m_CurrentPlayer = 0;

		}
    }
}

