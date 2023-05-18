using System;
using System.Collections.Generic;

namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
	internal class GameBoard
	{
		private struct sequanceCounter
		{
			internal int m_XCounter;
			internal int m_OCounter;

			internal bool IsASequance(int i_SequanceLength)
			{
				if(m_XCounter + m_OCounter == i_SequanceLength)
				{
					if(m_XCounter == 0 || m_OCounter == 0)
					{
						return true;
					}
				}

				return false;		
			}
			internal void ResetSequanceCounter()
			{
				m_XCounter = m_OCounter = 0;
			}
        }

        private SquereType[,] m_Matrix;
		private int m_NumOfMarkedSqueres;
		private bool m_IsThereASequance;
		private sequanceCounter[] m_Rows;
		private sequanceCounter[] m_Columns;
		private sequanceCounter m_MainDiagnol;
		private sequanceCounter m_SeconedDiagnol;

		internal SquereType[,] Matrix
		{
			get
			{
				return m_Matrix;
			}
		}
		internal GameBoard(int i_MatrixSize)
		{
			m_Matrix = new SquereType[i_MatrixSize,i_MatrixSize];
			m_NumOfMarkedSqueres = 0;
			m_IsThereASequance = false;
			m_Rows = new sequanceCounter[i_MatrixSize];
			m_Columns = new sequanceCounter[i_MatrixSize];
			m_MainDiagnol = new sequanceCounter();
			m_SeconedDiagnol = new sequanceCounter();
		}
		internal bool IsThereASequance
        {
			get
			{
				return m_IsThereASequance;
			}
			set
			{
				m_IsThereASequance = value;
			}
		}
        internal bool AddNewSymbol(SquereType i_Symbol, int i_row, int i_col)
		{
			if (IsSquareEmpty(i_row, i_col))
			{
				m_Matrix[i_row, i_col] = i_Symbol;
				updateSeqaunceCounters(i_Symbol, i_row, i_col);
                m_IsThereASequance = isThereASequance(i_row, i_col);
				m_NumOfMarkedSqueres++;
                return true;
			}
			else
			{
				return false;
			}
		}
		internal bool IsSquareEmpty(int i_row, int i_col)
		{
			return m_Matrix[i_row, i_col].IsEmpty();

        }
        private void updateSeqaunceCounters(SquereType i_Symbol, int i_row, int i_col)
		{
			if(i_Symbol.IsX())
			{ 
				m_Rows[i_row].m_XCounter++;
				m_Columns[i_col].m_XCounter++;
			}
			else
			{
                m_Rows[i_row].m_OCounter++;
                m_Columns[i_col].m_OCounter++;
            }

            updateDiagnol(i_Symbol, i_row, i_col);
        }
        private void updateDiagnol(SquereType i_Symbol, int i_row, int i_col)
		{
            if (i_row == i_col)
            {
                if(i_Symbol.IsX())
				{
					m_MainDiagnol.m_XCounter++;
				}
				else
				{
                    m_MainDiagnol.m_OCounter++;
                }
            }

            if(i_row == m_Matrix.GetLength(0) - 1 - i_col)
            {
                if (i_Symbol.IsX())
                {
					m_SeconedDiagnol.m_XCounter++;
                }
                else
                {
                    m_SeconedDiagnol.m_OCounter++;
                }
            }
        }
		
        internal bool IsBoardFull()
		{
			return m_NumOfMarkedSqueres == (m_Matrix.Length);
		}
        private bool isThereASequance(int i_row, int i_col)
		{
			int v_GeneralLength = m_Matrix.GetLength(0);

			return (m_Rows[i_row].IsASequance(v_GeneralLength) ||
				m_Columns[i_col].IsASequance(v_GeneralLength) ||
				m_MainDiagnol.IsASequance(v_GeneralLength) ||
				m_SeconedDiagnol.IsASequance(v_GeneralLength));
		}
		internal void ResetGameBoard()
		{
			resetBoard();
            m_NumOfMarkedSqueres = 0;
            m_IsThereASequance = false;
			resetCounters();
        }
		private void resetBoard()
		{
			int v_BoardSize = m_Matrix.GetLength(0);

            for (int i = 0; i < v_BoardSize; ++i)
			{
				for(int j = 0; j < v_BoardSize; ++j)
				{
					m_Matrix[i, j].resetSquere();
                }				
			}
		}
		private void resetCounters()
		{
            int v_BoardSize = m_Matrix.GetLength(0);

			for(int i = 0; i< v_BoardSize; ++i)
			{
                m_Rows[i].ResetSequanceCounter();
                m_Columns[i].ResetSequanceCounter();
            }

            m_MainDiagnol.ResetSequanceCounter();
            m_SeconedDiagnol.ResetSequanceCounter();
        }
		
    }
}

