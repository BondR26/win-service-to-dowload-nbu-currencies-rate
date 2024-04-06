Prerequistes : conan, cmake, Visual Studio 16 2019 
1. To build the project open cmd.exe with administrative privilege;
2. Change dir to the project foleder(where conanfile.py is located)
 and run build_and_install.bat script
 > build_and_install.bat
2. cool_porject.exe file would be installed in ./run folder 
3. Now you have 3 options of working with cool_porject.exe
    3.1 As standalone >cool_project.exe standalone (will run for 2 minutes and then exits )
	3.2 Reigster cool_project.exe using scm tool and commands;
	3.3 Use set of commands to make cool_project.exe a windows service: 
		3.3.1 cool_project.exe install 
		3.3.2 cool_project.exe start
		3.3.3 cool_project.exe remove
	The last three command are correspoding to code inside cool_project.exe which will set it up as win service.
4. SETTINGS
    4.1 User can modify config.json file which is found in working directory
	   !!!(this means that if you run exe in standalone mode the config.json file and result file with currencies would be found in the same folder)
		!ATTENTION (for windows service folder is C:\Windows\System32\ ; this means that if you install and start cool_project.exe as windows servie the config files woulc be located in  C:\Windows\System32\)
	4.2 User can modify HKEY_LOCAL_MACHINE\SOFTWARE\CoolCurrencyProj reg key values 
	
5. Config values are : in config json data_format : 0 - json, 1 - xml, 2 -csv
									fetch_rate(periodically downloading data about currencies from nbu ) 0 - 1min , 1 - 2min, 3 - 5min
									
6. Config values in regestry keys are data_format = "json", "xml", "csv";
										fetch_rate = "minute", "two_minutes"; "five_minutes"
										
7. If user changes settings inside a file or regkey - service immediately changes its configuration, saves file in new format(if needed) and reschedules new operation time;

7. MY ADVICE - for quick overview i would reccomend to run it in standalone mode ; this way user would be able to see conifg file and curency at hand;