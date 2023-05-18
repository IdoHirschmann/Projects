using System;
namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
    internal class ComputerPlayer
    {
        internal static void PlayNextMove(GameBoard i_GameBoard)
        {
            SquereType v_ComputerType = new SquereType();
            Random v_random = new Random();
            int v_BoardSize = i_GameBoard.Matrix.GetLength(0);
            int v_Row = v_random.Next(0, v_BoardSize);
            int v_Col = v_random.Next(0, v_BoardSize);

            v_ComputerType.Type = SquereType.eSquereType.O;

            while (!i_GameBoard.AddNewSymbol(v_ComputerType, v_Row, v_Col))
            {
                v_Row = v_random.Next(0, v_BoardSize);
                v_Col = v_random.Next(0, v_BoardSize);
            }
        }
    }
}
