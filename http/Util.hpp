#pragma once

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<sstream>
using namespace std;

class Util{
public:
	static void StringToLower(string& s)
	{
		transform(s.begin(), s.end(), s.begin(), ::tolower);
	}
	static void StringToUpper(string& s)
	{
		transform(s.begin(), s.end(), s.begin(), ::toupper);
	}
	static void TransformToVector(string& s, vector<string>& v)
	{
		size_t start = 0;
		while(1)
		{
			size_t pos = s.find('\n', start);
			if(string::npos == pos)
				break;
			string sub_str = s.substr(start, pos-start);
			v.push_back(sub_str);
			start = pos + 1;
		}
	}
	static void MakeKV(string s, string& key, string& val)
	{
		size_t pos = s.find(": ", 0);
		if(string::npos == pos)
			return;
		key = s.substr(0, pos);
		val = s.substr(pos+2);
	}
	static int StringToInt(string s)
	{
		stringstream ss(s);
		int ret = 0;
		ss >> ret;
		return ret;
	}
	static string IntToString(int i)
	{
		stringstream ss;
		ss<<i;
		return ss.str();
	}
	static string CodeToDec(int code)
	{
		switch(code){
			case 200:
				return "OK";
			case 404:
				return "NOT FOUND";
			default:
				return "Unkonw";
		}
	}
	static string SuffixToType(string &suffix)
	{
		string s = "Content-Type: ";
		if(suffix == ".html")
			s += "text/html";
		else if(suffix == ".png")
		s += "image/png";
		else if(suffix == ".css")
			s += "text/css";
		else if(suffix == ".js")
			s += "application/x-javascript";
		else if(suffix == ".jpg")
			s += "image/jpeg";
		else if(suffix == ".mp4")
			s += "video/mpeg4";
		else
			s += "text/html";
		return s;
	}
};






