#pragma checksum "C:\Users\Deadb\Desktop\IoT-Automated-light\Automated Light Web Interface\Pages\IOTDashboard.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "a1e96bebfc3f302e64fa8bd28954c4cec9518c0e"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(Automated_Light_Web_Interface.Pages.Pages_IOTDashboard), @"mvc.1.0.razor-page", @"/Pages/IOTDashboard.cshtml")]
namespace Automated_Light_Web_Interface.Pages
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
#nullable restore
#line 1 "C:\Users\Deadb\Desktop\IoT-Automated-light\Automated Light Web Interface\Pages\_ViewImports.cshtml"
using Automated_Light_Web_Interface;

#line default
#line hidden
#nullable disable
#nullable restore
#line 3 "C:\Users\Deadb\Desktop\IoT-Automated-light\Automated Light Web Interface\Pages\IOTDashboard.cshtml"
using System.Web.Helpers;

#line default
#line hidden
#nullable disable
#nullable restore
#line 4 "C:\Users\Deadb\Desktop\IoT-Automated-light\Automated Light Web Interface\Pages\IOTDashboard.cshtml"
using System.Web.Mvc;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"a1e96bebfc3f302e64fa8bd28954c4cec9518c0e", @"/Pages/IOTDashboard.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"a02f6c2390a388a39488a633eddcd6706f2fed46", @"/Pages/_ViewImports.cshtml")]
    public class Pages_IOTDashboard : global::Microsoft.AspNetCore.Mvc.RazorPages.Page
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
#nullable restore
#line 5 "C:\Users\Deadb\Desktop\IoT-Automated-light\Automated Light Web Interface\Pages\IOTDashboard.cshtml"
  

    var myChart = new Chart(width: 600, height: 400)
        .AddTitle("Sales Per Employee")
        .AddSeries("Default", chartType: "Line",
            xValue: new[] { "Peter", "Andrew", "Julie", "Mary", "Dave" },
            yValues: new[] { "2", "6", "4", "5", "3" })
        .Write();




#line default
#line hidden
#nullable disable
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<Automated_Light_Web_Interface.Pages.IOTDashboardModel> Html { get; private set; }
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.ViewDataDictionary<Automated_Light_Web_Interface.Pages.IOTDashboardModel> ViewData => (global::Microsoft.AspNetCore.Mvc.ViewFeatures.ViewDataDictionary<Automated_Light_Web_Interface.Pages.IOTDashboardModel>)PageContext?.ViewData;
        public Automated_Light_Web_Interface.Pages.IOTDashboardModel Model => ViewData.Model;
    }
}
#pragma warning restore 1591