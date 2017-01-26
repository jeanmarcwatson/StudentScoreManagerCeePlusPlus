#include "stdafx.h"

#include <list>
#include <string>
#include <memory>
#include <algorithm>

#include "CppUnitTest.h"

#include "..\StudentScoreManagerCeePlusPlus\FileIO.h"
#include "..\StudentScoreManagerCeePlusPlus\Student.h"
#include "..\StudentScoreManagerCeePlusPlus\StudentScoreManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace StudentScoring;

namespace TestStudentScoreManagerCeePlusPlus
{		
	TEST_CLASS(TestStudentScoreManagerCeePlusPlus)
	{
	public:
		
		TEST_METHOD(TestOutputUsingInputFile)
		{
			StudentScoreManager studentScoreManager;
			std::string inputFile { "students.txt" };

			studentScoreManager.CreateStudents(inputFile);
			studentScoreManager.PersistStudents(studentScoreManager.GetStudents());			

			StudentCsvFileManager studentCSVFileManager;
			std::string outputFile{ "students-graded.txt" };

			LinesUniquePtr outputCSVLines = studentCSVFileManager.ReadCsv(outputFile);

			auto counter = 0;
			std::for_each(outputCSVLines->begin(), outputCSVLines->end(),
				[&counter](const std::string& line)
					{
						switch (counter++)
						{
							case 0 :
									Assert::IsTrue(line == "BUNDY,TED,88");
									break;
							case 1:
									Assert::IsTrue(line == "SMITH,ALLAN,85");
									break;
							case 2:
									Assert::IsTrue(line == "SMITH,FRANCIS,85");
									break;
							case 3:
									Assert::IsTrue(line == "KING,MADISON,83");
									break;						
						}
					});		
		}

		TEST_METHOD(TestStudentTypeCTOR)
		{
			Student student{ std::string {"JEAN-MARC,WATSON,999"} };			

			Assert::IsTrue(student.GetFirstName() == "JEAN-MARC");
			Assert::IsTrue(student.GetLastName() == "WATSON");
			Assert::IsTrue(student.GetScore() == 999);			
		}

	};
}