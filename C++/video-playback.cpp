// Reads a video file and plays it back
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("video-copy SRC DEST\n");
        return 1;
    }

    cv::VideoCapture video(argv[1]);
    if (!video.isOpened()) {
        printf("Failed to open video %s\n", argv[1]);
        return 1;
    }

    cv::namedWindow("edges", CV_WINDOW_AUTOSIZE);
    int frame_speed = video.get(CV_CAP_PROP_FPS);
    while (true) {
        cv::Mat frame;
        if (!video.read(frame))
            break;

        cv::imshow("edges", frame);
        cv::waitKey(frame_speed);
    }

    return 0;
}
