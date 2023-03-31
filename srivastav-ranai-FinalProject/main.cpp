#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;

/**
 * Method to overlay an image onto another image
 *
 * WE go row by row and pixel by pixel until one of the images is exhausted
 *
 * @param bkg The background image
 * @param fg  The image to overlay with
 * @param op  The output destination
 * @param location The Point (x,y) where the top left corner of the image will be
 */
void img_overlay(const cv::Mat &bkg, const cv::Mat &fg,
                 cv::Mat &op, cv::Point2i location)
{
    bkg.copyTo(op);

    for(int row = std::max(location.y , 0); row < bkg.rows; row++)
    {
        int fY = row - location.y;

        if(fY >= fg.rows)
            break;

        for(int x = std::max(location.x, 0); x < bkg.cols; ++x)
        {
            int fX = x - location.x; // because of the translation.

            // we are done with this row if the column is outside of the fg image.
            if(fX >= fg.cols)
                break;

            // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
            double opacity =
                    2 * ((double)fg.data[fY * fg.step + fX * fg.channels() + 3]) / 255.;


            // and now combine the bkg and fg pixel, using the opacity,
            // but only if opacity > 0.
            for(int c = 0; opacity > 0 && c < op.channels(); ++c)
            {
                unsigned char foregroundPx =
                        fg.data[fY * fg.step + fX * fg.channels() + c];
                unsigned char backgroundPx =
                        bkg.data[row * bkg.step + x * bkg.channels() + c];
                op.data[row * op.step + op.channels() * x + c] =
                        backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}

/**
 * This method takes in 2 XML cascade classifiers and
 * @param frame
 * @param face_cascade
 * @param eyes_cascade
 */
void detectAndDisplay( Mat frame, CascadeClassifier face_cascade, CascadeClassifier eyes_cascade )
{

    Mat frame_gray;
    // Declare an ~ array
    Mat left_ear = imread("../left_bkg.png");
    int width = int(left_ear.cols * 0.6);
    int ht = int(left_ear.rows * 0.6);
    resize(left_ear, left_ear, Size(width, ht));


    Mat right_ear = imread("../right_bkg.png");
    width = int(left_ear.cols * 0.6);
    ht = int(left_ear.rows * 0.6);
    resize(right_ear, right_ear, Size(width, ht));

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );    // Convert to Grayscale to balance image
    equalizeHist( frame_gray, frame_gray );                 // Image brightness spread out over a larger range

    std::vector<Rect> faces;                                         // 2D rectangle array storing faces in the vid stream
    face_cascade.detectMultiScale( frame_gray, faces );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
//        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 0, 0, 0 ), 4 );
        Point start(center.x-faces[i].width/2, center.y-faces[i].height/2);
        Point end  (center.x+faces[i].width/2, center.y+faces[i].height/2);
//        rectangle(frame, start, end, Scalar(0,255,0), 3);


        Mat faceROI = frame_gray( faces[i] );                   //Face Region Of Interest

        //-- In each face, detect eyes
        std::vector<Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
//            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4 );

            if(eyes[j].x < faces[i].x/2)
            {
                std::cout << "left";
                img_overlay(frame, left_ear, frame, Point2i(faces[i].x + eyes[j].x + (eyes[j].width/2) - 190, faces[i].y + eyes[j].y + eyes[j].height/2 - 240));
            }
            else
            {
                std::cout << "right" << std::endl;
                img_overlay(frame, right_ear, frame, Point2i(faces[i].x + eyes[j].x + (eyes[j].width/2) - 10, faces[i].y + eyes[j].y + eyes[j].height/2 - 200));
            }
        }
    }

    imshow( "Capture - Face detection", frame );
}


/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main( int argc, const char** argv )
{

    String face_cascade_name = samples::findFile("../haarcascade_frontalface_alt.xml");
    String eyes_cascade_name = samples::findFile("../haarcascade_eye_tree_eyeglasses.xml");

    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;

    face_cascade.load(face_cascade_name);
    eyes_cascade.load(eyes_cascade_name);


    VideoCapture capture;
    capture.open( 0 );

    Mat frame;
    while ( capture.read(frame) )
    {
        detectAndDisplay(frame , face_cascade, eyes_cascade);

        if( waitKey(10) == 27 )
        {
            break;
        }
    }
    return 0;
}