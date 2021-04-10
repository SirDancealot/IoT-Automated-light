using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace AutomatedLight.Models
{
    public class TemperatureItem
    {
        public long Id { get; set; }
        public double Temp { get; set; }
        public DateTime Time { get; set; }
    }
}
