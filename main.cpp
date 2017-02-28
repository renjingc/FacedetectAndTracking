#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h> 

#include "tracker.h"
#include "detector.h"
#include "dataReader.h"
#include "multiTrackAssociation.h"
#include "parameter.h"

using namespace cv;
using namespace std;

static string _sequence_path_;
static string _detection_xml_file_;

//Configuration
int MAX_TRACKER_NUM;
int MAX_TEMPLATE_SIZE;
int EXPERT_THRESH;
double BODYSIZE_TO_DETECTION_RATIO;
double TRACKING_TO_BODYSIZE_RATIO;
int FRAME_RATE;
double TIME_WINDOW_SIZE;
double HOG_DETECT_FRAME_RATIO;

void read_config()
{
	ifstream conf_file("config.txt");
	
	if (!conf_file.is_open())
	{
		cerr<<"fail to load config.txt."<<endl;
		exit(1);
	}

	string line;
	while (conf_file.good())
	{
		getline(conf_file,line);
		istringstream line_s(line);
		string field;
		line_s>>field;
		if (field.compare("MAX_TRACKER_NUM:")==0)
			line_s>>MAX_TRACKER_NUM;
		else if (field.compare("FRAME_RATE:")==0)
			line_s>>FRAME_RATE;
		else if (field.compare("TIME_WINDOW_SIZE:")==0)
			line_s>>TIME_WINDOW_SIZE;
		else if (field.compare("HOG_DETECT_FRAME_RATIO:")==0)
			line_s>>HOG_DETECT_FRAME_RATIO;
		else if (field.compare("MAX_TEMPLATE_SIZE:")==0)
			line_s>>MAX_TEMPLATE_SIZE;
		else if (field.compare("EXPERT_THRESH:")==0)
			line_s>>EXPERT_THRESH;
		else if (field.compare("BODYSIZE_TO_DETECTION_RATIO:")==0)
			line_s>>BODYSIZE_TO_DETECTION_RATIO;
		else if (field.compare("TRACKING_TO_BODYSIZE_RATIO:")==0)
			line_s>>TRACKING_TO_BODYSIZE_RATIO;
	}
	conf_file.close();
}

void multiTrack(int readerType,int detectorType)
{
	namedWindow("multiTrack",CV_WINDOW_AUTOSIZE);
	SeqReader* reader;
	Mat frame;

	reader = new VideoReader(_sequence_path_);
	Sleep(1000);
	
	reader->readImg(frame);
	if (frame.data==NULL)
	{
		cerr<<"fail to open pictures!"<<endl;
		return ;
	}

	Detector* detector;
	detector = new FaceDetector();

	TrakerManager mTrack(detector,frame,EXPERT_THRESH);
	
	for (int frameCount=0;frame.data!=NULL;frameCount++)
	{
		mTrack.doWork(frame);

		if (frame.cols>640)
			resize(frame, frame, Size(640, frame.rows / (frame.cols/640)));
		imshow("multiTrack", frame);
		
		reader->readImg(frame);


		char c = waitKey(33);
		if(c == 'q') break;
		else if (c=='p')
		{
			waitKey(0);
		}
		else if(c != -1)
		{
			mTrack.setKey(c);
		}
	}

	delete reader;
	delete detector;
}

void help()
{
	cout << "usage: \n\n"
		"1.\n"
		"FacedetectAndTracking <sequence_path> \n"
		"（调用视频：<sequence_path>为视频地址）\n\n"

		"2.\n"
		"FacedetectAndTracking <sequence_path> \n"
		"（调用摄像头：<sequence_path>为摄像头编号，自带为0，usb摄像头插的为1）\n\n";

	getchar();
}

int main(int argc,char** argv)
{
	if (argc !=2)
	{
		help();
		exit(1);
	}

	read_config();

	_sequence_path_=string(argv[1]);
	int seq_format=VIDEO;
	
	multiTrack(seq_format, FACE);

	
	return 0;
}