#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <streambuf>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

#define maxx 1000
#define minx 1
#define maxy 460
#define miny 1
#define POSTHRESHOLD 52000
#define NEGTHRESHOLD 1000

using namespace cv;
using namespace std;
struct timeval t1, t2;
int i=0;

int difftimer()
{
	gettimeofday(&t2, NULL);
	return (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec)/1000;
}

int main()
{
	gettimeofday(&t1, NULL);
	while(i<110)
	{
		i=i+1;
		int j=0;
		stringstream ss;
		ss << i;
		string filename="images/"+ss.str()+"b.jpg";
		string origname="images/"+ss.str()+".jpg";
		Mat src = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
		Mat colorsrc = imread(origname, CV_LOAD_IMAGE_COLOR);
		while(j<50)
		{
			Rect randomrect;
			srand (difftimer());
			randomrect.x = (rand()%(maxx-minx))+minx;
			srand (difftimer());
			randomrect.y = (rand()%(maxy-miny))+miny;
			randomrect.width = 256;
			randomrect.height = 256;
			Mat croppedRandom,thresholded;
			cout<<randomrect.x<<" "<<randomrect.y<<endl;
			threshold(src, thresholded, 128, 255, THRESH_BINARY);
			croppedRandom = thresholded(randomrect);
			int whitedots=countNonZero(croppedRandom);
			cout<<whitedots<<endl;
			if(whitedots>POSTHRESHOLD)
			{
				stringstream newss;
				srand (difftimer());
				newss << rand();
				Mat orig;
				orig=colorsrc(randomrect);
				cout<<"Positive found"<<endl;
				// imwrite("genData/pos/pos"+newss.str()+"b.png",croppedRandom);
				imwrite("genData/pos/pos"+newss.str()+".png",orig);
				j++;
			}
			else if (whitedots<NEGTHRESHOLD)
			{
				stringstream newss;
				srand (difftimer());
				newss << rand();
				Mat orig;
				orig=colorsrc(randomrect);
				cout<<"Negative found"<<endl;
				// imwrite("genData/neg/neg"+newss.str()+"b.png",croppedRandom);
				imwrite("genData/neg/neg"+newss.str()+".png",orig);
				j++;
			}
			else
			{
				cout<<"Nothing spectacular found. Trying again"<<endl;
			}
		}
	}

}
