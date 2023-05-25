using Ex03.GarageLogic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ex03.ConsoleUI
{
    public class UI
    {
        private static Garage m_Garage = new Garage();

        internal static void StartMenu()
        {
            PrintGarageMenu();
            string v_MethodChoice = Console.ReadLine();
            

            switch(v_MethodChoice)
            {
                case "1":
                    {
                        GetNewClient();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "2":
                    {
                        PresentVehicleLicenseNumber();
                        Console.WriteLine("\n");
                        StartMenu() ;
                        break;
                    }
                case "3":
                    {
                        SetNewVehicleStatus();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "4":
                    {
                        InflateWheelsToMax();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "5":
                    {
                        FillFuel();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "6":
                    {
                        ChargeEngine();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "7":
                    {
                        PresentClientInfo();
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }
                case "8":
                    {
                        Console.WriteLine("Thank you for using our garage :)");
                        break;
                    }
                default:
                    {
                        Console.WriteLine("Invalid choice please try again.");
                        Console.WriteLine("\n");
                        StartMenu();
                        break;
                    }

            }
        }
        internal static void PrintGarageMenu()
        {
            Console.WriteLine(@"Ido and Ziv's garage menu:
Please enter the number of your choice:
1 - Add new vehicle
2 - Present all vehicle's license (you can filter by status)
3 - Set a vehicle new status
4 - Inflate all wheels into max
5 - Fill fuel
6 - Charge electric engine
7 - Present vehicle's information
8 - Exit");
        }
        internal static void GetNewClient()
        {
            string[]? v_ClientRequestInfo = null;
            bool v_ValidInput = false;
            int v_Index = 0;
      
            Console.WriteLine("Please Enter a lisence number: ");
            string v_LicenseNumber = Console.ReadLine();

            if(!m_Garage.CheckIfClientExist(v_LicenseNumber,out v_ClientRequestInfo))
            {
                string[] v_ClientInfoFromUser = new string[v_ClientRequestInfo.Length];

                while (!v_ValidInput)
                {
                    v_Index = 0;

                    foreach (string v_ClientInfo in v_ClientRequestInfo)
                    {
                        Console.WriteLine(v_ClientInfo);
                        v_ClientInfoFromUser[v_Index++] = Console.ReadLine();
                    }
                    try
                    {
                        string[] v_VehicleRequestInfo = m_Garage.AddNewClient(v_LicenseNumber, v_ClientInfoFromUser);
                        SetVehicleInfo(v_LicenseNumber, v_VehicleRequestInfo);
                        v_ValidInput = true;
                    }
                    catch(Exception i_InvalidInput)
                    {
                        handleInvalidInput(i_InvalidInput);
                    }
                }
            }
        }
        internal static void SetVehicleInfo(string i_LicenseNumber, string[] i_VehicleInfoRequest)
        {
            bool v_IsValid = false;
            int v_Index = 0;
            string[] v_VehicleInfoFromUser = new string[i_VehicleInfoRequest.Length];

            while (!v_IsValid)
            {
                v_Index = 0;
                foreach (string v_VehicleInfo in i_VehicleInfoRequest)
                {
                    Console.WriteLine(v_VehicleInfo);
                    v_VehicleInfoFromUser[v_Index++] = Console.ReadLine();
                }
                try
                {
                    m_Garage.SetVehicleFields(i_LicenseNumber, v_VehicleInfoFromUser);
                    Console.WriteLine(string.Format("Vehicle {0} is in repair", i_LicenseNumber));
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                }
            }
        }
        internal static void PresentVehicleLicenseNumber()
        {
            string[] v_StatusOptions = m_Garage.GetStatusOptions();
            string[] v_AllStatuses = new string[v_StatusOptions.Length + 1];

            Array.Copy(v_StatusOptions, 0, v_AllStatuses, 0, v_StatusOptions.Length);
            v_AllStatuses[v_AllStatuses.Length - 1] = "All";

            string v_CombainStatusOptions = string.Join(", ", v_AllStatuses);
            bool v_IsValid = false;

            while (!v_IsValid)
            {
                Console.WriteLine(string.Format("Please enter the vehicle's status filter ({0}):", v_CombainStatusOptions));
                string v_StatusFilter = Console.ReadLine();

                try
                {
                    List<string>? v_FilteredVehicles = m_Garage.PresentVehiclesByStatus(v_StatusFilter);
                    if (v_FilteredVehicles.Count != 0)
                    {
                        int v_Index = 0;

                        Console.WriteLine(string.Format("These are the vehicles license number according to {0} status:", v_StatusFilter));
                        foreach (string v_Vehicle in v_FilteredVehicles)
                        {
                            Console.WriteLine(string.Format("{0}. {1}", v_Index, v_Vehicle));
                            v_Index++;
                        }
                    }
                    else
                    {
                        Console.WriteLine("There are no vehicles in our garage at this status.");
                    }
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        internal static void SetNewVehicleStatus()
        {
            bool v_IsValid = false;
            string[] v_Statuses = m_Garage.GetStatusOptions();
            string v_StatusesCombined = string.Join(", ", v_Statuses);

            while (!v_IsValid)
            {
                Console.WriteLine(string.Format("Please enter the vehicle license number and the new status ({0}) (seperated by enter): ", v_StatusesCombined));
                string v_VehicleLicense = Console.ReadLine();
                string v_NewStatus = Console.ReadLine();

                try
                {
                    m_Garage.ChangeVehicleStatus(v_VehicleLicense, v_NewStatus);
                    v_IsValid |= true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        internal static void InflateWheelsToMax()
        {
            bool v_IsValid = false;

            while (!v_IsValid)
            {
                Console.WriteLine("Please enter the vehicle license number:");
                string v_LicenseNumber = Console.ReadLine();

                try
                {
                    m_Garage.InflateWheelsToMax(v_LicenseNumber);
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        internal static void FillFuel()
        {
            bool v_IsValid = false;

            while (!v_IsValid)
            {
                Console.WriteLine("Please enter vehicle's license number:");
                string v_LicenseNumber = Console.ReadLine();

                Console.WriteLine("Please enter the type of fuel and the amount liters to fill (seperated by enter):");
                string v_FuelType = Console.ReadLine();
                string v_AmountToFill = Console.ReadLine();

                try
                {
                    m_Garage.FuelVehicle(v_LicenseNumber, v_FuelType, v_AmountToFill);
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        internal static void ChargeEngine()
        {
            bool v_IsValid = false;

            while (!v_IsValid)
            {
                Console.WriteLine("Please enter vehicle's license number:");
                string v_LicenseNumber = Console.ReadLine();

                Console.WriteLine("Please enter the amount time to charge in minutes:");
                string v_AmountToCharge = Console.ReadLine();

                try
                {
                    m_Garage.ChargeVehicle(v_LicenseNumber, v_AmountToCharge);
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        internal static void PresentClientInfo()
        {
            bool v_IsValid = false;

            while (!v_IsValid)
            {
                Console.WriteLine("Please enter license number:");
                string v_LicenseNumber = Console.ReadLine();
                try
                {
                    string v_VehicleInfo = m_Garage.PresentFullInfoOnVehicle(v_LicenseNumber);

                    Console.WriteLine(v_VehicleInfo);
                    v_IsValid = true;
                }
                catch (Exception i_InvalidInput)
                {
                    handleInvalidInput(i_InvalidInput);
                    break;
                }
            }
        }
        private static void handleInvalidInput(Exception i_InvalidInput)
        {
            Console.WriteLine(string.Format("{0} please try again.\n", i_InvalidInput.Message));
        }
    }
}
