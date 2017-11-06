function assimp_configure(error)
	includedirs(
	{
			EXTERNAL_DIR .. "/assimp/include"
	})
  libdirs(
	{
			EXTERNAL_DIR .. "/assimp/lib/Release"
	})

	links (
	{
		"assimp-vc140-mt.lib"
	})
end