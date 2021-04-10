using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace AutomatedLight.Models
{
    public class TemperatureContext : DbContext
    {
        public TemperatureContext(DbContextOptions<TemperatureContext> options) : base(options) { }
        
        public DbSet<TemperatureItem> TemperatureItems { get; set; }
    }
}
