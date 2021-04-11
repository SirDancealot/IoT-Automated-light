using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using AutomatedLight.Models;

namespace AutomatedLight.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DataController : ControllerBase
    {
        private readonly DataContext _context;

        public DataController(DataContext context)
        {
            _context = context;
        }

        // GET: api/Data
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DataItem>>> GetDataItems()
        {
            return await _context.DataItems.ToListAsync();
        }

        [HttpGet("latest")]
        public async Task<ActionResult<DataItem>> GetLatest()
        {
            IEnumerable<DataItem> items = await _context.DataItems.ToListAsync(); 

            return items.Max();
        }

        // POST: api/Data?temp=<value>&lux=<value>
        [HttpPost]
        public async Task<ActionResult<DataItem>> PostData(double temp, double lux)
        {
            DataItem item = new DataItem
            {
                Temp = temp,
                Time = DateTime.Now,
                Lux = lux
            };

            _context.DataItems.Add(item);
            await _context.SaveChangesAsync();

            return item;
        }
    }
}
