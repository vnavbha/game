cs_app("tools", "unittestgenerator")
links{
	"System",
}
postbuildcommands {
  "xcopy /E /Y /I $(ProjectDir)".."\\" .. "unittestgeneratorfiles $(TargetDir)\\unittestgeneratorfiles"
}
