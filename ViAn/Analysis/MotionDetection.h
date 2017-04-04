#ifndef MOTIONDETECTION_H
#define MOTIONDETECTION_H

#include "AnalysisMethod.h"
#include <string>

/**
 * @brief The MotionDetection class
 * This class is used to detect motion in videos. This
 * is done using background subtraction with OpenCV.
 */
class MotionDetection : public AnalysisMethod {
public:
    MotionDetection(std::string source_file);

private:

    cv::Mat first_frame;                             // First frame in the video
    cv::Mat gray;                                    // Grayscale of current
    cv::Mat frame_delta, frame_thresh, frame_dilate;
    cv::Size blur_size = cv::Size(31,31);

    void setup_analysis() override;
    void do_analysis() override;


protected:

};

#endif // MOTIONDETECTION_H
