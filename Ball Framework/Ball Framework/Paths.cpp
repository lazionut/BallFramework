#include "Paths.h"

std::string Paths::m_filePath = "";
std::uint32_t Paths::m_numberOfAssets = 0;
std::unordered_map<std::string, std::string> Paths::m_assetsPaths;

void Paths::SetFilePath(const std::string& filePath)
{
	m_filePath = filePath;
	ReadPaths();
}

std::string Paths::GetFilePath()
{
	return m_filePath;
}

void Paths::AddObjectPath(const std::string& objectKey, const std::string& path)
{
}

std::string Paths::ReturnObjectPath(const std::string& objectKey)
{
	return std::string();
}

Paths::Paths()
{
}

void Paths::ReadPaths()
{
}
