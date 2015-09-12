#include<iostream>
#include<string>
//#include<conio.h>
#include<fstream>
#include<stdio.h>

using namespace std;
fstream out, in;

char query[100], query1[100], rhs[10][100], thequery[100], *temp1;
int number, noc, rhsv = 0, ch = 0, once = 0, see = 0, haha = 0, seriously = 0;
char mystr[15][100],mystr1[15][100];

char lhs[10][100];
char forclause1[100], forclause2[100];
char *s1, *s2, *s3, *s4;
char qpart[100];
int temp;

class predicate
{
public:
	bool check[10];
	bool checlall;
	char pred[10][100];
	int no_of_predicates;
	predicate()
	{
		for (int i = 0; i < 10; i++)
		{
			check[i] = false;
		}
	}
}pr[10];
class clauses
{
public:
	char clau[10][50];
	int no_of_clauses;
	clauses()
	{
		no_of_clauses = -1;
	}
}cl;
bool checkpred(int i);
void reset()
{
	for (int i = 0; i < rhsv; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			pr[i].check[j] = false;
		}
	}
}
void checkpwc()
{
	haha = 0;
	int kl;
	bool val;
	do{
		kl = 0;
		see = 0;
		for (int i = 0; i < rhsv; i++)
		{
			for (int k = 0; k < pr[i].no_of_predicates; k++)
			{
				for (int j = 0; j <= cl.no_of_clauses; j++)
				{
					if (strcmp(pr[i].pred[k], cl.clau[j]) == 0)
					{
						kl++;
						pr[i].check[k] = true;
						//cout << pr[i].pred[k] << "--- available in facts---\n";
						val = checkpred(i);
						if (val == 1)
						{
							if (haha >= seriously)
							{
								return;
							}
							//cout << "TRUE";
							out << "TRUE";

							once = 1;
							//_getch();
							exit(1);
						}
					}
				}
			}
		}
	} while (see != 0);

}
bool duplicate(char rhs[100])
{
	for (int i = 0; i <= cl.no_of_clauses; i++)
	{
		if (strcmp(rhs, cl.clau[i]) == 0)
		{
			return true;
		}
	}
	return false;
}
void replace_pred(char forclause[100])
{
	char *s;
	char temps[100];
	for (int i = 0; i < rhsv; i++)
	{
		for (int j = 0; j <= pr[i].no_of_predicates; j++)
		{
			////cout << endl << pr[i].pred[j];
			strcpy(temps, pr[i].pred[j]);
			s = strstr(temps, "(x,");
			if (s != NULL)
			{
				s[0] = '\0';
				strcpy(pr[i].pred[j], temps);
				strcat(pr[i].pred[j], forclause);
				strcat(pr[i].pred[j], s + 2);
				//cout << endl << pr[i].pred[j];
			}
			s = strstr(temps, "(x)");

			if (s != NULL)
			{
				s[0] = '\0';
				strcpy(pr[i].pred[j], temps);

				strcat(pr[i].pred[j], forclause);
				strcat(pr[i].pred[j], ")");
				//cout << endl << pr[i].pred[j];
			}
			s = strstr(temps, ",x)");


			if (s != NULL)
			{
				s[0] = '\0';
				strcpy(pr[i].pred[j], temps);
				strcat(pr[i].pred[j], ",");
				strcat(pr[i].pred[j], forclause + 1);
				strcat(pr[i].pred[j], ")");
				//cout << endl << pr[i].pred[j];
			}

		}
	}
}

void replace_rhs(char forclause[100])
{
	char temps[100], *s;
	for (int i = 0; i < rhsv; i++)
	{
		strcpy(temps, rhs[i]);
		s = strstr(temps, "(x,");
		if (s != NULL)
		{
			s[0] = '\0';
			strcpy(rhs[i], temps);
			strcat(rhs[i], forclause);
			strcat(rhs[i], s + 2);
			//cout << endl << rhs[i];
		}
		s = strstr(temps, "(x)");

		if (s != NULL)
		{
			s[0] = '\0';
			strcpy(rhs[i], temps);

			strcat(rhs[i], forclause);
			strcat(rhs[i], ")");
			//cout << endl << rhs[i];
		}
		s = strstr(temps, ",x)");


		if (s != NULL)
		{
			s[0] = '\0';
			strcpy(rhs[i], temps);
			strcat(rhs[i], ",");
			strcat(rhs[i], forclause + 1);
			strcat(rhs[i], ")");
			//cout << endl << rhs[i];
		}
	}
}
void replace_pred1(char forclause[100])
{
	char *s;
	char temps[100], fortemp[100];
	for (int i = 0; i < rhsv; i++)
	{
		for (int j = 0; j <= pr[i].no_of_predicates; j++)
		{
			////cout << endl << pr[i].pred[j];
			strcpy(temps, pr[i].pred[j]);
			s = strstr(temps, ",x)");
			if (s != NULL)
			{
				s[0] = '\0';
				strcpy(pr[i].pred[j], temps);
				strcat(pr[i].pred[j], ",");
				strcat(pr[i].pred[j], forclause);
				//strcat(pr[i].pred[j], s + 2);
				//cout << endl << pr[i].pred[j];
			}
			s = strstr(temps, "(x)");

			if (s != NULL)
			{
				s[0] = '\0';
				strcpy(pr[i].pred[j], temps);
				strcat(pr[i].pred[j], "(");
				strcat(pr[i].pred[j], forclause);

				//cout << endl << pr[i].pred[j];
			}
			s = strstr(temps, "(x,");
			if (s != NULL)
			{
				strcpy(fortemp, forclause);
				s[1] = '\0';
				strcpy(pr[i].pred[j], temps);
				temp1 = strstr(fortemp, ")");
				temp1[0] = '\0';
				strcat(pr[i].pred[j], fortemp);
				//strcat(pr[i].pred[j], ",");
				strcat(pr[i].pred[j], s + 2);
				//strcat(pr[i].pred[j], s + 2);
				//cout << endl << pr[i].pred[j];
			}
		}
	}
}
void replace_rhs1(char forclause[100])
{
	char temps[100], *s, fortemp[100];
	for (int i = 0; i < rhsv; i++)
	{
		strcpy(temps, rhs[i]);
		s = strstr(temps, ",x)");
		if (s != NULL)
		{
			s[0] = '\0';
			strcpy(rhs[i], temps);
			strcat(rhs[i], ",");
			strcat(rhs[i], forclause);
			//	strcat(rhs[i], s + 2);
			//cout << endl << rhs[i];
		}
		s = strstr(temps, "(x)");

		if (s != NULL)
		{
			s[0] = '\0';
			strcpy(rhs[i], temps);
			strcat(rhs[i], "(");
			strcat(rhs[i], forclause);
			//strcat(rhs[i], ")");
			//cout << endl << rhs[i];
		}
		s = strstr(temps, "(x,");
		if (s != NULL)
		{
			strcpy(fortemp, forclause);
			s[1] = '\0';
			strcpy(rhs[i], temps);
			temp1 = strstr(fortemp, ")");
			temp1[0] = '\0';
			strcat(rhs[i], fortemp);
			//strcat(pr[i].pred[j], ",");
			strcat(rhs[i], s + 2);
			//strcat(pr[i].pred[j], s + 2);
			//cout << endl << rhs[i];
		}


	}
}

bool trueval(int i)
{
	int val = 0;
	for (int j = 0; j < pr[i].no_of_predicates; j++)
	{
		if (pr[i].check[j] == true)
		{
			val++;
		}
	}
	if (val == pr[i].no_of_predicates)
	{
		return true;
	}
	else return false;
}
void parse()
{

}
bool checkpred(int i)
{
	//seriously = 50;

	bool val;
	bool val1;
	for (int j = 0; j < pr[i].no_of_predicates; j++)
	{
		val = trueval(i);
		if (val == true)
		{
			val1 = duplicate(rhs[i]);
			if (val1 == false)
			{
				strcpy(cl.clau[++cl.no_of_clauses], rhs[i]);
			}
			haha++;
			see++;
			if (strcmp(rhs[i], thequery) == 0 || haha >= seriously)
			{
				return true;
			}
			return false;
		}
		else
		{


		}
		////cout << val;
	}
	return val;
}
void checkit()
{
	bool val;
	int cmp;
	for (int i = 0; i < rhsv; i++)
	{
		cmp = strcmp(rhs[i], thequery);
		if (cmp == 0)
		{
			//cout << "its there";
			val = checkpred(i);
			//cout << val;
		}

	}
}
void redo()
{
	
	rhsv = 0;
	seriously = 0;
	noc = 0;
	cl.no_of_clauses = -1;
	for (int i = 0; i < number; i++)
	{
		 strcpy(mystr[i],mystr1[i]);
		//cout << mystr[i] << endl;
	}
	
	for (int i = 0; i < number; i++)
	{
		s2 = mystr[i];
		if ((s1 = strstr(mystr[i], "=>")) != NULL)
		{
			seriously++;

			////cout << "true"<<endl;
			//	//cout << s1 + 2 << endl;
			//rhs[i] = "aa";
			s1[0] = '\0';
			strcpy(rhs[rhsv], s1 + 2);
			//cout << rhs[rhsv] << endl;
			strcpy(lhs[rhsv], mystr[i]);
			//cout << lhs[rhsv] << endl;
			for (int j = 0; lhs[rhsv][j] != '\0'; j++)
			{
				if (lhs[rhsv][j] == '&')
				{
					noc++;
				}
			}

			//cout << noc << endl;
			pr[rhsv].no_of_predicates = noc + 1;
			if (noc == 0)
			{
				//seriously+=1;
				strcpy(pr[rhsv].pred[0], lhs[rhsv]);
				//cout << pr[rhsv].pred[0] << endl << endl;
			}
			else{
				for (int k = 0; k < noc; k++)
				{
					seriously += 2;
					s2 = strstr(lhs[rhsv], "&");
					s2[0] = '\0';
					strcpy(pr[rhsv].pred[k], lhs[rhsv]);
					//cout << pr[rhsv].pred[k] << endl;
					////cout << s2+1<<endl;
					s2 = s2 + 1;
					strcpy(lhs[rhsv], s2);
					temp = k;
				}
				strcpy(pr[rhsv].pred[temp + 1], lhs[rhsv]);
				//cout << pr[rhsv].pred[temp + 1] << endl << endl;;
				noc = 0;
			}
			rhsv++;
		}

		else
		{
			strcpy(cl.clau[++cl.no_of_clauses], mystr[i]);
			//cout << cl.clau[cl.no_of_clauses] << "  clause  " << endl;
			if (strcmp(thequery, mystr[i]) == 0)
			{
				//cout << "TRUE";
				out << "TRUE";
				//_getch();
				exit(1);
			}
		}
	}

}
int main()
{
	in.open("input.txt");

	in >> query1;
	strcpy(thequery, query1);
	//cout << query1 << endl;
	in >> number;
	//cout << number << endl;
	for (int i = 0; i < number; i++)
	{
		in >> mystr1[i];
		//cout << mystr[i] << endl;
	}
	in.close();
	out.open("output.txt", ios::out);

	int l = 0;
	int mine = 0, mine1 = 0;


	redo();
	char query2[100];
	for (int f = 0; f <= cl.no_of_clauses + 1; f++)
	{
		char tmp[100];
		strcpy(tmp, query1);
		strcpy(query2, query1);
		s3 = strstr(query1, "(");
		//strcat(query1)
		////cout << s3 << endl;;
		strcpy(qpart, s3);
		s3[0] = '\0';
		//s3++;

		//strcpy(qpart, s3);
		char tes[100];
		if ((s4 = strstr(qpart, ",")) != NULL)
		{

			strcat(query1, "(");
			strcpy(tes, query1);
			//cout << query1;
			s4[0] = '\0';
			s4 = s4 + 1;
			strcpy(forclause1, qpart);
			//cout << s4 << endl;
			char first[20];
			strcpy(first, s4);
			strcpy(forclause2, s4);
			strcat(first, ",");
			s3 = strstr(query2, ",");
			////cout << s3 << endl;;
			s3[0] = '\0';
			s3++;
			strcpy(qpart, s3);
			s4 = strstr(s3, ")");
			s4--;
			s4 = '\0';
			//cout << s3 << endl;

			//cout << rhsv << endl;
			strcat(query1, "x,");
			for (int i = 0; i < rhsv; i++)
			{

				s3 = strstr(rhs[i], query1);
				if (s3 != NULL)
				{
					//cout << s3;

					strcat(query1, qpart);
					//cout << query1;
					ch++;
				}
				else
				{
					if (l > 0)
					{
						strcpy(query1, forclause1);
						strcat(query1, ",x)");
						for (int q = 0; q < rhsv; q++)
						{
							for (int w = 0; w < pr[q].no_of_predicates; w++)
							{
								s3 = strstr(pr[q].pred[w], query1);
								s4 = strstr(pr[q].pred[w], tes);
								if (s3 != NULL && s4 != NULL)
								{
									ch++;
									strcpy(pr[q].pred[w], tmp);
									replace_pred1(forclause2);
									replace_rhs1(forclause2);
									mine++;
								}
							}
						}
					}
				}
				////cout << endl<<forclause1;
				////cout << endl<< forclause2;
			}
		}
		else
		{

			seriously += 1;
			strcat(query1, qpart);
			char *s5;
			s5 = strstr(query1, "(");
			strcpy(forclause1, s5);
			s5 = strstr(forclause1, ")");
			s5[0] = '\0';
			//strcpy(forclause1,)
			//cout << query1;
			ch++;
			if (l > 0)
			{
				s3 = strstr(query1, "(");
				s3[0] = '\0';

				strcat(query1, "(x)");

				for (int q = 0; q < rhsv; q++)
				{
					for (int w = 0; w < pr[q].no_of_predicates; w++)
					{
						s3 = strstr(pr[q].pred[w], query1);

						s4 = strstr(pr[q].pred[w], tes);
						if (s3 != NULL && s4 != NULL)
						{
							ch++;
							strcpy(pr[q].pred[w], tmp);
							replace_pred(forclause1);
							replace_rhs(forclause1);
							mine++;
						}
					}
				}
			}
		}

		if (ch > 0 && mine == 0)
		{
			replace_pred(forclause1);
			replace_rhs(forclause1);
		}
		/*	else if (ch > 0 && mine != 0)
		{
		replace_pred1(forclause1);
		replace_rhs1(forclause1);
		}*/
		ch = 0;
		strcpy(tes, query2);
		strcat(query2, ",x)");
		for (int i = 0; i < rhsv; i++)
		{

			s3 = strstr(rhs[i], query2);
			if (s3 != NULL)
			{
				//cout << s3;
				//strcat(query2, ",x)");
				//cout << query1;
				ch++;
			}
			else
			{
				if (l > 0)
				{
					s4 = strstr(tes, "(");
					if (s4 != NULL)
					{
						s4[0] = '\0';
					}
					strcpy(query1, "(x,");
					strcat(query1, forclause2);
					for (int q = 0; q < rhsv; q++)
					{
						for (int w = 0; w < pr[q].no_of_predicates; w++)
						{
							s3 = strstr(pr[q].pred[w], query1);

							s4 = strstr(pr[q].pred[w], tes);
							if (s3 != NULL && s4 != NULL)
							{
								ch++;
								strcpy(pr[q].pred[w], tmp);
								replace_pred(forclause1);
								replace_rhs(forclause1);
								mine1++;
							}
						}
					}
				}
			}
			////cout << endl << forclause1;
			////cout << endl << forclause2;
		}
		if (ch > 0 && mine1 == 0)
		{
			replace_pred1(forclause2);
			replace_rhs1(forclause2);

		}
		/*	else if (ch > 0 && mine1 > 0)
		{
		replace_pred(forclause2);
		replace_rhs(forclause2);
		}*/
		checkpwc();
		reset();
		redo();
		strcpy(query1, cl.clau[f]);
		l++;
	}
	//checkit();
	//cout << "FALSE";
	out << "FALSE";
	out.close();

	//	_getch();
}
