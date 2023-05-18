using System;
namespace B23_Ex02_IdoHirschmann_211329883_ZivChoen_313453797
{
    internal class UI
    {
        internal static void StartGame()
        {
            GameManager v_NewGame = new GameManager();

            v_NewGame.GameBoard = new GameBoard(getBoardSizeFromUser());
            v_NewGame.SetOpponentType(getOpponentTypeFromUser());

            play(v_NewGame);
        }
        private static int getBoardSizeFromUser()
        {
            string v_InputChecker;

            Console.WriteLine("Please enter board's size (number between 3-9): ");
            v_InputChecker = Console.ReadLine();

            while (v_InputChecker.Length != 1 || v_InputChecker[0] < '3' || v_InputChecker[0] > '9')
            {
                Console.WriteLine("Invalid input, Please enter board's size (number between 3-9): ");
                v_InputChecker = Console.ReadLine();
            }

            return int.Parse(v_InputChecker);

        }
        private static bool getOpponentTypeFromUser()
        {
            string v_InputChecker;

            Console.WriteLine("Please enter 0 if you want to match another human player, or 1 if you want to match a computer: ");
            v_InputChecker = Console.ReadLine();

            while (v_InputChecker.Length != 1 || (v_InputChecker[0] != '0' && v_InputChecker[0] != '1'))
            {
                Console.WriteLine("Invalid input, Please enter 0 if you want to match another human player, or 1 if you want to match a computer: ");
                v_InputChecker = Console.ReadLine();
            }

            int v_UsersChoice = int.Parse(v_InputChecker);
            return Convert.ToBoolean(v_UsersChoice);
        }
        private static void play(GameManager i_GameManager)
        {
            bool v_ContinueToPlay = true;
            bool v_ValidSquerChoice = false;
            int? v_Row = null;
            int? v_Col = null;

            while (v_ContinueToPlay)
            {
                while(!i_GameManager.IsGameOver())
                {
                    printGameBoard(i_GameManager.GameBoard.Matrix);

                    while (!v_ValidSquerChoice)
                    {
                        if (getNextMoveFromUser(i_GameManager.GameBoard.Matrix.GetLength(0), out v_Row, out v_Col))
                        {
                            v_ValidSquerChoice = i_GameManager.PlayNextMove((int)v_Row, (int)v_Col);
                            if (!v_ValidSquerChoice)
                            {
                                takenSquereMessage();
                            }
                        }
                        else
                        {
                            i_GameManager.PlayerRetired();
                            break;
                        }
                    }
                    v_ValidSquerChoice = false;
                }

                v_ContinueToPlay = endRound(i_GameManager);

                if(v_ContinueToPlay)
                {
                    i_GameManager.ResetGame();
                }
            }
        }
        private static bool getNextMoveFromUser(int i_BoardSize, out int? o_Row, out int? o_Col)
        {
            string v_RowChecker, v_ColChecker;
            bool v_Continue;
            o_Row = o_Col = null;

            Console.WriteLine("Please enter row and col indexes (between 1 - {0}) , sapareted by Enter: ", i_BoardSize);
            v_RowChecker = Console.ReadLine(); 
            

            if (retire(v_RowChecker))
            {
                v_Continue = false;
            }
            else
            {
                v_ColChecker = Console.ReadLine();
                v_Continue = true;

                while (!isIndexesValid(v_RowChecker, v_ColChecker, i_BoardSize))
                {
                    Console.WriteLine("Invalid input, please enter row and col indexes (between 1 - {0}) , sapareted by Enter: ", i_BoardSize);
                    v_RowChecker = Console.ReadLine(); 
                    
                    if (retire(v_RowChecker))
                    {
                        v_Continue = false;
                        break;
                    }
                    else
                    {
                        v_ColChecker = Console.ReadLine();
                        v_Continue = true;
                    }
                }

                if (v_Continue == true)
                {
                    o_Row = int.Parse(v_RowChecker) - 1;
                    o_Col = int.Parse(v_ColChecker) - 1;
                }
            }

            return v_Continue;
        }
        private static bool isIndexesValid(string i_Row, string i_Col, int i_BoardSize)
        {
            return ((i_Row.Length == 1 && i_Row[0] > '0' && int.TryParse(i_Row, out int v_RowChecker) && v_RowChecker <= i_BoardSize)
                && (i_Col.Length == 1 && i_Col[0] > '0' && int.TryParse(i_Col, out int v_ColChecker) && v_ColChecker <= i_BoardSize));
        }
        private static bool retire(string i_UserInput)
        {
            return i_UserInput.Length == 1 && i_UserInput[0] == 'Q';
        }
        private static void takenSquereMessage()
        {
            Console.WriteLine("Oops! the squere you've chosen is already taken.");
        }
        private static bool endRound(GameManager i_GameManager)
        {
            bool v_Continue;
            string v_UserChoice;

            printGameBoard(i_GameManager.GameBoard.Matrix);
            summarizeRound(i_GameManager);
            Console.WriteLine("Do you want to play another round? (press 0 for no, or 1 for yes) :");
            v_UserChoice = Console.ReadLine();

            while (v_UserChoice.Length != 1 || (v_UserChoice[0] != '1' && v_UserChoice[0] != '0'))
            {
                Console.WriteLine("Invalid input, do you want to play another round? (press 0 for no, or 1 for yes) :");
                v_UserChoice = Console.ReadLine();
            }

            v_Continue = Convert.ToBoolean(int.Parse(v_UserChoice));
            return v_Continue;
        }
        private static void summarizeRound(GameManager i_GameManager)
        {
            char? v_Winner = null;

            if(i_GameManager.Winner != null)
            {
                if(i_GameManager.Winner.Value.playerType.IsX())
                {
                    v_Winner = 'X';
                }
                else
                {
                    v_Winner = 'O';
                }
            }

            if(v_Winner == null)
            {
                Console.WriteLine("The round has ended in a draw!");
            }
            else
            {
                Console.WriteLine("The winner of this round is player {0}!", v_Winner);
            }

            Console.WriteLine("The current scoresheet: Player X: {0}, Player O: {1}.", i_GameManager.Players[0].Score, i_GameManager.Players[1].Score);
        }
        private static void printGameBoard(SquereType [,] i_GameBoard)
        {
            int v_BoardSize = i_GameBoard.GetLength(0);

            Console.Write(@" ");

            for (int i = 1; i <= v_BoardSize; ++i)
            {
                Console.Write(@" {0}  ", i);
            }

            Console.WriteLine();

            for (int i = 1; i <= v_BoardSize; ++i)
            {
                Console.Write(i);
                for(int j = 0; j < v_BoardSize; ++j)
                {
                    if(i_GameBoard[i-1,j].IsEmpty())
                    {
                        Console.Write(@"|   ");
                    }
                    else
                    {
                        Console.Write("| {0} ", i_GameBoard[i - 1, j].Type);
                    }
                }

                Console.WriteLine("|");
                Console.Write(" =");

                for(int j = 0; j < v_BoardSize; ++j)
                {
                    Console.Write("====");
                }

                Console.WriteLine();
            }
        }
    }
}

