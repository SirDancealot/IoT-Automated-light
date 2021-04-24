using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using AutomatedLight.Models;
using System.Web.Http.Cors;

namespace AutomatedLight.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class DataController : ControllerBase
    {
        private readonly DataContext _context;

        public DataController(DataContext context)
        {
            _context = context;
        }

        // GET: Data
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DataItem>>> GetDataItems()
        {
            return await _context.DataItem.ToListAsync();
        }

        [HttpGet("latest")]
        public async Task<ActionResult<DataItem>> GetLatest()
        {
            DataItem max;

            try
            {
                IEnumerable<DataItem> items = await _context.DataItem.ToListAsync();
                max = items.Max();
            } catch (Exception)
            {
                max = new DataItem()
                {
                    Lux = 0.0,
                    Humidity = 0.0,
                    Temp = 0.0,
                    Time = DateTime.Now
                };
            }

            if (max == null)
                max = new DataItem()
                {
                    Lux = 0.0,
                    Humidity = 0.0,
                    Temp = 0.0,
                    Time = DateTime.Now
                };

            return max;
        }

        [HttpGet("latest/temp")]
        public async Task<ActionResult<double>> GetLatestTemp()
        {
            ActionResult<DataItem> item = await GetLatest();
            return item.Value.Temp;
        }
        [HttpGet("latest/lux")]
        public async Task<ActionResult<double>> GetLatestLux()
        {
            ActionResult<DataItem> item = await GetLatest();
            return item.Value.Lux;
        }
        [HttpGet("latest/humidity")]
        public async Task<ActionResult<double>> GetLatestHumidity()
        {
            ActionResult<DataItem> item = await GetLatest();
            return item.Value.Humidity;
        }


        // POST: Data?temp=<value>&lux=<value>&humidity=<value>
        [HttpPost]
        public async Task<ActionResult<DataItem>> PostData(double temp, double lux, double humidity)
        {
            DataItem item = new DataItem
            {
                Temp = temp,
                Time = DateTime.Now,
                Lux = lux,
                Humidity = humidity
            };

            _context.DataItem.Add(item);
            await _context.SaveChangesAsync();

            return item;
        }
    }
}
