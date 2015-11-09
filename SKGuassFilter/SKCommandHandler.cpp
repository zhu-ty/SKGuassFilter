//Author:ShadowK
//email:zhu.shadowk@gmail.com
//2015.11.9
//Use Ctrl+M,Ctrl+O to fold the code.

#pragma once

#include "SKCommandHandler.h"
#include "SKImageDisplayer.h"

#include <vector>
#include <string>
using namespace cv;


class SKCommandHandlerImpl
{
public:


	//Compare two strings.(Case insensitive)
	bool compare(const string& x, const string& y);
	//For split string.
	vector<string> split(string str, string pattern);

	void help();
	void load(string s);
	void save(string s);
	void display(string name);
	void hide();
	void exit();

	void calculate();

	Mat input;
	Mat output;
	IplImage *display_pic;

	SKImageDisplayer idis;
};

SKCommandHandler::SKCommandHandler()
{
	_impl = new SKCommandHandlerImpl();
	_impl->display_pic = nullptr;
}
SKCommandHandler::~SKCommandHandler()
{
	if (_impl->display_pic != nullptr)	cvReleaseImage(&(_impl->display_pic));
	delete _impl;
}
void SKCommandHandler::begin()
{
	printf("Input command.Input \"help\" for command help.\n$");
}
bool SKCommandHandler::handle(char *s)
{
	string sr(s);
	return handle(sr);
}
bool SKCommandHandler::handle(string s)
{
	try
	{
		if (s == "")
			return false;
		vector<string> splitstr = _impl->split(s, " ");
		if (_impl->compare(splitstr[0], "help"))
			_impl->help();
		else if (_impl->compare(splitstr[0], "load"))
		{
			if (splitstr.size() < 2)
				printf("Error\n");
			else
				_impl->load(splitstr[1]);
		}
		else if (_impl->compare(splitstr[0], "save"))
		{
			if (splitstr.size() < 2)
				printf("Error\n");
			else
				_impl->save(splitstr[1]);
		}
		else if (_impl->compare(splitstr[0], "display"))
		{
			_impl->display("ImageNow");
		}
		else if (_impl->compare(splitstr[0], "hide"))
		{
			_impl->hide();
		}
		else if (_impl->compare(splitstr[0], "exit"))
		{
			printf("See you next time!\n");
			return true;
		}
		else if (_impl->compare(splitstr[0], "calculate"))
		{
			printf("Calculating...\n");
			_impl->calculate();
		}
#ifdef _DEBUG
		else if (_impl->compare(splitstr[0], "loadd"))
		{
			_impl->load("hw5.jpg");
		}
		else if (_impl->compare(splitstr[0], "cad"))
		{
			printf("Calculating...\n");
			_impl->calculate();
		}
#endif
		else
		{
			printf("Error\n");
		}
	}
	catch (...)
	{
		printf("Some error just happened. You may re-input your command if you wish.\n");
	}
	printf("\n");
	return false;
}

bool SKCommandHandlerImpl::compare(const string& x, const string& y)
{
	string::const_iterator p = x.begin();
	string::const_iterator q = y.begin();
	while (p != x.end() && q != y.end() && toupper(*p) == toupper(*q))
	{
		++p;
		++q;
	}
	if (p == x.end())
	{
		return (q == y.end());
	}
	if (q == y.end())
	{
		return false;
	}
	return false;
}
vector<string> SKCommandHandlerImpl::split(string str, string pattern)
{
	int pos;
	std::vector<std::string> result;
	if (str[str.length() - 1] == '\n')
		str.pop_back();
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
void SKCommandHandlerImpl::help()
{
	printf("\"load <FileName> <FileNum>\" Load or reload a image with full location.Input FileNum to add a picnum\n");
	printf("Sample: load C:\\Users\\WIN_20150404_144352.JPG 2\n");
	printf("\"display\"Display the output image.\n");
	printf("Sameple: display\n");
	printf("\"hide\"Stop displaying the image.\n");
	printf("Sameple: hide\n");
	printf("\"save <FileName>\"Save the image.Input the Name without the path to save it at the location of the program.\n");
	printf("Sameple: save C:\\Users\\WIN_20150404_144352.JPG\n");
	printf("\"calculate\"Do the main work of the program.\n");
	printf("Sameple: calculate\n");
	printf("\"exit\"Exit the program\n");
	printf("Sameple: exit\n");
	printf("WARNING:Do not use image which has spaces in its FileName.\n");

}
void SKCommandHandlerImpl::load(string s)
{
	input = imread(s,IMREAD_COLOR);
	if (input.empty())
		printf("Wrong FileName.\n");
	else
	{
		output = input;
		printf("Load successful.\n");
	}
}
void SKCommandHandlerImpl::save(string s)
{
	if (output.empty() || !imwrite(s,output))
	{
		printf("Error!\n");
	}
	printf("Save successful.\n");
}
void SKCommandHandlerImpl::display(string s)
{
	if (!output.empty())
	{
		idis.display(&output, s.c_str());
	}
}
void SKCommandHandlerImpl::hide()
{
	idis.hide();
}
void SKCommandHandlerImpl::exit()
{
	hide();
	printf("See you next time!\n");
}

void SKCommandHandlerImpl::calculate()
{
	//Check input and turn it into gray.
	if (input.empty())
		return;
	Mat tmp;
	cvtColor(input, tmp, CV_BGR2GRAY);
	//output = tmp;


	printf("\n");
}
