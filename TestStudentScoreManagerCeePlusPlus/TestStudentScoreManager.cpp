#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "CppUnitTest.h"

#include "..\StudentScoreManagerCeePlusPlus\FileIO.h"
#include "..\StudentScoreManagerCeePlusPlus\Student.h"
#include "..\StudentScoreManagerCeePlusPlus\StudentScoreManager.h"
#include "..\StudentScoreManagerCeePlusPlus\StudentCSVFileManager.h"
#include "..\StudentScoreManagerCeePlusPlus\StudentCsvFileException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace StudentScoring;

namespace TestStudentScoreManagerCeePlusPlus
{		
	TEST_CLASS(TestStudentScoreManagerIO)
	{
	public:
		
		TEST_METHOD(TestOutputUsingInputFile)
		{
			StudentScoreManager studentScoreManager;
			std::string inputFile { "..\\Data\\students.txt" };

			try
			{
				studentScoreManager.CreateStudents(inputFile);
				studentScoreManager.PersistStudents(studentScoreManager.GetStudents());
			}
			catch (std::exception& exception)
			{
				std::cout << exception.what() << std::endl;
			}			

			StudentCsvFileManager studentCSVFileManager;
			std::string outputFile{ "..\\Data\\students-graded.txt" };

			LinesUniquePtr outputCSVLines;
			try
			{
				outputCSVLines = studentCSVFileManager.ReadCsv(outputFile);
			}
			catch (std::exception& exception)
			{
				std::cout << exception.what() << std::endl;
			}			

			auto counter = 0;
			std::for_each(outputCSVLines->begin(), outputCSVLines->end(),
				[&counter](const auto& line)
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
	};

	TEST_CLASS(TestStudentScoreManagerStudentConstruction)
	{
	public:

		TEST_METHOD(TestStudentTypeStringCTOR)
		{
			Student student { std::string{ "JEAN-MARC,WATSON,999" } };

			Assert::IsTrue(student.GetFirstName() == "JEAN-MARC");
			Assert::IsTrue(student.GetLastName() == "WATSON"); 
			Assert::IsTrue(student.GetScore() == 999);
		}

		TEST_METHOD(TestStudentTypeIndividualParamsCTOR)
		{
			Student student { std::string("JEAN-MARC"), std::string("WATSON"),999 };

			Assert::IsTrue(student.GetFirstName() == "JEAN-MARC");
			Assert::IsTrue(student.GetLastName() == "WATSON");
			Assert::IsTrue(student.GetScore() == 999);
		}
	};

	TEST_CLASS(TestStudentScoreManagerStudentComparitor)
	{
	public:

		TEST_METHOD(CompareStudentOneTrailsStudentTwo)
		{
			auto student1 = std::make_shared<Student>( "JEAN-MARC,WATSON,999" );
			auto student2 = std::make_shared<Student>("EWAN,WATSON,999");						

			auto position = Compare(student1, student2);

			Assert::IsTrue(position == false);
		}

		TEST_METHOD(CompareStudentTwoTrailsStudentOne)
		{
			auto student1 = std::make_shared<Student>("JEAN-MARC,WATSON,999");
			auto student2 = std::make_shared<Student>("EWAN,WATSON,50");

			auto position = Compare(student2, student1);

			Assert::IsTrue(position == false);
		}

		TEST_METHOD(CompareStudentOneEqualsStudentTwo)
		{
			auto student1 = std::make_shared<Student>("JEAN-MARC,WATSON,999");
			auto student2= std::make_shared<Student>("JEAN-MARC,WATSON,999");

			auto position = Compare(student1, student2);

			Assert::IsTrue(position == false);
		}

		TEST_METHOD(CompareStudentOneScoresHigherStudentTwo)
		{
			auto student1 = std::make_shared<Student>("JEAN-MARC,WATSON,999");
			auto student2 = std::make_shared<Student>("JEAN-MARC,WATSON,50");

			auto position = Compare(student1, student2);

			Assert::IsTrue(position == true);
		}
	
		TEST_METHOD(CompareStudentOneScoresLowerStudentTwo)
		{
			auto student1 = std::make_shared<Student>("JEAN-MARC,WATSON,10");
			auto student2 = std::make_shared<Student>("JEAN-MARC,WATSON,50");

			auto position = Compare(student1, student2);

			Assert::IsTrue(position == false);
		}
	};

	TEST_CLASS(TestStudentCSVFileManager)
	{
	public:

		TEST_METHOD(ReadCsvFileDoesNotExist)
		{
			StudentCsvFileManager studentCsvFileManager;

			try
			{
				std::string nonExistantFile{ "c:\\NonexistantDirectory\\DoesntExist.txt" };
				studentCsvFileManager.ReadCsv(nonExistantFile);
			}
			catch (std::exception exception)
			{
				Assert::IsTrue(std::string(exception.what()) == "Failed to read file: c:\\NonexistantDirectory\\DoesntExist.txt");
			}
		}

		TEST_METHOD(WriteCsvFileNoAssociatedInputFile)
		{
			StudentCsvFileManager studentCsvFileManager;
			auto students = std::list<string>{ "JOHN, DOE, 99", "JAMES, SMITH, 25" };

			try
			{				
				studentCsvFileManager.WriteCsv(students);
			}
			catch (StudentCsvFileException& exception)
			{
				Assert::IsTrue(std::string(exception.what()) == "No respective CSV input-file provided. Output incorporates use of input-file name");
			}
		}

		TEST_METHOD(ReadCsvCheckContentsReturned)
		{
			StudentCsvFileManager studentCsvFileManager;
			LinesUniquePtr outputCSVLines;
			std::string inputFile{ "..\\Data\\students.txt" };

			try
			{
				outputCSVLines = studentCsvFileManager.ReadCsv(inputFile);
			}
			catch (StudentCsvFileException& exception)
			{
				std::cout << exception.what() << std::endl;
			}

			auto counter = 0;
			std::for_each(outputCSVLines->begin(), outputCSVLines->end(),
				[&counter](const auto& line)
			{
				switch (counter++)
				{
				case 0:
					Assert::IsTrue(line == "TED,BUNDY,88");
					break;
				case 1:
					Assert::IsTrue(line == "ALLAN,SMITH,85");
					break;
				case 2:
					Assert::IsTrue(line == "MADISON,KING,83");
					break;
				case 3:
					Assert::IsTrue(line == "FRANCIS,SMITH,85");					
					break;
				}
			});
		}

		TEST_METHOD(ReadStudents)
		{
			StudentCsvFileManager studentCsvFileManager;
			Students students;
			std::string inputFile{ "..\\Data\\students.txt" };

			try
			{
				students = studentCsvFileManager.ReadStudents(inputFile);
			}
			catch (StudentCsvFileException& exception)
			{
				std::cout << exception.what() << std::endl;
			}

			auto counter = 0;
			std::for_each(begin(students), end(students),
				[&counter](std::shared_ptr<Student>& student)
			{
				switch (counter++)
				{
				case 0:
					Assert::IsTrue(student->GetFirstName() == "TED");
					Assert::IsTrue(student->GetLastName() == "BUNDY");
					Assert::IsTrue(student->GetScore() == 88);
					break;
				case 1:
					Assert::IsTrue(student->GetFirstName() == "ALLAN");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);
					break;
				case 2:
					Assert::IsTrue(student->GetFirstName() == "MADISON");
					Assert::IsTrue(student->GetLastName() == "KING");
					Assert::IsTrue(student->GetScore() == 83);
					break;
				case 3:
					Assert::IsTrue(student->GetFirstName() == "FRANCIS");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);
					break;
				}
			});
		}

		TEST_METHOD(ReadStudentsUsingMalformedInputFile)
		{
			// The variant input file looks like this (blank line, missing score and insufficient field delimiters):
			//	*
			//	*  TED,BUNDY,88
			//	*
			//	*  ALLAN,SMITH,85
			//	*  MADISON,KING,83
			//	*  HARRY,NORMAN,
			//	*  WENDY,JONES,100
			//	*  JAMES, BUTLER
			//	*  FRANCIS,SMITH,85
			//	*  

			StudentCsvFileManager studentCsvFileManager;
			Students students;
			std::string inputFile{ "..\\Data\\students-variant.txt" };

			try
			{
				students = studentCsvFileManager.ReadStudents(inputFile);
			}
			catch (StudentCsvFileException& exception)
			{
				std::cout << exception.what() << std::endl;
			}

			auto counter = 0;
			std::for_each(begin(students), end(students),
				[&counter](std::shared_ptr<Student>& student)
			{
				switch (counter++)
				{
				case 0:
					Assert::IsTrue(student->GetFirstName() == "TED");
					Assert::IsTrue(student->GetLastName() == "BUNDY");
					Assert::IsTrue(student->GetScore() == 88);
					break;
				case 1:
					Assert::IsTrue(student->GetFirstName() == "ALLAN");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);
					break;
				case 2:
					Assert::IsTrue(student->GetFirstName() == "MADISON");
					Assert::IsTrue(student->GetLastName() == "KING");
					Assert::IsTrue(student->GetScore() == 83);
					break;
				case 3:
					Assert::IsTrue(student->GetFirstName() == "HARRY");
					Assert::IsTrue(student->GetLastName() == "NORMAN");
					Assert::IsTrue(student->GetScore() == 0);		
					break;
				case 4:
					Assert::IsTrue(student->GetFirstName() == "WENDY");
					Assert::IsTrue(student->GetLastName() == "JONES");
					Assert::IsTrue(student->GetScore() == 100);					
					break;
				case 5:
					Assert::IsTrue(student->GetFirstName() == "FRANCIS");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);
					break;
				}
			});
		}
	};

	TEST_CLASS(TestStudentScoreManager)
	{
	public:

		TEST_METHOD(PersistStudents)
		{
			StudentScoreManager studentScoreManager;
			auto students = Students { std::make_shared<Student>("JOHN, DOE, 99"), std::make_shared<Student>("JAMES, SMITH, 25") };

			try
			{				
				studentScoreManager.PersistStudents(students);
			}
			catch (std::exception exception)
			{
				Assert::IsTrue(std::string(exception.what()) == "No respective CSV input-file provided. Output incorporates use of input-file name");
			}		
		}

		TEST_METHOD(CreateStudents)
		{
			StudentScoreManager studentScoreManager;
			StudentCsvFileManager studentCsvFileManager;			

			try
			{
				std::string inputFile{ "..\\Data\\students.txt" };
				studentScoreManager.CreateStudents(inputFile);
			}
			catch (StudentCsvFileException& exception)
			{
				std::cout << exception.what() << std::endl;
			}

			auto students = studentScoreManager.GetStudents();

			auto counter = 0;
			std::for_each(begin(students), end(students),
				[&counter](std::shared_ptr<Student>& student)
			{
				switch (counter++)
				{
				case 0:
					Assert::IsTrue(student->GetFirstName() == "TED");
					Assert::IsTrue(student->GetLastName() == "BUNDY");
					Assert::IsTrue(student->GetScore() == 88);
					break;
				case 1:
					Assert::IsTrue(student->GetFirstName() == "ALLAN");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);
					break;
				case 2:
					Assert::IsTrue(student->GetFirstName() == "FRANCIS");
					Assert::IsTrue(student->GetLastName() == "SMITH");
					Assert::IsTrue(student->GetScore() == 85);					
					break;
				case 3:
					Assert::IsTrue(student->GetFirstName() == "MADISON");
					Assert::IsTrue(student->GetLastName() == "KING");
					Assert::IsTrue(student->GetScore() == 83);
					break;
				}
			});
		}
	};
}