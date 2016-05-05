#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;


#define TH1 10
#define alpha 0.7

float refBlue=0;
float refGreen=0;
float refRed=0;
float refCounter=0;

float refBlue2=0;
float refGreen2=0;
float refRed2=0;
float refCounter2=0;


int refX=0;
int refY=0;
int xyCounter=0;
int refX2=0;
int refY2=0;
int xyCounter2=0;


CvPoint CircleCenter;
int Radius;
CvScalar Color;
int Thickness;
int Shift;

int preprocessTime=60;

double Scale;
int FontFace;
double HorizontalScale;
double VerticalScale;
double Shear;
int LineType;
CvPoint TextPosition1,TextPosition2,TextPosition3;

int main()
{
        float x1;
        float y1;
        float x2;
        float y2;
        
        CvCapture *capture;  
        IplImage *frame; 
        IplImage *frame3;
        IplImage *frame6;
        IplImage* logoImg = NULL;
        IplImage *src = 0;
        IplImage* logoImg2 = NULL;
        CvSize logoImg_cvsize;
        float scale = 0.1;
        
        uchar* ptr3;
        uchar* ptr1;
        uchar* ptr4;
            
        int ballX;
        int ballY;
        int ballVX;
        int ballVY;
            
        int point;
        int point2;
            
        int midCircleCenterX;
        int midCircleCenterY;
                    
        int rightCircleCenterX;
        int rightCircleCenterY;
            
        int leftCircleCenterX;
        int leftCircleCenterY;
            
        bool isTouch=false;                     
        bool isTouch2=false;
        bool isWin; 
        int state=0;
        
        CvPoint FromPoint1,ToPoint1;
        CvPoint FromPoint2,ToPoint2;
        CvScalar Color;
        
        CvSize dst_cvsize;          //目標影像尺寸
        logoImg2=cvLoadImage("wm2.jpg");
        src=cvLoadImage("wm.jpg");
        logoImg_cvsize.width= src->width * scale;       
        logoImg_cvsize.height = src->height * scale; 
        
        logoImg = cvCreateImage( logoImg_cvsize, src->depth, src->nChannels); //創立目標影像
        cvResize(src, logoImg, CV_INTER_LINEAR);    //縮放來源影像到目標影像
        //cvSaveImage("0o.jpg", logoImg);//儲存影像
        cvFlip(logoImg, 0, 0);
        
        while(true){
            
            if(state==0){
                int c2=30;
                capture=cvCreateCameraCapture( 0 );
                //cvNamedWindow("Webcam",1);
                cvNamedWindow("Webcam3",1);
                           
                frame = cvQueryFrame(capture);    
                CvSize ImageSize1 = cvSize(1000,700);
                frame3 = cvCreateImage(ImageSize1,IPL_DEPTH_8U,3);
                
                srand (time(0));
                     
                ballX=rand() % 800+100;
                ballY=rand() % 600+50;
                ballVX=rand() % 10 -5;
                (ballVX==0)?ballVX++:ballVX=ballVX;
                ballVY=rand() % 10 -5;
                            
                point=0;
                point2=0;
                            
                midCircleCenterX=frame3->width/2;
                midCircleCenterY=frame3->height/2;
                                    
                rightCircleCenterX=frame3->width;
                rightCircleCenterY=frame3->height/2;
                            
                leftCircleCenterX=0;
                leftCircleCenterY=frame3->height/2;
                
                isTouch=false;                     
                isTouch2=false;
                isWin=false;         
                x1=0;
                y1=0;
                x2=0;
                y2=0;
                
                    
                while (c2 > 0) {
                      frame = cvQueryFrame(capture);      
                      frame6=cvCloneImage(frame);   
                      cvWaitKey(20);
                      c2--;
                      //cvShowImage("Webcam", frame);
                      cvShowImage("Webcam3", frame6);
                }     
                
                preprocessTime=60;
                while (preprocessTime > 0) {
                      frame = cvQueryFrame(capture); 
                      cvFlip(frame, 0, 1);     
                      frame6=cvCloneImage(frame);
                      cvRectangle(frame6, cvPoint(200,200), cvPoint(238,240), cvScalar(0,0,255), 2);   
                      for (int y=205; y<235; y++) {  
                              uchar* ptr2=(uchar*) (frame6->imageData +y*frame6->widthStep); 
                              //x=570 y=460
                              for (int x=205; x<235; x++) {     
                                 refBlue+=ptr2[3*x];
                                 refGreen+=ptr2[3*x+1];
                                 refRed+=ptr2[3*x+2];
                                 refCounter++;
                              } 
                      }
                      
                      cvRectangle(frame6, cvPoint(400,200), cvPoint(438,240), cvScalar(0,0,255), 2);   
                      for (int y=205; y<235; y++) {  
                              uchar* ptr2=(uchar*) (frame6->imageData +y*frame6->widthStep); 
                              for (int x=405; x<435; x++) {     
                                 refBlue2+=ptr2[3*x];
                                 refGreen2+=ptr2[3*x+1];
                                 refRed2+=ptr2[3*x+2];
                                 refCounter2++;
                              } 
                      }
                      
                      cvWaitKey(100);
                      preprocessTime--;
                      //cvShowImage("Webcam", frame);
                      cvShowImage("Webcam3", frame6);
                } 
                cvDestroyWindow("Webcam3");
                state=1;
                refBlue=refBlue/refCounter;
                refGreen=refGreen/refCounter;
                refRed=refRed/refCounter;
                
                refBlue2=refBlue2/refCounter;
                refGreen2=refGreen2/refCounter;
                refRed2=refRed2/refCounter;
                
                
                // printf(" refBlue  =  %.2f \n refGreen =  %.2f \n refRed   =  %.2f\n", refBlue,refGreen, refRed);
                //printf(" refBlue2  =  %.2f \n refGreen2 =  %.2f \n refRed2   =  %.2f\n", refBlue2,refGreen2, refRed2);
                //printf("%d %d",frame->width,frame->height);
                //ystem("pause");
            }
            
            if(state==1){
                while(1)
                {
                        
                     frame = cvQueryFrame(capture);     
                     cvFlip(frame, 0, 1);        
                     
                     for (int y=0; y<frame3->height; y++) {  
                          ptr3=(uchar*) (frame3->imageData +y*frame3->widthStep);  
                          for (int x=0; x<frame3->width; x++) {     
                             ptr3[3*x]=0;
                             ptr3[3*x+1]=0;
                             ptr3[3*x+2]=0; 
                          }
                     }
                     
                    cvRectangle(frame3, cvPoint(4,4), cvPoint(frame3->width-4,frame3->height-4), cvScalar(255,255,255), 5);
                    FromPoint1 = cvPoint(frame3->width/2,0);
                    ToPoint1 = cvPoint(frame3->width/2,frame3->height);
                                               
                    Color=CV_RGB(255,255,255);
                    Thickness=5;
                    Shift=0;
                    cvLine(frame3,FromPoint1,ToPoint1,Color,Thickness,CV_AA,Shift);
                    
                    CircleCenter=cvPoint(midCircleCenterX,midCircleCenterY);
                    Radius=100;
                    cvCircle(frame3,CircleCenter,Radius,Color,Thickness,CV_AA,Shift);
                    
                    CircleCenter=cvPoint(rightCircleCenterX,rightCircleCenterY);
                    cvCircle(frame3,CircleCenter,Radius,Color,Thickness,CV_AA,Shift);
                    
                    CircleCenter=cvPoint(leftCircleCenterX,leftCircleCenterY);
                    cvCircle(frame3,CircleCenter,Radius,Color,Thickness,CV_AA,Shift);
                    
                    //draw the ice ball
                    ballX+=ballVX;
                    ballY+=ballVY;
                    
                    Color=CV_RGB(255,255,0);
                    CircleCenter=cvPoint(ballX,ballY);
                    cvCircle(frame3,CircleCenter,20,Color,8,CV_AA,Shift);
                    
                    if(ballX-10<0){
                        ballVX*=-1;
                        ballX=10;
                        //cout << ballX << "," << ballY <<"," <<frame3->width<<","<<ballVX <<endl;
                        //system("pause");
                    }
                    if(ballX+10>frame3->width){
                        ballVX*=-1;
                        ballX=frame3->width-10;  
                    }
                    if(ballY-10<0){
                        ballVY*=-1;
                        ballY=10;
                    }  
                    if(ballY+10>frame3->height){
                        ballVY*=-1;
                        ballY=frame3->height-10;
                    }
                    // touch the circle
                    int rtCirDistance=(int)sqrt((rightCircleCenterX-ballX)*(rightCircleCenterX-ballX)+(rightCircleCenterY-ballY)*(rightCircleCenterY-ballY));
                    if(rtCirDistance-20<Radius&&isTouch==false){
                        point++;
                        isTouch=true;
                    }
                    if(rtCirDistance-20>Radius&&isTouch==true){
                        isTouch=false;
                    }
                    
                    int lfCirDistance=(int)sqrt((leftCircleCenterX-ballX)*(leftCircleCenterX-ballX)+(leftCircleCenterY-ballY)*(leftCircleCenterY-ballY));
                    if(lfCirDistance-20<Radius&&isTouch2==false){
                        point2++;
                        isTouch2=true;
                    }
                    if(lfCirDistance-20>Radius&&isTouch2==true){
                        isTouch2=false;
                    }
                    
                    //text area
                    Scale=3;
                    Thickness=3;
                    CvFont Font1=cvFont(Scale,Thickness);
                    Color=CV_RGB(155,255,255);
                    FontFace=CV_FONT_HERSHEY_SIMPLEX;
                    HorizontalScale=1;
                    VerticalScale=1;
                    Shear=2;
                    LineType=CV_AA;
                    TextPosition2=cvPoint(25,50);
                    TextPosition3=cvPoint(frame3->width-150,50);
        
                    cvInitFont(&Font1,FontFace,HorizontalScale,VerticalScale,Shear,Thickness,LineType);
                    char myBuf[60]={'P','o','i','n','t',':'};
                    sprintf(myBuf+6*sizeof(char),"%d",point);
                    cvPutText(frame3,myBuf,TextPosition2,&Font1,Color);
                    
                    sprintf(myBuf+6*sizeof(char),"%d",point2);
                    cvPutText(frame3,myBuf,TextPosition3,&Font1,Color);
                    
                    refX=0;
                    refY=0;
                    refX2=0;
                    refY2=0;
                    xyCounter=0;
                    xyCounter2=0;
                        
                    for (int y=0; y<frame->height; y++) {  
                        ptr1=(uchar*) (frame->imageData +y*frame->widthStep);   
                        for (int x=0; x<frame->width; x++) {     
                            float D= (ptr1[3*x] - refBlue) *  (ptr1[3*x] - refBlue) +
                            (ptr1[3*x+1] - refGreen) * (ptr1[3*x+1] -refGreen) +
                            (ptr1[3*x+2] - refRed) * (ptr1[3*x+2] - refRed);
                           
                             if (sqrt(D) < TH1) {
                                 xyCounter++;
                                 refX+=x;
                                 refY+=y;                        
                             }
                        }
                    }
                    
                    for (int y=0; y<frame->height; y++) {  
                        ptr1=(uchar*) (frame->imageData +y*frame->widthStep);   
                        for (int x=0; x<frame->width; x++) {     
                            float D2= (ptr1[3*x] - refBlue2) *  (ptr1[3*x] - refBlue2) +
                            (ptr1[3*x+1] - refGreen2) * (ptr1[3*x+1] -refGreen2) +
                            (ptr1[3*x+2] - refRed2) * (ptr1[3*x+2] - refRed2);
                           
                             if (sqrt(D2) < TH1) {
                                 xyCounter2++;
                                 refX2+=x;
                                 refY2+=y;                        
                             }
                        }
                    }
                    
                    
                        
                    if (xyCounter > 0) {
                       refX = refX/xyCounter;
                       refY = refY/xyCounter;
                       if(x1+50>ballX-20&&x1-50<ballX+20&&y1+50>ballY-20&&y1-50<ballY+20){
                           ballVX=refX/10;
                           ballVY=refY/10;
                        }
                    }
                    else {
                         refX=-1;
                         refY=-1;
                    }
                     
                    
                    if (xyCounter2 > 0) {
                       refX2 = refX2/xyCounter2;
                       refY2 = refY2/xyCounter2;
                       if(x2+50>ballX-20&&x2-50<ballX+20&&y2+50>ballY-10&&y2-50<ballY+10){
                           ballVX=refX2/10;
                           ballVY=refY2/10;
                        }
                    }
                    else {
                         refX2=-1;
                         refY2=-1;
                    }
                    
                  // Start to move a Logo using a refColor
                   if (refX >=0 && refY >=0) {
                      x1=refX;
                      x1*=1.2;
                      y1=refY*1.2;
                      if(x1>frame3->width/2-100)
                          x1=frame3->width/2-100;
                          
                      if(y1>frame3->height-10)
                          y1=frame3->height-10;                     
                   }
                   
                    if (refX2 >=0 && refY2 >=0) {
                      x2=refX2;
                      x2=x2*1.2+500;
                      y2=refY2*1.2;
                       if(x2>frame3->width-100)
                          x2=frame3->width-100;
                          
                       if(y2>frame3->height-10)
                          y2=frame3->height-10; 
                   }
                   
                   //printf(" * %f %f %d %d %d %d \n", x2, y1,refX, refY,refX2, refY2);
                
                   if( (logoImg->height + y1) > frame3->height) 
                       y1 = frame3->height - logoImg->height - 1;
                
                    for (int y=0; y<logoImg->height; y++) {  
                          ptr1=(uchar*) (logoImg->imageData +y*logoImg->widthStep);
                          ptr3=(uchar*) (frame3->imageData +(y+(int)y1)*frame3->widthStep); 
                          for (int x=0; x<logoImg->width; x++) {     
                                 ptr3[3*(x+(int)x1)]=alpha*ptr1[3*(x)] + (1-alpha)*ptr3[3*(x+(int)x1)]; 
                                 ptr3[3*(x+(int)x1)+1]=alpha*ptr1[3*(x)+1] + (1-alpha)*ptr3[3*(x+(int)x1)+1]; 
                                 ptr3[3*(x+(int)x1)+2]=alpha*ptr1[3*(x)+2] + (1-alpha)*ptr3[3*(x+(int)x1)+2];    
                          }
                    }
                   if( (logoImg2->height + y2) > frame3->height) 
                       y2 = frame3->height - logoImg2->height - 1; 
                   
                    for (int y=0; y<logoImg2->height; y++) {  
                          ptr1=(uchar*) (logoImg2->imageData +y*logoImg2->widthStep);
                          ptr3=(uchar*) (frame3->imageData +(y+(int)y2)*frame3->widthStep); 
                          for (int x=0; x<logoImg2->width; x++) {     
                                 ptr3[3*(x+(int)x2)]=alpha*ptr1[3*(x)] + (1-alpha)*ptr3[3*(x+(int)x2)]; 
                                 ptr3[3*(x+(int)x2)+1]=alpha*ptr1[3*(x)+1] + (1-alpha)*ptr3[3*(x+(int)x2)+1]; 
                                 ptr3[3*(x+(int)x2)+2]=alpha*ptr1[3*(x)+2] + (1-alpha)*ptr3[3*(x+(int)x2)+2];    
                          }
                    }
                    // End to move a Logo using a refColor
                    cvShowImage("Webcam", frame);
                    //isBreak
                    cvShowImage("Webcam3", frame3);
                    cvWaitKey(20);
                    //point2=10;
                    if(point>=10||point2>=10){
                         state=2;
                         isWin=true;
                         break;
                    }
                    
            }
        }
        
        if(state==2){
            //cout << point <<" "<< point2 <<endl;
            if(point>=10&&isWin){
                 Scale=100;
                 Thickness=3;
                 CvFont Font1=cvFont(Scale,Thickness);
                 Color=CV_RGB(255,0,0);
                 FontFace=CV_FONT_HERSHEY_SIMPLEX;
                 HorizontalScale=3;
                 VerticalScale=3;
                 Shear=2;
                 LineType=CV_AA;
                 TextPosition2=cvPoint(frame3->width/2-200,frame3->height/2);
                 
                 cvInitFont(&Font1,FontFace,HorizontalScale,VerticalScale,Shear,Thickness,LineType);
                 cvPutText(frame3,"Left Win",TextPosition2,&Font1,Color); 
                 cvShowImage("Webcam3", frame3);
                 cvWaitKey (15);
            }
            else if(point2>=10&&isWin){
                 Scale=100;
                 Thickness=3;
                 CvFont Font1=cvFont(Scale,Thickness);
                 Color=CV_RGB(0,255,0);
                 FontFace=CV_FONT_HERSHEY_SIMPLEX;
                 HorizontalScale=4;
                 VerticalScale=4;
                 Shear=2;
                 LineType=CV_AA;
                 TextPosition2=cvPoint(frame3->width/2-250,frame3->height/2);
                
                 cvInitFont(&Font1,FontFace,HorizontalScale,VerticalScale,Shear,Thickness,LineType);
                 cvPutText(frame3,"Right Win",TextPosition2,&Font1,Color);
                 cvShowImage("Webcam3", frame3);
                 cvWaitKey (15);
            }
            isWin=false;
            
            if(cvWaitKey (15)==13)
                state=0;
            else
                state=2;
        }
        cvWaitKey(20);
    }
    
    cvReleaseCapture(&capture);
    cvDestroyWindow("Webcam3");
    
}
