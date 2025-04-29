// KJN - it is good practice to insert comment about intended use, context, contributors, etc
// This file contains the functions to convert weights and heights,
// process data from an input file and output to a text file with the result of the BMI category
// Contributors: KJN, GH

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int ounces2pounds(int x)
{
    return(x/16);
}

int stones2pounds(int x)
{
    return(x*14);
}

double weight2kg(int stones, int pounds, int ounces)
{
    return (stones2pounds(stones)+pounds+ounces2pounds(ounces))/2.2;
}

double height2metres(int feet, int inches)
{
    //convert inches to feet and then convert feet to metres
    double total_feet = feet + inches/12;
    return total_feet/3.28;
}

// Categories for the BMI
char categorise(double kg, double metre)
{
    double bmi = kg/(metre*metre);
    char cat;
    if (bmi<19)
        cat='A';
    else if (bmi<25)
        cat='B';
    else if (bmi<30)
        cat='C';
    else
        cat='D';
    return(cat);
}

void process_data(char* input_file, char* output_file)
{
    ifstream f_in;
    ofstream f_out;
    string data;
    string person_id;
    int pounds, stones, ounces, feet, inches;
    double kg, m;
    char cat;

    f_in.open(input_file,ios::in);
    f_out.open(output_file,ofstream::out);
    while (!f_in.eof())
    {
    	f_in >> person_id >> pounds >> stones >> ounces >> feet >> inches;
        kg=weight2kg(int(stones),int(pounds),int(ounces));
        m =height2metres(int(feet),int(inches));
        cat=categorise(kg,m);
	f_out << person_id << " " << cat << endl;
    }
    f_in.close();
    f_out.close();
}

int main(int argc, char *argv[])
{
    // Checking if 3 arguments are supplied, otherwise output error message
    if(artgc != 3)
	{
	   cerr << argv[0] << "<input_file> <output_file>" << endl;
	   return 1;
	}
    // KJN - Need to check that 3 arguments were supplied upon execution
    process_data(argv[1], argv[2]);
    return 0;
}
