using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace AutomatedLight.Models
{
    public class DataItem : IComparable
    {
        public Guid Id { get; set; }
        public double Temp { get; set; }
        public double Lux { get; set; }
        public double Humidity { get; set; }
        public DateTime Time { get; set; }

        public int CompareTo(object obj)
        {
            if (obj is DataItem)
                return Time.CompareTo(((DataItem)obj).Time);
            else
                throw new ArgumentException("Object is not a DataItem");
        }
    }
}
