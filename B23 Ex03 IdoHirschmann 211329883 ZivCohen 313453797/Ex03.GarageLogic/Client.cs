using System;
namespace Ex03.GarageLogic
{
	internal class Client
	{
		private string? m_OwnerName = null;
		private string? m_OwnerPhoneNumber = null;
		private eVehicleStatus m_VehicleStatus = eVehicleStatus.InRepeir;
		private Vehicle? m_Vehicle = null;

		internal string? OwnerName
		{
			get
			{
				return m_OwnerName;
			}
			set
			{
				m_OwnerName = value;
			}
		}
		internal string? OwnerPhoneNumber
		{
			get
			{
				return m_OwnerPhoneNumber;
			}
			set
			{
				m_OwnerPhoneNumber = value;
			}
		}
        internal eVehicleStatus VehicleStatus
        {
            get
            {
                return m_VehicleStatus;
            }
            set
            {
				m_VehicleStatus = value;
            }
        }
        internal Vehicle? Vehicle
        {
            get
            {
                return m_Vehicle;
            }
            set
            {
                m_Vehicle = value;
            }
        }
        public override string ToString()
        {
			string v_ClientData;

			v_ClientData =
				string.Format(@"Owner's name - {0},
owner's phone number is {1},
vehicle's status {2},
{3}",
				m_OwnerName, m_OwnerPhoneNumber, m_VehicleStatus.ToString(), m_Vehicle.ToString());

			return v_ClientData;
        }
    }
}

