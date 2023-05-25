using System;
namespace Ex03.GarageLogic
{
	public abstract class Engine
	{
        internal abstract void FillVehicle(float i_Amount);
        internal abstract float CalcEnergyPercentage();
        internal abstract string[] GetFillParams();
        public abstract override string ToString();
        internal abstract void ResetEngine();
    }
}

