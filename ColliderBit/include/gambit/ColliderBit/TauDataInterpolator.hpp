#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream; using std::vector;





class TauDataInterpolator{
    private:
        vector<double> X, Y;
        vector<vector<double>> Z;
	bool debug1 = false;

        void fillVectors(string path){
            string filename(path);
            string file_contents;
            std::map<int, std::vector<string>> csv_contents;
            char delimiter = ',';
            file_contents = this->readFileIntoString(path);
            istringstream sstream(file_contents);
            std::vector<string> items;
            string record;
            std::vector<double> Ztmp;
            int counter = 0;
	    if(this->debug1){cout << "debug01" << endl;}
            while (std::getline(sstream, record)) {
                istringstream line(record);
                int cnt = 0;
                while (std::getline(line, record, delimiter)) {
                    items.push_back(record);
                    if (!std::isdigit(record[0]) && record[0] != '-'){
                        continue;
                    }
                    if (cnt == 0){
                        this->X.push_back(stringToDouble(record));
                        cnt++;
                    }
                    else if (cnt == 1){
                        this->Y.push_back(stringToDouble(record));
                        cnt++;
                    }
                    else{
                        Ztmp.push_back(stringToDouble(record));
                        cnt = 0;
                    }
                }

	    	if(this->debug1){cout << "debug02" << endl;}
                csv_contents[counter] = items;
                auto it = csv_contents.begin();
                std::advance(it, 1);
                items.clear();
                counter += 1;

            }
	    if(this->debug1){cout << "debug03" << endl;}
            this->X = this->uniqueVecEntries(this->X);
            this->Y = this->uniqueVecEntries(this->Y);
	    if(this->debug1){cout << "debug04" << endl;}

            this->vecToZ(Ztmp, this->X.size(), this->Y.size());
	    if(this->debug1){cout << "debug05" << endl;}
        //    this->printZ();
        }

        void printZ(){
            cout << Z.size() << endl;
            for (int i = 0; i<this->Z.size();i++){
                cout << Z[0].size() << " ";
            }
            for (int i = 0; i<this->Z.size(); i++){
                for (int j = 0; j<this->Z[0].size(); j++){
                    cout << Z[i][j] << " ";
                }
                cout << endl;
            }
        }

	void printV(vector<double> v){
		cout << v.size() << endl;
		for (int i = 0; i<v.size(); i++){
			cout << v[i] << endl;
		}
	}

        string readFileIntoString(const string& path) {
            auto ss = ostringstream{};
            ifstream input_file(path);
            if (!input_file.is_open()) {
                cerr << "Could not open the file - '"
                << path << "'" << endl;
            exit(EXIT_FAILURE);
            }
            ss << input_file.rdbuf();
            return ss.str();
        }

        double stringToDouble(string s){
            string resS1 = "";
            int i = 0;
            while(s[i] != '\0'){
                resS1 += s[i];
                i++;
            }
            double resD = std::stod(resS1);
            return resD;
        }

        std::vector<double> uniqueVecEntries(std::vector<double> v){
            std::sort(v.begin(),v.end());
	    if(this->debug1){cout << "debug11" << endl;}
            auto last = std::unique(v.begin(), v.end());
	    if(this->debug1){cout << "debug12" << endl;}
            v.erase(last,v.end());
	    if(this->debug1){cout << "debug13" << endl;}
            return v;
        }

        void vecToZ(std::vector<double> Zlong, int sizeX, int sizeY){
            std::vector<double> tmp;
	    if(this->debug1){cout << "debug21" << endl;}
            for (int i = 0; i < Zlong.size(); i++){
                tmp.push_back(Zlong[i]);
	    	if(this->debug1){cout << "debug22" << endl;}
                if (i != 0 && i!=1 && (i+1)%sizeX == 0 ){
	    	    if(this->debug1){cout << "debug23" << endl;}
                    this->Z.push_back(tmp);
                    tmp.clear();
                }

//            this->transposeZ();
            }
        }
        void transposeZ(){
            vector<vector<double>> newZ = this->Z;
            for (int ii = 0; ii < this->Z.size(); ii++){
                for (int jj = 0; jj < this->Z.size(); jj++){
                    newZ[ii][jj] = this->Z[jj][ii];
                }
            }
            this->Z = newZ;
        }

  
        double linearInterpolation(double x, double y,int indX,int indY){
            double res = 0.0;

	    
	    if(this->debug1){cout << "debug61" <<" " << indX << " " <<indY << " " << x <<" " << y << endl;}
            double slopeX = (this->Z[indX+1][indY] - this->Z[indX][indY])/(indX+1 - indX);
	    if(this->debug1){cout << "debug62" << endl;}
            double slopeY = (this->Z[indX][indY+1] - this->Z[indX][indY])/(indY+1 - indY);
	    if(this->debug1){cout << "debug63" << endl;}
            double priorX = this->linF(slopeX,x,this->X[indX],this->Z[indX][indY]);
	    if(this->debug1){cout << "debug64" << endl;}
            double priorY = this->linF(slopeY,y,this->Y[indY],Z[indX][indY]);
	    if(this->debug1){cout << "debug65" << endl;}

            res = (priorX + priorY)/2;
            return res;
        }

        double linF(double m, double x, double x0, double t){
            double res = m*(x-x0) + t;
            return res;
        }

    public:
        TauDataInterpolator(string path){
            this->fillVectors(path);
	    
	    //this->printV(this->X);
	    //this->printV(this->Y);
	    //this->printZ();
        }

/*        double interpolateAtXY(double x, double y){
            double res = 0.0;
            int indX, indY;
            for (int i = 0; i<this->X.size() && this->X[i]<=x; i++){
                indX = i;
            }
            for (int i = 0; i<this->Y.size() && this->Y[i]<=y; i++){
                indY = i;
            }

            if (x < -2){indX = 0;}
            if (y < -2){indY = 0;}
            if (x >= 2){indX = this->X.size()-2;}
            if (y >= 2){indY = this->Y.size()-2;}

            cout << "indX" << indX << " " << this->X[indX] << " "<< this->X[indX+1]<< endl;
            cout << "Zs" << this->Z[indX][indY] << " "<< this->Z[indX+1][indY] << " "<< this->Z[indX][indY+1] << endl;
            res = this->linearInterpolation(x,y,indX,indY);
            return res;
        }
*/
        double interpolateAtXY(double x, double y){
            double res = 0.0;
            int indX, indY;
            int i = 0;
	    if(this->debug1){cout << "debug52" << endl;}
	    //this->printV(this->X);
	    for (int ii = 0; ii < this->X.size() and this->X[ii] <= x; ii++){
		indX = ii;
	    }
            //while(this->X[i] <= x){
            //    indX = i;
            //    i++;
            //}
            i = 0;
	    if(this->debug1){cout << "debug53" << endl;}
            while(this->Y[i] <= y){
                indY = i;
                i++;
            }

	    if(this->debug1){cout << "debug54" << endl;}
            if (x < -2){indX = 0;}
            if (y < -2){indY = 0;}
            if (x >= 2){indX = this->X.size()-2;}
            if (y >= 2){indY = this->Y.size()-2;}
	    if(this->debug1){cout << "debug55" << endl;}

            res = this->linearInterpolation(x,y,indX,indY);
	    if(this->debug1){cout << "debug56" << endl;}
            return res;
        }

};


/*int main()
{

    Interpolator itpl("../HEPData_filled.csv");
    double res = itpl.interpolateAtXY(2,-1.2);
    cout << "res" << res << endl;
    string filename("../HEPData.csv");
    string file_contents;
    std::map<int, std::vector<string>> csv_contents;
    char delimiter = ',';
    cout << std::stod("-2.0") << endl;

    exit(EXIT_SUCCESS);
}
*/
