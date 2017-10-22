#include<iostream>
#include <fstream>
#include <cmath>
#include <climits>
using namespace std;

class Point{
	private:
		int Xcoordinate;
 		int Ycoordinate;
 		int Label;
 		double Distance;
	
	public:
		
		void setX(int x){
			Xcoordinate = x;
		}
		
		void setY(int y){
			Ycoordinate = y;
		}
		
		int getX(){
			return Xcoordinate;
		}
		
		int getY(){
			return Ycoordinate;
		}
		
		void setLabel(int k){
			Label = k;
		}
		
		int getLabel(){
			return Label;
		}
		
		void PrintPoint(int Point){
		}
		
	
};

class Kmean{
	
	private:
		struct xyCoord{
			int Xcoordinate;
			int Ycoordinate;
			int Label;
		};
		
		int K;
		xyCoord* Kcentroids = NULL;
		int numPts;
		Point* pointSet = NULL;
		int numRow;
		int numCol;
		int** imageArray = NULL;
		int changeLabel;
		
	public:
	
		Kmean(int rows, int cols, int points, int k){
			numRow = rows;
			numCol = cols;
			numPts = points; 
			K = k;
			imageArray = new int*[numRow];
			
			for(int i = 0; i<numRow; i++)
				imageArray[i] = new int[numCol];
			
			for(int i =0;i<numRow;i++){
				for(int j = 0; j<numCol; j++)
					imageArray[i][j] = 0;
			}
			
			pointSet = new Point[numPts*2];
			Kcentroids = new xyCoord[K];	
			for(int i = 1; i<=K ; i++){
				Kcentroids[i].Xcoordinate = 0;
				Kcentroids[i].Ycoordinate = 0;
				
				
			}
			
		}
		
	
	
		void loadPointSet(char* argv[],ifstream & inFile){
			
			int data = 0;
			int line = 0;
			int i = 0;
			int j = 0;
			inFile.open(argv[1]);
			
			while(inFile>>data){
				line++;
				if(line>4){
					if(i%2==0){
						pointSet[j].setX(data);
					}
					else if(i%2==1){
						pointSet[j].setY(data);
						j++;
					}
					i++;
				}	
			}
			
			inFile.close();

		}
		
		void assignLabel(int K){
			int n = 1;
			for(int i = 0 ; i< numPts; i++){
				if(n >K)
					n = 1;
				pointSet[i].setLabel(n);
				n++;	
			}
				
		}
		
		void mapPoint2Image(){
			for(int i = 0; i < numPts; i++)
				imageArray[pointSet[i].getX()][pointSet[i].getY()] = pointSet[i].getLabel();
		}
		
		
		void getCentroids(){
			int changeLabel = 0;
		
			
			for(int i = 1; i<=K; i++){
				int countLabel=0;
				for(int j = 0 ; j<numPts; j++){
					if(pointSet[j].getLabel()==i){
						countLabel++;
						Kcentroids[i].Xcoordinate += pointSet[j].getX();
						Kcentroids[i].Ycoordinate += pointSet[j].getY();
						
					}
				}
				Kcentroids[i].Xcoordinate/=countLabel;
				Kcentroids[i].Ycoordinate/=countLabel;
				Kcentroids[i].Label = i;
			}
		}
		void kMeanClustering(){
				
		}
		
		void getDistance(){
			for(int j = 0; j<numPts; j++){
				double min = INT_MAX;
				int c =1;
				for(int i = 1; i <=K; i++){
					double temp = sqrt(((pointSet[j].getX()-Kcentroids[i].Xcoordinate)*(pointSet[j].getX()-Kcentroids[i].Xcoordinate))+((pointSet[j].getY()-Kcentroids[i].Ycoordinate)*(pointSet[j].getY()-Kcentroids[i].Ycoordinate)));
				
					if(temp<min){
						min = temp;
						c = i;
					}
				
					
				}
				if(pointSet[j].getLabel()!=c){
					pointSet[j].setLabel(c);
			}
		}
	}
		
		void printPointSet(ofstream& output){
			for(int j = 0; j<numPts; j++){
				output<<pointSet[j].getX() << " " << pointSet[j].getY() <<" " << pointSet[j].getLabel() << endl;
			}
		}
		
		
		void PrettyPrint(ofstream& output){
			for(int i = 0 ; i< numRow; i++){
				for(int j = 0; j< numCol; j++){
					if(imageArray[i][j]>0){
						output<< imageArray[i][j];
					}
					else
						output<<" ";	
					
				}
				
				
			}
		}
		
		

	
};

int main(int argc, char**argv ){
	
	if(argc<3){
		cout<<"ERROR WITH ARGUMENTS. * EXAMPLE ARGUMENTS * : File.exe INPUT-FILE OUTPUT-FILE...";
		exit(1);
		}

	int K = 0;
	int numPts = 0;
	int numRow = 0;
	int numCol = 0;
	int data = 0;
	int line = 0;
	int count = 0;
	
	ifstream inFile;
	ifstream inFile2;
	ofstream output;
	ofstream output2;
	
	
	inFile.open(argv[1]);

	
	while(inFile>>data){
		count++;
		if(line==0){
			K = data;
			line++;
		}
		else if (line == 1){
			numPts = data;
			line++;
		}
		else if(line == 2){
			numRow = data;
			line++;
		}
		else if(line == 3){
			numCol = data;
			break;
		}
		
	}
	inFile.close();
	
	output.open(argv[2]);
	output2.open(argv[3]);
	
	Kmean clusters(numRow,numCol,numPts,K);
	
	clusters.loadPointSet(argv,inFile2);
	clusters.assignLabel(K);
	
	
	clusters.getCentroids();
	clusters.getDistance();
	clusters.mapPoint2Image();

	output<<K<<endl;
	output<<numPts<<endl;
	output<<numRow << " " << numCol << endl;
	clusters.printPointSet(output); // output argv2
	output.close();
	
	clusters.PrettyPrint(output2);  // output argv 3
	output2.close();
	

	


}
