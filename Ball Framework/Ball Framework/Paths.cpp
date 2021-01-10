#include "Paths.h"

namespace BallFramework
{

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
		if (m_filePath == "") 
			return;

		auto it = m_assetsPaths.find(objectKey);
		if (it == m_assetsPaths.end())
			++m_numberOfAssets;
		m_assetsPaths[objectKey] = path;

		std::ofstream fout(m_filePath);

		fout << m_numberOfAssets << std::endl;
		for (auto&& asset : m_assetsPaths)
		{
			fout << asset.first << " " << asset.second << std::endl;
		}
		fout.close();
	}

	std::string Paths::ReturnObjectPath(const std::string& objectKey)
	{
		if (m_filePath == "" || m_numberOfAssets == 0)
			return "";

		auto it = m_assetsPaths.find(objectKey);
		if (it != m_assetsPaths.end())
		{
			return it->second;
		}
		return "";
	}

	Paths::Paths()
	{
	}

	void Paths::ReadPaths()
	{
		std::ifstream fin(m_filePath);

		if (fin.is_open() && m_filePath != "")
		{
			if (fin.peek() == std::ifstream::traits_type::eof())
			{
				m_numberOfAssets = 0;
				return;
			}

			fin >> m_numberOfAssets;
			std::string objectKey, path;
			for (auto index = 0; index < m_numberOfAssets; index++)
			{
				fin >> objectKey;
				fin >> path;
				m_assetsPaths[objectKey] = path;
			}
			fin.close();
		}
		else 
		{
			LOGGING_ERROR("File from path not found!");
		}
	}

}