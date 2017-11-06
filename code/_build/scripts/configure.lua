newaction {
   trigger     = 		"generate",
   description = 		"Generate projects and solutions",
   execute = function ()
      if _OPTIONS["vs"] == "2015" then
				_ACTION="vs2015"
				print_info("generating..")
			end
   end
}

newoption {
   trigger     = 		"vs",
   description = 		"The visual studio version",
   value       = 		"Visual Studio Version",
   allowed = {
      { "2015",    	"Visuial studio 2015" }
   }
}

if(_ACTION == "clean") then
	-- a more thorough clean
	print_info("cleaning directories")
	os.rmdir(BUILD_DIR .. "/_obj")
	os.rmdir(BUILD_DIR .. "/_out")
   os.rmdir(BUILD_DIR .. "/_solutions")
end
