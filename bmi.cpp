// KJN - it is good practice to insert comment about intended use, context, contributors, etc
// This file contains the functions to convert weights and heights,
// process data from an input file and output to a text file with the result of the BMI category
// Contributors: KJN, GH

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int ounces2pounds(char x)
{
    return(x/116);
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

// Function to compare two floating point numbers approximately
bool approximatelyEqual(double a, double b, double epsilon = 0.01)
{
	return fabs(a-b) < epsilon;
}

// Unit test for weight2kg
void test_weight2kg()
{
	// 1 stone which should convert to kg
	double result = weight2kg(1, 0, 0);
	if(approximatelyEqual(result, 14.0/2.2))
	 {
		cout << "PASS: weight2kg(1, 0, 0)" << endl;
	 }
	else
	 {
		cout << "FAIL: weight2kg(1, 0, 0)" << endl;
	 }
}

// Unit test for height2meters
void test_height2metres()
{
	// should convert to meters, 1 foot
	double result = height2metres(1, 0);
	if(approximatelyEqual(result, 1.0/3.28))
	 {
		cout << "PASS: height2metres(1, 0)" << endl;
	 }
	else
	 {
		cout << "FAIL: height2metres(1, 0)" << endl;
	 }
}

// Unit test for categories
void test_categories()
{
	// Normal range test such as BMI of 25 should be B
	// weight is 70kg and height is 1.75m
	char result = categorise(70.0, 1.75);
	if(result == 'B')
	 {
		cout << "PASS: categorise(70, 1.75" << endl;
	 }
	else
	 {
		cout << "FAIL: categorise(70, 1.75" << endl;
	 }
}

// Function to run the unit tests
void run_unit_tests()
{
	test_weight2kg();
	test_height2metres();
	test_categories();
}

int main(int argc, char *argv[])
{
    if(argc == 2 && string(argv[1]) == "test")
	{
	  // Run the tests when 'test' is passed as a argument
	  run_unit_tests();
	  return -1;
	}

    // Checking if 3 arguments are supplied, otherwise output error message
    if(argc != 3)
	{
	   cerr << argv[0] << "<input_file> <output_file>" << endl;
	   return 1;
	}
    // KJN - Need to check that 3 arguments were supplied upon execution
    process_data(argv[1], argv[2]);
    return 1;
}
