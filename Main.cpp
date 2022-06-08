
#include <iostream>
#include <sstream>
#include <vector>
#include<set>
#include <fstream>
#include <algorithm>
#include<map>


using namespace std;

class YearAvg {
public:

	YearAvg() {
	this->temp = 0;
	this->year = 0;
	this->rain = 0;

}
	YearAvg(double temp, int year, double rain) {
	this->temp = temp;
	this->year = year;
	this->rain = rain;

}

	~YearAvg() {
	// TODO Auto-generated destructor stub
}

	double getRain() const {
		return rain;
	}

	void setRain(double rain) {
		this->rain = rain;
	}

	double getTemp() const {
		return temp;
	}

	void setTemp(double temp) {
		this->temp = temp;
	}

	int getYear() const {
		return year;
	}

	void setYear(int year) {
		this->year = year;
	}
	bool operator < (const YearAvg yrObj) const{
		return (year+temp+rain)<(yrObj.year+yrObj.temp+yrObj.rain);
	}
	const std::string toCSV() {
	std::ostringstream strs;
	strs << temp;
	std::string tempStr = strs.str();
	strs.str("");
	strs << year;
	std::string yearStr = strs.str();
	strs.str("");
	strs << rain;
	std::string rainStr = strs.str();

	return tempStr + "," + yearStr + "," + rainStr;

}
	static bool sortByRain(const YearAvg &lhs, const YearAvg &rhs) { return lhs.rain < rhs.rain; }

private:
	double temp;
	int year;
	double rain;

};

int main() {

	map<int,YearAvg> yearMap;
	vector<YearAvg> vavgs;
	string header;
	int size = 0;

	string line;
	ifstream file("yearly.csv");
	if (file.is_open()) {
		getline(file, header);
		while (getline(file, line)) {
			cout << line << '\n';

			std::stringstream sstr(line);
			std::string token;

			string toks[3];
			char delim = ',';

			int i = 0;


		while (std::getline(sstr, token, delim)) {

			toks[i] = token;
			i++;
		}
		
		  // store into vector
	 vavgs.push_back(YearAvg(stof(toks[0]), stoi(toks[1]), stof(toks[2])));
		size++;
		yearMap[stoi(toks[1])]=YearAvg(stof(toks[0]), stoi(toks[1]), stof(toks[2]));
	}	        

	cout << "size of file is " << size << endl;
	file.close();
}	       


else {
	cout << "Error opening file";
}
set<YearAvg> savgs(vavgs.begin(),vavgs.end());
for(YearAvg yearAvg:savgs){
	cout<<yearAvg.toCSV()<<endl;
}
cout<<"size of file is: "<<savgs.size()<<endl;

vector<YearAvg> vsort;
vsort.assign(savgs.begin(),savgs.end());

sort(vsort.begin(),vsort.end(),YearAvg::sortByRain);

ofstream ofile;
ofile.open("yearout.csv");
ofile << header << "\n";
for (const YearAvg &yearAvg : vsort) {
	ofile << yearAvg.getTemp() << "," << yearAvg.getYear() << ","
	<< yearAvg.getRain() << "\n";
}
ofile.close();

int year;
cout<<"Enter the year to check weather: ";
cin>>year;
if(yearMap.find(year)!=yearMap.end()){
	cout<<header;
	cout<<(yearMap.find(year)->second).toCSV()<<endl;
}
else cout<<"data for this year doesn't exist in the database"<<endl;

return 0;
}
