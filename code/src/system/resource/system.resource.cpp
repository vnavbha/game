#include "system.resource.h"
#include "system/resource/resourceid.h"
#include "system/base/stream/inputfilestream.h"
#include "system/base/collections/buffer.h"
#include "system/base/debug/debug.h"
#include "system/base/app/appbase.h"
#include <string>

#if defined(WINDOWS)
#include <Windows.h>
#endif

//-----------------------------------------------------------------------------

ZSystemResourceSubSystem::ZSystemResourceSubSystem()
{

}

ZSystemResourceSubSystem::~ZSystemResourceSubSystem()
{

}

//-----------------------------------------------------------------------------

bool ZSystemResourceSubSystem::Init()
{
	ZFilePath path = GetApp()->GetExePath();
	m_resourcePath = path.GetDirectory() + GetApp()->GetApplicationOption<ZString>("RESOURCE_PATH");

	ZASSERT(m_resourcePath.IsValid());
	return ZSubSystem::Init();
}

void ZSystemResourceSubSystem::Uninit()
{
	ZSubSystem::Uninit();
}

ZResourcePtr ZSystemResourceSubSystem::Load(const ZResourceId& rid)
{
	if (rid.IsValid() == false)
	{
		return ZResourcePtr();
	}

	ZFilePath path = ToFilePath(rid);
	ZInputFileStream stream;
	if (stream.Open(path) == false)
	{
		return ZResourcePtr();
	}

	ZBuffer data;
	//char aBuffer[READ_BUFFER_SIZE];
	TArray<char> aBuffer(READ_BUFFER_SIZE);
	size_t nTotalBytes = 0;
	do
	{
		nTotalBytes += stream.Read(aBuffer.data(), READ_BUFFER_SIZE);
		data += aBuffer;
	} while (!stream.IsEof());

	TSharedPtr<ZResourceData> pResourceData(ZNEW ZResourceData(std::move(data)));
	m_aResources.insert(TPair< uint64, TSharedPtr<ZResourceData> >(rid.Hash(), pResourceData));
	return ZResourcePtr(pResourceData);
}

void ZSystemResourceSubSystem::Update(const STime& gameTime)
{
	ZSubSystem::Update(gameTime);
}

ZResourcePtr ZSystemResourceSubSystem::Get(const ZResourceId& rid)
{
	auto it = m_aResources.find(rid.Hash());
	if (it == m_aResources.end())
	{
		return ZResourcePtr(nullptr);
	}
	return ZResourcePtr(it->second);
}

ZFilePath ZSystemResourceSubSystem::ToFilePath(const ZResourceId& rid) const
{
	if (rid.IsValid() == false)
	{
		return ZFilePath();
	}
	
	ZString sRid = rid.ToString();
	size_t iProtocol = sRid.find(':');
	if (iProtocol == ZString::npos)
	{
		return ZString();
	}
	ZString sProtocol = sRid.substr(0, iProtocol);
	size_t iTrim = iProtocol + 1;
	if (iTrim >= sRid.length())
	{
		return ZFilePath();
	}
	ZString sPath = sRid.substr(iTrim, sRid.length());

	ZFilePath result = m_resourcePath + sPath;
	return result;
}

