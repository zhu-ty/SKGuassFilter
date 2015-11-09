//SKCommandHandler
//Do properthings when input a command.
//Author:ShadowK
//email:zhu.shadowk@gmail.com
//2015.11.9
//Use Ctrl+M,Ctrl+O to fold the code.

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "SKDefinition.h"
using namespace std;

class SKCommandHandler
{
public:
	void begin();
	bool handle(string s);
	bool handle(char *s);
	SKCommandHandler();
	~SKCommandHandler();
private:
	class SKCommandHandlerImpl *_impl;
};