// lab16.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <locale>
#include <cwchar>
#include "Div.h"
#include "LexAnaliz.h"
#include "PolishNotation.h"

#define EXP1 17

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getin(parm.in);
		Lex::LEX lex = Lex::lexAnaliz(log, in);
		LT::showTable(lex.lextable, log);
		MFST_TRACE_START
			unsigned int start_time = clock();
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start();
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		cout << search_time << endl;
		mfst.savededucation();
		mfst.printrules();
		/*bool rc = PolishNotation(EXP1, lex);
		if (rc)
		cout << "Польская запись построена" << endl;
		else
		cout << "Польская запись не построена" << endl;
		LT::showTable(lex.lextable, log);*/
		//IT::showTable(lex.idtable);
		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};
	//system("notepad D://in.txt.log");
	system("pause");
	return 0;
};


