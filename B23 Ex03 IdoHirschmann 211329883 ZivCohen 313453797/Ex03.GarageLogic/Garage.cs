using System;
using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Linq;

namespace Ex03.GarageLogic
{
    public class Garage
    {
        private readonly Dictionary<string, Client> m_Clients = new Dictionary<string, Client>();

        const int k_NumOfClientFields = 4;
        const int k_OwnersNameInd = 0;
        const int k_OwnersPhoneNumberInd = 1;
        const int k_VehicleTypeInd = 2;
        const int k_EngineTypeInd = 3;
        const int k_PhoneNumberLength = 10;

        public bool CheckIfClientExist(string i_LicenseNumber , out string[]? o_ClientFieldList)
        {
            bool v_IsClientExist = m_Clients.TryGetValue(i_LicenseNumber , out Client? v_Client);

            o_ClientFieldList = null;

            if(v_Client != null)
            {
                v_Client.VehicleStatus = eVehicleStatus.InRepeir;
            }
            else
            {
               o_ClientFieldList = createClientFieldList();
               m_Clients.Add(i_LicenseNumber, ObjectFactory.CreateClient());
            }

            return v_IsClientExist;
        }
        private string[] createClientFieldList()
        {
            string[] v_VehicleType = Enum.GetNames(typeof(eVehiclesTypes));
            string v_VehicleTypeCombain = string.Join(", ", v_VehicleType);
            string[] v_EngineType = Enum.GetNames(typeof (eEngineTypes));
            string v_EngineTypeCombain = string.Join(", ", v_EngineType);
            string[] v_ClientFieldList = new string[k_NumOfClientFields];

            v_ClientFieldList[k_OwnersNameInd] = "Owner's name";
            v_ClientFieldList[k_OwnersPhoneNumberInd] = "Owner's phone number";
            v_ClientFieldList[k_VehicleTypeInd] = string.Format("Vehicle type ({0})", v_VehicleTypeCombain);
            v_ClientFieldList[k_EngineTypeInd] = string.Format("Engine type ({0})", v_EngineTypeCombain);

            return v_ClientFieldList;
        }
        public string[]? AddNewClient(string i_LicenseNumber, string[] i_ClientFields)
        {
            string[]? v_VehicleFields = null;
            Client v_Client = m_Clients[i_LicenseNumber];

            setClient(v_Client, i_ClientFields);
            v_Client.Vehicle.LicenseNumber = i_LicenseNumber;
            v_VehicleFields = v_Client.Vehicle.GetVehicleFields();

            return v_VehicleFields;
        }
        public void SetVehicleFields(string i_LicenseNumber, string[] i_VehicleFields)
        {
            try
            {
                m_Clients[i_LicenseNumber].Vehicle.SetVehicleFields(i_VehicleFields);
            }
            catch (Exception i_InvalidInput)
            {
                m_Clients[i_LicenseNumber].Vehicle.ResetVehicle();
                throw i_InvalidInput;
            }
        }
        private void setClient(Client io_Client, string[] i_ClientFields)
        {
            setClientName(io_Client, i_ClientFields[k_OwnersNameInd]);
            setClientPhoneNumber(io_Client, i_ClientFields[k_OwnersPhoneNumberInd]);
            setClientVehicle(io_Client, i_ClientFields[k_VehicleTypeInd], i_ClientFields[k_EngineTypeInd]);
        }
        private void setClientName(Client io_Client, string i_Name)
        {
            bool v_ContainsOnlyLettersOrSpaces = Regex.IsMatch(i_Name, @"^[a-zA-Z\s]+$");

            if (!v_ContainsOnlyLettersOrSpaces)
            {
                throw new FormatException("Invalid name input.");
            }
            else
            {
                io_Client.OwnerName = i_Name;
            }
        }
        private void setClientPhoneNumber(Client io_Client, string i_PhoneNumber)
        {
            if (isValidPhoneNumber(i_PhoneNumber))
            {
                io_Client.OwnerPhoneNumber = i_PhoneNumber;
            }
            else
            {
                throw new FormatException("Invalid phone number.");
            }
        }
        private bool isValidPhoneNumber(string i_PhoneNumber)
        {
            bool v_IsPhoneNumberValid = false;

            if(i_PhoneNumber.Length == k_PhoneNumberLength)
            {
                v_IsPhoneNumberValid = int.TryParse(i_PhoneNumber, out int o_PhoneNumber);
            }

            return v_IsPhoneNumberValid;
        }
        private void setClientVehicle(Client io_Client, string i_VehicleType, string i_EngineType)
        {
            bool v_IsVehicleTypeValid = Enum.TryParse<eVehiclesTypes>(i_VehicleType, out eVehiclesTypes v_VehicleType);
            bool v_IsEngineTypeValid = Enum.TryParse<eEngineTypes>(i_EngineType, out eEngineTypes v_EngineType);

            if (!v_IsVehicleTypeValid)
            {
                throw new FormatException("Invalid Vehicle type.");
            }
            else if(!v_IsEngineTypeValid)
            {
                throw new FormatException("Invalid Engine type.");
            }
            else
            {
                io_Client.Vehicle = ObjectFactory.CreatVehicle(v_VehicleType, v_EngineType);                
            }
        }
        public List<string>? PresentVehiclesByStatus(string i_VehiclesStatus)
        {
            List<string>? v_VehiclesByFilter = null;
            bool v_IsVehicleStatusValid = Enum.TryParse<eVehicleStatus>(i_VehiclesStatus, out eVehicleStatus v_VehicleStatus);

            if(!v_IsVehicleStatusValid)
            {
                throw new FormatException("Invalid vehicle status.");
            }
            else
            {
         
                v_VehiclesByFilter = new List<string>();
                if (v_VehicleStatus == eVehicleStatus.All)
                {
                    foreach (Client v_Vehicle in m_Clients.Values)
                    {
                        v_VehiclesByFilter.Add(v_Vehicle.Vehicle.LicenseNumber);
                    }
                }
                else
                {
                    var v_FilteredVehicles = m_Clients.Where(pair => pair.Value.VehicleStatus.Equals(i_VehiclesStatus));
                    foreach (var v_Vehicle in v_FilteredVehicles)
                    {
                        v_VehiclesByFilter.Add(v_Vehicle.Value.Vehicle.LicenseNumber);
                    }
                }
            }

            return v_VehiclesByFilter;
        }
        public void ChangeVehicleStatus(string i_LicenseNumber, string i_NewStatus)
        {
            Client? v_Client = isClientExist(i_LicenseNumber);
            bool v_IsVehicleStatusValid = Enum.TryParse<eVehicleStatus>(i_NewStatus, out eVehicleStatus v_VehicleStatus);          
                                   
            if(!v_IsVehicleStatusValid || v_VehicleStatus == eVehicleStatus.All)
            {
                throw new FormatException("Invalid vehicle status.");
            }
            else
            {
                v_Client.VehicleStatus = v_VehicleStatus;
            }
        }
        public void InflateWheelsToMax(string i_LicenseNumber)
        {
            Client? v_Client = isClientExist(i_LicenseNumber);

            foreach (Wheel v_wheel in v_Client.Vehicle.Wheels)
            {
                v_wheel.FillAirPressure((float)v_wheel.MaxAirPressureCapacity - v_wheel.CurrentAirPressure);
            }
        }
        public void FuelVehicle(string i_LicenseNumber, string i_FuelType, string i_AmoutnOfFuel)
        {
            Client? v_Client = isClientExist(i_LicenseNumber);

            if (v_Client.Vehicle.Engine is ElectricEngine)
            {
                throw new ArgumentException("Invalid option, can't fill fuel in electric car");
            }
            bool v_IsFuelTypeValid = Enum.TryParse<eFuelTypes>(i_FuelType, out eFuelTypes v_FuelType);

            if (!v_IsFuelTypeValid)
            {
                throw new FormatException("Invalid input for fuel type");
            }
            else if (v_Client.Vehicle.GetFuelType() != v_FuelType)
            {
                throw new ArgumentException("Invalid type of fuel for this vehicle");
            }
            bool v_IsAmountValid = float.TryParse(i_AmoutnOfFuel, out float v_AmountInLitters);

            if (!v_IsAmountValid)
            {
                throw new FormatException("Invalid input for amount");
            }
            else
            {
                v_Client.Vehicle.FillVehicle(v_AmountInLitters);
            }
        }
        public void ChargeVehicle(string i_LicenseNumber, string i_AmountInMinutes)
        {
            Client? v_Client = isClientExist(i_LicenseNumber);

            if (v_Client.Vehicle.Engine is FuelEngine)
            {
                throw new ArgumentException("Invalid option, can't charge a fuel engine");
            }
            bool v_IsAmountValid = float.TryParse(i_AmountInMinutes, out float v_MinutesToFill);

            if (v_IsAmountValid && v_MinutesToFill >= 0)
            {
                v_Client.Vehicle.FillVehicle(v_MinutesToFill / 60f);
            }
            else
            {
                throw new FormatException("Invalid number of minutes to charge input.");
            }
        }
        public string PresentFullInfoOnVehicle(string i_LicenseNumber)
        {
            Client? v_Client = isClientExist(i_LicenseNumber);

            return v_Client.ToString();
        }
        private Client? isClientExist(string i_LicenseNumber)
        {
            bool v_IsClientExist = m_Clients.TryGetValue(i_LicenseNumber, out Client? v_Client);

            if (!v_IsClientExist)
            {
                throw new ClientDoesNotExist();
            }

            return v_Client;
        }
        public string[] GetStatusOptions()
        {
            string[] v_VehicleStatusOptions = Enum.GetNames(typeof(eVehicleStatus));
            string[] v_VehicleValidStatusOptions = new string[v_VehicleStatusOptions.Length - 1];

            Array.Copy(v_VehicleStatusOptions, 0, v_VehicleValidStatusOptions , 0, v_VehicleValidStatusOptions.Length);

            return v_VehicleValidStatusOptions;
        }
    }
}