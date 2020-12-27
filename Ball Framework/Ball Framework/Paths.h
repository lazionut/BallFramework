#pragma once
#include<string>
#include<cstdint>
#include<unordered_map>
#include<fstream>

class Paths
{
public:
	static void SetFilePath(const std::string& filePath);
	static std::string GetFilePath();

	static void AddObjectPath(const std::string& objectKey, const std::string& path);
	static std::string ReturnObjectPath(const std::string& objectKey);

private:

	Paths();
	Paths(const Paths&) = delete;

	static void ReadPaths();

	static std::unordered_map<std::string, std::string> m_assetsPaths;
	static uint32_t m_numberOfAssets;
	static std::string m_filePath;
};

