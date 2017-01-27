#include"stdafx.h"

#include "CustomTypes.h"

#include <exception>
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <fstream>

#include "FileIO.h"

namespace StudentScoring
{

	/* Concrete implementation for the writing of a file */
	void FileIO::WriteFile(std::string& fileName, Lines& contents)
	{
		std::ofstream outputFileStream(fileName);

		try
		{	
			/* Check the file is open before proceeding */
			if (outputFileStream.is_open())
			{
				/* Use a lambda to iterate through each line and write it to the output-stream */
				std::for_each(contents.begin(), contents.end(), [&](const std::string& str) { outputFileStream << str.c_str(); });
			}

		}
		catch (std::exception& exception)
		{			
			std::string compositeMessage ="The file could not be written:"  + std::string(exception.what());
			OutputDebugStringA(compositeMessage.c_str());

			// Allow exception to be caught be caller
			throw;
		}

		outputFileStream.close();
	}

	/* Concrete implementation for the reading of a file */
	LinesUniquePtr FileIO::ReadFile(std::string& fileName)
	{
		/* Use a unique pointer as only need one instance of the file data container - 
			prevent copying for efficiencies sake */
		LinesUniquePtr contents = std::make_unique<Lines>();
		std::string line = "";

		try
		{
			std::ifstream inputFileStream(fileName);

			if (inputFileStream.is_open())
			{
				/* Red the file into the unique container */
				while (std::getline(inputFileStream, line))
				{
					contents->push_back(line);
				}
			}
			else
			{
				std::string message = "Failed to read file: " + fileName;
				throw std::exception(message.c_str());
			}
		}
		catch (std::exception& exception)
		{			
			std::string compositeMessage ="The file could not be read: " + std::string(exception.what());
			OutputDebugStringA(compositeMessage.c_str());

			// Allow exception to be caught be caller
			throw;
		}

		return contents;
	}
}